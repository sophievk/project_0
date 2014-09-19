#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include "util.h"


/*
 * First, print out the process ID of this process.
 *
 * Then, set up the signal handler so that ^C causes
 * the program to print "Nice try.\n" and continue looping.
 *
 * Finally, loop forever, printing "Still here\n" once every
 * second.
 */

// Dara is driving
int main(int argc, char **argv)
{
  /* use getpid() system call to find pid
   *
   * print pid
   *
   * loop continuously, printing "Still here\n" once every second
   * 
   * set up a signal handler so that if you hit ctrl-c (^c), it prints nice
   * try and continues the loop
   */

   int pid;                       // pid of calling funcion
   const struct timespec interval = {1};

   pid = getpid();
   fprintf(stdout, "%d\n", pid);
   
   while(1)
   {
      fprintf(stdout, "Still here\n");
      nanosleep(&interval, NULL);
//      if(argv[0] == '^c')
//      {
//         SIGCTRLC(argv[0]);
//      }
   }
   return 0;
}

/*handler_t *SIGCTRLC(char *cmdline)
{
   if(&cmdline == )
      ssize_t bytes;
      const int STDOUT = 1;
      bytes = writes(STDOUT, "Nice try.\n", 10);

   return 0;
}*/


