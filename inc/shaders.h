#ifndef SHADER_H
#define SHADER_H
#endif
#include "./glad.h"

char *loadShaderSource(char *path);
unsigned int compileShader(char *source, int shaderType);
unsigned int linkShaders(unsigned int vertex, unsigned int fragment);
unsigned int createShader(char *vertexPath, char *fragmentPath);
