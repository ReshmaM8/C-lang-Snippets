#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h> 
#include <unistd.h>
#include <sys/wait.h>
//HAS NO SIGNALS OR CLOCK TIME 
//TODO
//modified code of orginal assignment code: 
//1) Create a N processes if the leader value = 0
//example run: ./ring 4 0 0 
//


int main(int argc, char** argv) {
  //unpack N, leader and cnt values 
  int N = atoi (argv[1]);       
  int leader = atoi (argv[2]); 
  int cnt = atoi (argv[3]); 
  //transofrm for exec 
   char n[1]; 
  // char lead[7];
  // char count[5];  
  //declare pid 
   pid_t pid;
   pid = fork();
  //signal declaration 
  sigset_t newmask, waitmask;
  sigemptyset(&waitmask); 


  while(N!=1){
    //check leader value = 0 or !=0 
    if(leader == 0 && pid != 0){
        if(pid <0 ) return 1; 
        leader = getpid();
        printf("parent process %d\n", getppid()); 
        printf("first child(leader): %d %d %d\n", N, leader, cnt); N = N - 1; 
        // sprintf(n,"%c", N); //cnt goes zero here ??
        //sprintf(lead,"%c",leader); 
        //sprintf(count,"%c", cnt);
        //execl("./ring.c", n, leader, cnt, NULL);
    }
    if(leader != 0){
      //the second to N child process will be created 
      printf("grandchild process: %d %d %d\n", N, leader, cnt); 
      N = N - 1; 
      sprintf(n,"%c", N);
      execl("./ring.c", n, leader, cnt, NULL);
      
    }
  }

  if(N == 1){
   //final child send signal to leader 
   printf("end of N process: %d %d %d\n", N, leader,cnt); 
   //kill(leader,SIGUSR1);
  }




}
