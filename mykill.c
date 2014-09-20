#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

/*
 * Sophie Khounlo - svk297
 * Dara Cline - dyc257
 */


//Sophie is driving
int main(int argc, char **argv)
{
  pid_t pid;
  
  pid = atoi(argv[1]);
  kill(pid, SIGUSR1);

  return 0;
}
