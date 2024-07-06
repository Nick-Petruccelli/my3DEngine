#include "../../inc/shaders.h"
#include <stdio.h>
#include <stdlib.h>

char *loadShaderSource(char *path) {
  FILE *fp = fopen(path, "r");
  if (fp == NULL) {
    printf("ERROR::SHADER::LOADING\nFailed to open file at %s", path);
    return NULL;
  }
  fseek(fp, 0L, SEEK_END);
  int size = ftell(fp);
  rewind(fp);
  char *out = (char *)malloc(sizeof(char) * size);

  int i = 0;
  char c;
  while ((c = fgetc(fp)) != EOF) {
    out[i] = c;
    i++;
  }
  fclose(fp);

  return out;
}
