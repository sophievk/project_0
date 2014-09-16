/*
*Authors: Sophie Khounlo, Dara Cline
*Date: September 12
*Description: recursively computes the nth Fibonacci number, if the n is less than or equal to 13
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

const int MAX = 13;

static void doFib(int n, int doPrint);


/*
 * unix_error - unix-style error routine.
 */
inline static void 
unix_error(char *msg)
{
    fprintf(stdout, "%s: %s\n", msg, strerror(errno));
    exit(1);
}


int main(int argc, char **argv)
{
  int arg;
  int print;

  if(argc != 2){
    fprintf(stderr, "Usage: fib <num>\n");
    exit(-1);
  }

  if(argc >= 3){
    print = 1;
  }

  arg = atoi(argv[1]);
  if(arg < 0 || arg > MAX){
    fprintf(stderr, "number must be between 0 and %d\n", MAX);
    exit(-1);
  }

  doFib(arg, 1);

  return 0;
}

/* 
 * Recursively compute the specified number. If print is
 * true, print it. Otherwise, provide it to my parent process.
 *
 * NOTE: The solution must be recursive and it must fork
 * a new child for each call. Each process should call
 * doFib() exactly once.
 */

//Sophie is driving
static void doFib(int n, int doPrint)
{
   static int  prevfib, fib, first=0, second=1;
   pid_t pid; 
   /*if(n == 0 || n == 1)
   {
     fib = n; 
   }
   else
   {
      //fprintf(stdout, "print\n");
     // fork();
      if(doPrint == 1)
      {
        fprintf(stdout, "%d\n", fib);
      }
      if((pid = fork()) == 0)
      {
        doFib(n-1, doPrint);
      }
      else
      {
        waitpid(getpid(), &status, 0);
      }
   }
   fprintf(stdout,"exit\n");
   exit(0);*/
   if(n >= 0){
      if((pid=fork()) == 0)			// if process is child
      {
        fib = first + second;
        first = second;
        second = fib;
        if(n == 0 || n == 1)
        {
          fib = n;
          second = fib;
        }
        else
        {
//          fprintf(stdout, "before fib: %d\n",fib);
//          fib += prevfib;
//	  fprintf(stdout, "after fibL %d\n",fib);
          doFib(n-1, doPrint);
        }
//        fprintf(stdout, "exit fib: %d\n", fib);
        exit(fib);
      }
      else
      {
        waitpid(getpid(), &fib, 0);		// wait for child process to finish
      }
      if(WIFEXITED(fib))
      {
        prevfib = WEXITSTATUS(fib);
	fprintf(stdout, "prevfib: %d\n", prevfib);
      }
      if(doPrint == 1)
      {
        fprintf(stdout,"number: %d\n", fib);
      }
      exit(0);
   }
}


