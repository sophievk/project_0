#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
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
 *
 * Sophie Khounlo - svk297
 * Dara Cline - dyc257
 */

// Dara is driving

void sigint_handler(int sig);
void sigusr1_handler(int sig);

int main(int argc, char **argv)
{

   pid_t pid;                       // pid of calling funcion
   const struct timespec interval = {1};
   struct timespec remain;

   pid = getpid();
   fprintf(stdout, "%d\n", pid);
   
   Signal(SIGINT, sigint_handler);
   Signal(SIGUSR1, sigusr1_handler);

   while(1)
   {
      fprintf(stdout, "Still here\n");
      nanosleep(&interval, &remain);
      if(strcmp(argv[0], "^c") == 0)
      {
         //nanosleep(&remain, NULL);
         sigint_handler(SIGINT);
         //nanosleep(&remain, NULL);
      }
   }
   return 0;
}

void sigint_handler(int sig)
{
   ssize_t bytes;
   const int STDOUT = 1;
   bytes = write(STDOUT, "Nice try.\n", 10);
   if(bytes != 10)
      exit(-999);
}

void sigusr1_handler(int sig)
{
   ssize_t bytes;
   const int STDOUT = 1;
   bytes = write(STDOUT, "exiting\n", 8);
   if(bytes != 8)
      exit(-999);
   exit(1);
}
