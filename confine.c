#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h> 
 #include <sys/time.h>
#include <sys/resource.h>


void print_array(char* arr[], int n){
  for(int i = 0; i < n; i++){
    printf("array[%d]: %s\n", i, arr[i]);

  }
  
}
int main(int argc, char *argv[]) {  
  /*if(argc == 1){
    fprintf(stderr, "Usage: %s <file-to-exec>\n", argv[0]);
    exit(EXIT_FAILURE);            
  }*/
  /** set up arg array for execve */ 
  char* new_argv[argc]; // = construct_args(argc,argv)
  for(int i = 1; i < argc; i++){
    new_argv[i - 1] = argv[i];
  }
  new_argv[argc - 1] = NULL;
  /**begin forking process **/
 // printf("here\n");
  pid_t parent = getpid();
  pid_t child_pid = fork();
  
  struct rlimit rlMem;
  struct rlimit rlFSize;
  struct rlimit rlTime;

  if(child_pid == -1){
    printf("error, failed to fork\n");
    exit(1);
  }

  FILE *fp = NULL;
  char* outfilename = "confine_result.txt";

  fp = fopen(outfilename,"w");
  if(fp == NULL){
    printf("Unable to create file.\n");
    exit(EXIT_FAILURE);
  }


  if(child_pid == 0){//child
     getrlimit (RLIMIT_AS, &rlMem);
    rlMem.rlim_cur = 64*1024*1024;
    rlMem.rlim_max = 64*1024*1024;;
    setrlimit (RLIMIT_AS, &rlMem);

    getrlimit (RLIMIT_FSIZE, &rlFSize);
    rlFSize.rlim_cur = 4*1024*1024;
    rlFSize.rlim_max = 4*1024*1024;
    setrlimit (RLIMIT_FSIZE, &rlFSize);

    struct sigaction sact;
    sigaction(SIGALRM, &sact, NULL);
    alarm(60);
    //printf("begin child process\n");
    execve(argv[1], new_argv, NULL);
    perror("execve");
  }
  else{ //parent handling of what happened in execve
    //printf("we are in parent\n");
    int status;
    waitpid(child_pid, &status,0);
   // printf("status is %d\n", status);
    if( WIFEXITED(status) ){ 
      int value = WEXITSTATUS(status);
     // printf("returned value %d\n", value);
      fputs("NORMAL", fp);
      if(value < 65){
        return value;
      }else{
        return 128;
      }
    }
    else if( WIFSIGNALED(status ) ){ //terminated by bug
      // Child is terminated by a signal
      int sig_no = WTERMSIG(status);
      //printf("failed with signal number %d\n", sig_no);
      if(sig_no == 14){
        fputs("TIMEOUT", fp);
      }else{
        fputs("TERMINTATED", fp);
      }
      return 127;
    }
  }
  fclose(fp);
   exit(EXIT_FAILURE);
     
  

  }
  

