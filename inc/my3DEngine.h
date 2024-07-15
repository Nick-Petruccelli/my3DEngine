#ifndef MY3DENGINE_H
#define MY3DENGINE_H
#endif

#include "../inc/glad.h"
#include "glMath.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum { PLANE, CUBE, SPHERE, WEDGE } Primative;

typedef struct {
  unsigned int objID;
  float *vertData;
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

unsigned int placePrimitive(Primative prim, vec3 pos, vec3 rot, vec3 scale,
                            vec3 color);
float *loadPlaneData(vec3 color);
float *loadCubeData(vec3 color);
float *loadSphereData(vec3 color);
float *loadWedgeData(vec3 color);

void translateObject(unsigned int objID, vec3 translate);
void rotateObject(unsigned int objID, vec3 rotation);
void scaleObject(unsigned int objID, vec3 scale);

void render();
