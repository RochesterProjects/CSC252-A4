#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]){
    printf("here\n");
    int *new2 = NULL;
    new2 = malloc(66666666);
    if (new2 == NULL)
    {
        printf("malloc failed\n");
        exit( EXIT_FAILURE );
    }
    else
    {
        printf("success\n");
    }

  return 0;
}
