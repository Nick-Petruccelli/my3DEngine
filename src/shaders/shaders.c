#include "../../inc/shaders.h"
#include <stdio.h>
#include <stdlib.h>

char *loadShaderSource(char *path) {
  FILE *fp = fopen(path, "r");
  if (fp == NULL) {
    printf("ERROR::SHADER::LOADING\nFailed to open file at %s", path);
    return NULL;
  }
  int size = 0;
  char c;
  while ((c = fgetc(fp)) != EOF) {
    size++;
  }
  rewind(fp);
  char *out = (char *)malloc(sizeof(char) * (size - 1));

  int i = 0;
  while ((c = fgetc(fp)) != EOF) {
    out[i] = c;
    i++;
  }
  out[i] = c;
  fclose(fp);

  return out;
}
