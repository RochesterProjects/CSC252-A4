#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h> 


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
      printf("failed with singal number %d\n", sig_no);
      return 128;
    }
  }
  else{ //run program using execve
    printf("begin child process\n");
    execve(argv[1], new_argv, NULL);
    printf("done\n");
     
  }
  //run_confine(name, new_argv);

  }
  
  //exit(EXIT_FAILURE);

