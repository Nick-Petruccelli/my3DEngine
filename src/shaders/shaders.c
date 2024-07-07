#include "../../inc/shaders.h"
#include "../../glad/glad.h"
#include <stdio.h>
#include <stdlib.h>

char *loadShaderSource(char *path) {
  FILE *fp = fopen(path, "r");
  if (fp == NULL) {
    printf("ERROR::SHADER::LOADING\nFailed to open file at %s", path);
    return NULL;
  }
  fseek(fp, 0, SEEK_END);
  int len = ftell(fp);
  rewind(fp);
  char *out = malloc(len);
  if (out) {
    fread(out, 1, len, fp);
  }
  out[len] = '\0';

  fclose(fp);

  return out;
}

unsigned int compileShader(char *source, int shaderType) {
  unsigned int shaderID;
  shaderID = glCreateShader(shaderType);
  glShaderSource(shaderID, 1, (const GLchar *const *)&source, NULL);
  glCompileShader(shaderID);
  free(source);

  int success;
  char infoLog[512];
  glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
    printf("ERROR::SHADER::COMPILATION_FAILED\n%s\n", infoLog);
  }

  return shaderID;
}

unsigned int linkShaders(unsigned int vertex, unsigned int fragment) {
  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertex);
  glAttachShader(shaderProgram, fragment);
  glLinkProgram(shaderProgram);
  glDeleteShader(vertex);
  glDeleteShader(fragment);

  int success;
  char infoLog[512];
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    printf("ERROR::SHADER::PROGRAM::LINK_FAILED\n%s\n", infoLog);
  }

  return shaderProgram;
}

unsigned int createShader(char *vertexPath, char *fragmentPath) {
  unsigned int vertexShader =
      compileShader(loadShaderSource(vertexPath), GL_VERTEX_SHADER);
  unsigned int fragmentShader =
      compileShader(loadShaderSource(fragmentPath), GL_FRAGMENT_SHADER);

  return linkShaders(vertexShader, fragmentShader);
}
