#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  if(argc == 1) {
	fprintf(stderr, "Usage: %s /path/to/program args...\n", argv[0]);
	exit(1);
  }
}
