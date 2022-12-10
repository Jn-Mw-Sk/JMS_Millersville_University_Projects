/*
 * tsh - A tiny shell program
 * 
 * @Co-author: John Shenk
 * 
 * I start this implementation by setting the signal handlers up in main.
 * I also created char arrays for the command-line argument (words) and the parsed tokens (args) 
 * Then I create an infinite loop to ask for input. When I get the input, I call eval, where the real magic happens.

 * At the end of thi loop I put a sleep(1) for the sake of output neatness
 * 
 * In my SIGCHLD handler, I only want to care about when a child finishes, So in my while loop 
 *      I have an if statement to check if the child exited. if not, just return and carry on. 
 *
 * I also have it set up where is the user presses Ctrl-C, Z while there is no current job, it essentailly does nothing.
 * 
 *  
 * In the builtIn function, if there is currently no suspended job and the user enters fg, it displays 
 *        "fg: no suspended job"
 *
 * To wait for a foreground job, I call the waitfg function in builtIn when the fg command is entered and there is a suspended job.
 *      waitfg is also called in eval when awaiting a 
 *
 */

/*
 *******************************************************************************
 * INCLUDE DIRECTIVES
 *******************************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/*
 *******************************************************************************
 * TYPE DEFINITIONS
 *******************************************************************************
 */

typedef void handler_t (int);

/*
 *******************************************************************************
 * PREPROCESSOR DEFINITIONS
 *******************************************************************************
 */

// max line size 
#define MAXLINE 1024 
// max args on a command line 
#define MAXARGS 128

/*
 *******************************************************************************
 * GLOBAL VARIABLES
 *******************************************************************************
 */

// defined in libc
extern char** environ;   

sigset_t new;
sigset_t old;

// command line prompt 
char prompt[] = "tsh> ";

// for composing sprintf messages
char sbuf[MAXLINE];

// PID of the foreground job's leader, or 0 if there is no foreground job
volatile pid_t g_runningPid = 0;
// PID of the suspended job's leader, or 0 if there is no suspended job
volatile pid_t g_suspendedPid = 0; 

/*
 *******************************************************************************
 * FUNCTION PROTOTYPES
 *******************************************************************************
 */

int
parseline (const char* cmdline, char**argv);

void
sigint_handler (int sig);

void
sigtstp_handler (int sig);

void
sigchld_handler (int sig);

void
sigquit_handler (int sig);

void
unix_error (char* msg);

void
app_error (char* msg);

handler_t*
Signal (int signum, handler_t* handler);

void 
eval(char* cmdline, char** argv);

bool
builtIn(const char* cmdline);

void
waitfg();
/*
 *******************************************************************************
 * MAIN
 *******************************************************************************
 */

int
main (int argc, char** argv)
{
  /* Redirect stderr to stdout */
  dup2 (1, 2);

  char words[MAXLINE];
  char* args[MAXARGS];

  /* Install signal handlers */
  Signal (SIGINT, sigint_handler);   /* ctrl-c */
  Signal (SIGTSTP, sigtstp_handler); /* ctrl-z */
  Signal (SIGCHLD, sigchld_handler); /* Terminated or stopped child */
  Signal (SIGQUIT, sigquit_handler); /* quit */

  /* TODO -- shell goes here*/
  while(true){
    
    printf("%s", prompt);
    fflush(NULL);
    
    if(feof(stdin)){
      exit(0);
    }
    
    fgets(words, MAXLINE, stdin);
    eval(words, args);
  }
  exit(0);
}

/*
*  parseline - Parse the command line and build the argv array.
*
*  Characters enclosed in single quotes are treated as a single
*  argument.
*
*  Returns true if the user has requested a BG job, false if
*  the user has requested a FG job.
*/
int
parseline (const char* cmdline, char** argv)
{
  static char array[MAXLINE]; /* holds local copy of command line*/
  char* buf = array;          /* ptr that traverses command line*/
  char* delim;                /* points to first space delimiter*/
  int argc;                   /* number of args*/
  int bg;                     /* background job?*/

  strcpy (buf, cmdline);
  buf[strlen (buf) - 1] = ' ';  /* replace trailing '\n' with space*/
  while (*buf && (*buf == ' ')) /* ignore leading spaces*/
    buf++;

  /* Build the argv list*/
  argc = 0;
  if (*buf == '\'')
  {
    buf++;
    delim = strchr (buf, '\'');
  }
  else
  {
    delim = strchr (buf, ' ');
  }

  while (delim)
  {
    argv[argc++] = buf;
    *delim = '\0';
    buf = delim + 1;
    while (*buf && (*buf == ' ')) /* ignore spaces*/
      buf++;

    if (*buf == '\'')
    {
      buf++;
      delim = strchr (buf, '\'');
    }
    else
    {
      delim = strchr (buf, ' ');
    }
  }
  argv[argc] = NULL;

  if (argc == 0) /* ignore blank line*/
    return 1;

  /* should the job run in the background?*/
  if ((bg = (*argv[argc - 1] == '&')) != 0)
  {
    argv[--argc] = NULL;
  }
  return bg;
}

/*
 *******************************************************************************
 * SIGNAL HANDLERS
 *******************************************************************************
 */

