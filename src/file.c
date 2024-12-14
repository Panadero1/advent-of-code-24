#include "file.h"

#include <stdio.h>
#include <stdlib.h>

int read_file(char* path, char** b_out) {
  FILE* file = fopen(path, "r");

  if (file == NULL) {
    printf("can't open file\n");
    return -1;
  }

  if (fseek(file, 0, SEEK_END) != 0) {
    printf("couldn't seek\n");
    return -1;
  }
  long int size = ftell(file);

  fseek(file, 0, SEEK_SET);

  char* buf = (char*) malloc(size);

  if (fread(buf, 1, size, file) != size) {
    printf("problems reading\n");
    free(buf);
    return -1;
  }

  *b_out = buf;

  return size;
}
