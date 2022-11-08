#include  <stdio.h>
#include  <sys/types.h>
#include  <stdlib.h>

#define   MAX_COUNT  5

void  ChildProcess(void);                /* child process prototype  */
void  ParentProcess(int);               /* parent process prototype */

void  main(void)
{
  pid_t  pid;
  int status, i, children;
  children = 2;

  for (i = 0; i < children; i++){
    pid = fork();
    if (pid < 0){
      printf("Error: Fork Op \n");
      exit(-1);
      }
    else if (pid == 0){
      ChildProcess();
      exit(0);
      }
  wait(&status);
  ParentProcess(status);
  }
}


void  ChildProcess()
{
  int i, num_loops;
  pid_t pid, ppid;
  pid = getpid();
  ppid = getppid();

  srandom(getpid());
  num_loops = random()%31;

  for (i = 0; i <= num_loops; i++){
    printf("Child Pid: %d is going to sleep...\n", pid);
    sleep(random()%11);
    printf("          **     Child Pid: %d is awake!  Where is my Parent: %d \n", pid, ppid);
  }
  printf("   *** Child process is done ***\n\n");
}

void  ParentProcess(int stat)
{
  int i;
  pid_t pid;
  pid = getpid();

  printf("\n Child Pid: %d has completed\n", pid);
  printf("*** Parent is done, Child exit status is %d. ***\n\n", WEXITSTATUS(stat));
}