/*
*  sigchld_handler - The kernel sends a SIGCHLD to the shell whenever
*      a child job terminates (becomes a zombie), or stops because it
*      received a SIGSTOP or SIGTSTP signal. The handler reaps all
*      available zombie children, but doesn't wait for any other
*      currently running children to terminate.
*/
void
sigchld_handler (int sig)
{
  sigemptyset(&new);
  sigaddset(&new, SIGINT);

  pid_t pid;
  
  while((pid = waitpid(-1, &sig, WUNTRACED)) >= 0)
  {
    if(WIFEXITED(sig)){
        sigprocmask(SIG_BLOCK, &new, &old);
        if(g_runningPid){
          g_runningPid = 0;
        }
        sigprocmask(SIG_SETMASK, &old, NULL);
        return;
    } else if(WIFSIGNALED(sig)){
          printf("Job (%d) terminated by signal %d\n", g_runningPid, sig);
          return;
    } else if(WIFSTOPPED(sig)){
          printf("Job (%d) stopped by signal %d\n", g_runningPid, sig);
          return;
    }
  }
  return;
}

/*
 *  sigint_handler - The kernel sends a SIGINT to the shell whenever the
 *     user types ctrl-c at the keyboard.  Catch it and send it along
 *     to the foreground job.
 */
void
sigint_handler (int sig)
{
  sigemptyset(&new);
  sigaddset(&new, SIGINT);

  sigprocmask(SIG_BLOCK, &new, &old);
  if(g_runningPid != 0){
    kill(-g_runningPid, SIGINT);
    g_runningPid = 0;
  }
  sigprocmask(SIG_SETMASK, &old, NULL);
  return;
}

/*
 *  sigtstp_handler - The kernel sends a SIGTSTP to the shell whenever
 *      the user types ctrl-z at the keyboard. Catch it and suspend the
 *      foreground job by sending it a SIGTSTP.
 */
void
sigtstp_handler (int sig)
{
     sigemptyset(&new);
     sigaddset(&new, SIGINT);

     sigprocmask(SIG_BLOCK, &new, &old);
     if(g_runningPid != 0){
      kill(-g_runningPid, SIGSTOP);

      g_suspendedPid = g_runningPid;
      g_runningPid = 0;
    }
    sigprocmask(SIG_SETMASK, &old, NULL);
  return;
}

/*
 *******************************************************************************
 * HELPER ROUTINES
 *******************************************************************************
 */


/*
 * unix_error - unix-style error routine
 */
void
unix_error (char* msg)
{
  fprintf (stdout, "%s: %s\n", msg, strerror (errno));
  exit (1);
}

/*
*  app_error - application-style error routine
*/
void
app_error (char* msg)
{
  fprintf (stdout, "%s\n", msg);
  exit (1);
}

/*
*  Signal - wrapper for the sigaction function
*/
handler_t*
Signal (int signum, handler_t* handler)
{
  struct sigaction action, old_action;

  action.sa_handler = handler;
  sigemptyset (&action.sa_mask); /* block sigs of type being handled*/
  action.sa_flags = SA_RESTART;  /* restart syscalls if possible*/

  if (sigaction (signum, &action, &old_action) < 0)
    unix_error ("Signal error");
  return (old_action.sa_handler);
}

/*
*  sigquit_handler - The driver program can gracefully terminate the
*     child shell by sending it a SIGQUIT signal.
*/
void
sigquit_handler (int sig)
{
  printf ("Terminating after receipt of SIGQUIT signal\n");
  exit (1);
}

/**
 * @brief ls &
 * @param cmdline The command line
 * @param argv A list of arguments to execute
 */
void
eval(char* cmdline, char** argv){
  sigemptyset(&new);
  //sigaddset(&new, SIGINT);
  //sigaddset(&new, SIGSTOP);

  bool is_bg = parseline(cmdline, argv);
  if(strlen(cmdline) < 2){
    return;
  }
  if(!builtIn(cmdline)){
    sigprocmask(SIG_BLOCK, &new, &old);
    int pid = fork();
    if(pid < 0){
          fprintf (stderr, "fork error (%s) -- exiting\n",
            strerror (errno));
          exit (1);
    }
    if(pid == 0){
      sigprocmask(SIG_SETMASK, &old, NULL);
      setpgid(pid, 0);
      int ret = execvp (argv[0], argv); 

      if (ret < 0)
      {
          cmdline[strlen(cmdline) - 1] = 0;
          printf ("%s: Command not found\n", cmdline);
          exit(1);
      }
      exit(0);

    } else {
        if(is_bg) {
          printf("(%d) %s\n", pid, argv[0]);
        } else {
          g_runningPid = pid;
          waitfg();
        }
    }
  }
  sigprocmask(SIG_UNBLOCK, &old, 0);
  return;
}

/**
 * @brief Checks if the command entered is built in ("quit" or "fg")
 * 
 * @param cmdline The command line we would like to check
 * @return true if the command is built in
 * @return false if the command is not built in
 */
bool
builtIn(const char* cmdline){
  sigemptyset(&new);
  //sigaddset(&new, SIGINT);
  sigaddset(&new, SIGSTOP);

  if(strcmp(cmdline, "quit\n") == 0){
    exit(0);
  }
  if(strcmp(cmdline, "fg\n") == 0){
    
    sigprocmask(SIG_BLOCK, &new, &old);
    if(g_suspendedPid == 0){
      printf("fg: No suspended job\n");
      return true;
    }
    g_runningPid = g_suspendedPid;
    g_suspendedPid = 0;
    kill(-g_runningPid, SIGCONT);
    waitfg();
    sigprocmask(SIG_SETMASK, &old, NULL);
    
    return true;
  }
  return false;
}

/**
 * @brief Waits until the fg process is finished and reaped
 * 
 */
void waitfg(){
  while(g_runningPid != 0){ 
    sigsuspend(&old);
  }
  return;
}