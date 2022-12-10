// Demonstrate how to install a signal handler.
// This program installs a handler for Ctrl-C and then
//   goes into an infinite loop. 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <signal.h>

#include <errno.h>

void
handler (int signal);

int
main ()
{
  if (signal (SIGINT, handler) == SIG_ERR)
  {
    fprintf (stderr, "signal error (%s) -- exiting\n",
	     strerror (errno));
    exit (1);
  }

  while (1)
    ; 
  
  return 0;
}

void
handler (int signal)
{
  printf ("Ctrl-c, lol\n"); 
  sleep (2);
  printf ("Fine, I'll stop\n"); 
  exit (17); 
}
