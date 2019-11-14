#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void print_array(char* arr[], int n){
  for(int i = 0; i < n; i++){
    printf("array[%d]: %s\n", i, arr[i]);

  }
  
}
int main(int argc, char *argv[]) {  
  if(argc == 1){
    fprintf(stderr, "Usage: %s <file-to-exec>\n", argv[0]);
    exit(EXIT_FAILURE);            
  }
  char* new_argv[argc];
  for(int i = 1; i < argc; i++){
    new_argv[i - 1] = argv[i];
  }
  new_argv[argc - 1] = NULL;
  execve(argv[1], new_argv, NULL);
  perror("execve");   /* execve() returns only on error */
  exit(EXIT_FAILURE);
}
