#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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
  printf("here\n");
  pid_t parent = getpid();
  pid_t child_pid = fork();
  
  struct rlimit rlMem;
  struct rlimit rlFSize;
  struct rlimit rlTime;

  if(child_pid == -1){
    printf("error, failed to fork\n");
    exit(1);
  }
  else if(child_pid > 0){ //parent handling of what happened in execve
    printf("we are in parent\n");
    int status;
    waitpid(child_pid, &status,0);
    printf("status is %d\n", status);
    if( WIFEXITED(status) ){ 
      int value = WEXITSTATUS(status);
      printf("returned value %d\n", value);
      if(value < 65){
        return value;
      }else{
        return 128;
      }
    }
    else if( WIFSIGNALED(status ) ){ //terminated by bug
      // Child is terminated by a signal
      int sig_no = WTERMSIG(status);
      printf("failed with signal number %d\n", sig_no);
      return 128;
    }
  }
  else{ //run program using execve this is child
    getrlimit (RLIMIT_DATA, &rlMem);
    rlMem.rlim_cur = 64*1024*1024;
    setrlimit (RLIMIT_DATA, &rlMem);

    getrlimit (RLIMIT_FSIZE, &rlFSize);
    rlFSize.rlim_cur = 1;
    setrlimit (RLIMIT_FSIZE, &rlFSize);
        
    getrlimit (RLIMIT_CPU, &rlTime);
    rlTime.rlim_cur = 60;
    setrlimit (RLIMIT_CPU, &rlTime);
    printf("begin child process\n");
    execve(argv[1], new_argv, NULL);
    printf("done\n");
     
  }
  //run_confine(name, new_argv);

  }
  
  //exit(EXIT_FAILURE);

