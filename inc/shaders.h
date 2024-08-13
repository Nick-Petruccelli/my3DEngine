#ifndef SHADER_H
#define SHADER_H
#endif
#include "glMath.h"
#include "glad.h"

char *loadShaderSource(char *path);
unsigned int compileShader(char *source, int shaderType);
unsigned int linkShaders(unsigned int vertex, unsigned int fragment);
unsigned int createShader(char *vertexPath, char *fragmentPath);
void setUniform3fv(unsigned int shader, char *name, vec3 value);
void setUniform1f(unsigned int shader, char *name, float value);
void setUniform1i(unsigned int shader, char *name, int value);
