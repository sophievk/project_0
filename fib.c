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
   int fib, f1, f2, status, status2;
   pid_t pid, pid2;

   if(n == 0 ||  n == 1)
   {
      exit(n);
   }
   
   pid = fork(); 
   if(n >= 2)
   { 
      if(pid == 0)			// if process is child
      {
          doFib(n-1, doPrint-1);
      } 
      else
      {
          waitpid(pid, &status, 0);    //parent wait for child
          f1 = WEXITSTATUS(status);
       }
          pid2 = fork();
          if (pid2 == 0) 
          {
             doFib(n-2, doPrint-1);
          }
          else
          {
             waitpid(pid2, &status2, 0);
             f2 = WEXITSTATUS(status2);
          }
    }
    

    fib = f1 + f2;
    if(doPrint == 1)
    {
       fprintf(stdout, "fib: %d\n", fib);
    }
    else
    {
       exit(fib); //return to parent
    }
    exit(0);
}


