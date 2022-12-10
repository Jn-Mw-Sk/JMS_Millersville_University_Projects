// A program that will always terminate due to a signal.

#include <stdio.h>

int
main ()
{
  // Dereferencing NULL is illegal!
  return *(int *) NULL;
}
