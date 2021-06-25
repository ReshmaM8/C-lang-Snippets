#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h> 
#include <unistd.h>
#include <sys/wait.h>
//ps aux | awk {'print $8'}|grep -c Z
void handler(int signum){}
int main(int argc, char** argv){
//playing ball with one parent and child process for N times 
int N= atoi (argv[1]);
pid_t child_pid;
sigset_t newmask, waitmask;
sigprocmask(SIG_BLOCK, &newmask, &waitmask); 
child_pid = fork();

sigemptyset(&waitmask); 
sigemptyset(&newmask); 
sigaddset(&waitmask, SIG_BLOCK); 
sigaddset(&newmask, SIGUSR1);

 if(child_pid < 0){
   return 1; 
 }
 while (N--)
    if (child_pid == 0)
    {
      printf("Hey, parent, throw the ball!\n");
      sigsuspend(&waitmask);
      // the child has the ball and will throw it to the parent
     
      printf("Hey, parent, catch the ball!\n");
      kill(getppid(), SIGUSR1);
    }
    
    else
    {
      // parent has the ball and will throw it to the child
      signal(SIGUSR1, handler);
      printf("Hey, kid, catch the ball!\n");
      kill(child_pid, SIGUSR1);
      printf("Hey, child, throw the ball!\n");
      sigsuspend(&waitmask);
    }

}
