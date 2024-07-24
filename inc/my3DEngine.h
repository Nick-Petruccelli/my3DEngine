#ifndef MY3DENGINE_H
#define MY3DENGINE_H
#endif

#include "glMath.h"
#include "glad.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum { PLANE, CUBE, SPHERE, WEDGE } Primative;

typedef struct {
  unsigned int objID;
  float *assetPtr;
  vec3 position;
  vec3 rotation;
  vec3 scale;
  unsigned int textureID;
} Object;

typedef struct {
  Object *objects;
  unsigned int size;
  unsigned int numObjects;
} SceneObjects;

int engineInit(unsigned int windowWidth, unsigned int windowHeight);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void translateObject(unsigned int objID, vec3 translate);
void rotateObject(unsigned int objID, vec3 rotation);
void scaleObject(unsigned int objID, vec3 scale);
