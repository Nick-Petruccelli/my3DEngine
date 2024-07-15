#include "../inc/my3DEngine.h"
#include "../inc/camera.h"
#include "../inc/glMath.h"
#include "../inc/glad.h"
#include "../inc/textures.h"
#include <GLFW/glfw3.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

SceneObjects sceneObjects;
unsigned int nextObjID;
unsigned int VBO, VAO;

int initEngine() {
  // window settings init
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // create window
  GLFWwindow *window = glfwCreateWindow(800, 600, "my3DEngine", NULL, NULL);
  if (window == NULL) {
    printf("Error Createing Window\n");
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  // initilize openGL function pointers with glad
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    printf("Error loading GLAD\n");
    return -1;
  }

  // init opengl viewport
  glViewport(0, 0, 800, 600);

  // set up window resizing
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // set the texture wrapping parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // create vertex buffer object
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5,
                        (void *)(sizeof(float) * 3));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  sceneObjects.objects = malloc(sizeof(Object) * 100);
  if (sceneObjects.objects == NULL) {
    printf("ERROR::SCENEINIT::SCENEOBJECTS\nfailed to allocate memory for "
           "scene objects\n.");
    return -1;
  }
  sceneObjects.size = 100;
  sceneObjects.numObjects = 0;

  return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

unsigned int placePrimitive(Primative prim, vec3 pos, vec3 rot, vec3 scale,
                            vec3 color) {
  if (sceneObjects.numObjects == sceneObjects.size) {
    printf("ERROR::MY#DENGINE::SCENEOBJECT::PLACEPRIMATIVE\nmax objects "
           "already placed\n");
    return NULL;
  }
  Object obj;
  unsigned int objID = nextObjID++;
  sceneObjects.numObjects++;
  switch (prim) {
  case PLANE:
    obj.vertData = loadPlaneData(color);
    break;
  case CUBE:
    obj.vertData = loadCubeData(color);
    break;
  case SPHERE:
    obj.vertData = loadSphereData(color);
    break;
  case WEDGE:
    obj.vertData = loadWedgeData(color);
    break;
  default:
    printf("ERROR::MY3DENGINE::SCENEOBJECT::PLACEPRIMATIVE\nfunction did not "
           "recive a valid enum option\n");
    return NULL;
  };

  copyVec3(pos, obj.position);
  copyVec3(rot, obj.rotation);
  copyVec3(pos, obj.scale);

  return objID;
}

float *loadPlaneData(vec3 color) {
  float *data = malloc(sizeof(float) * 48);

  float x = -0.5f;
  float y = -0.5f;
  float tx = 0;
  float ty = 0;
  bool evenTriangle = true;
  for (int i = 0; i < 6; i++) {
    data[(i * 8) + 0] = x;
    data[(i * 8) + 1] = y;
    data[(i * 8) + 2] = 0;
    data[(i * 8) + 3] = tx;
    data[(i * 8) + 4] = ty;
    data[(i * 8) + 5] = color[0];
    data[(i * 8) + 6] = color[1];
    data[(i * 8) + 7] = color[2];
    if (i == 2) {
      evenTriangle = !evenTriangle;
      continue;
    }
    if ((i % 2 == 0) && evenTriangle) {
      x += 1;
      tx += 1;
    }
    if ((i % 2 == 0) && !evenTriangle) {
      y -= 1;
      ty -= 1;
    }
    if ((i % 2 == 1) && evenTriangle) {
      y += 1;
      ty += 1;
    }
    if ((i % 2 == 1) && !evenTriangle) {
      x -= 1;
      tx -= 1;
    }
  }
  return data;
}
float *loadCubeData(vec3 color) {
  float *data = malloc(sizeof(float) * 288);
  float vertices[] = {
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 0.0f,
      0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
      -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

      -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
      -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f,

      -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f,
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
      -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  0.5f,  1.0f, 0.0f,

      0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
      0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 0.0f, 1.0f,
      0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 1.0f,
      0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
      -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

      -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      -0.5f, 0.5f,  0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f};

  for (int i = 0; i < 36; i++) {
    data[(i * 8)] = vertices[(i * 5)];
    data[(i * 8) + 1] = vertices[(i * 5) + 1];
    data[(i * 8) + 2] = vertices[(i * 5) + 2];
    data[(i * 8) + 3] = vertices[(i * 5) + 3];
    data[(i * 8) + 4] = vertices[(i * 5) + 4];
    data[(i * 8) + 5] = color[0];
    data[(i * 8) + 6] = color[1];
    data[(i * 8) + 7] = color[2];
  }

  return data;
}
float *loadSphereData(vec3 color) {
  float *data = malloc(sizeof(float) * 48);

  for (int i = 0; i < 6; i++) {
  }
  return data;
}
float *loadWedgeData(vec3 color) {
  float *data = malloc(sizeof(float) * 48);

  for (int i = 0; i < 6; i++) {
  }
  return data;
}

void translateObject(unsigned int objID, vec3 translate) {
  for (int i = 0; i < 3; i++) {
    sceneObjects.objects[objID].position[i] += translate[i];
  }
}
void rotateObject(unsigned int objID, vec3 rotation) {
  for (int i = 0; i < 3; i++) {
    sceneObjects.objects[objID].rotation[i] += rotation[i];
    int overRot = floorf(sceneObjects.objects[objID].rotation[i] / 360);
    if (overRot >= 1) {
      sceneObjects.objects[objID].rotation[i] -= overRot;
    }
    if (overRot + 1 <= -1) {
      sceneObjects.objects[objID].rotation[i] += overRot;
    }
  }
}
void scaleObject(unsigned int objID, vec3 scale) {
  for (int i = 0; i < 3; i++) {
    sceneObjects.objects[objID].scale[i] *= scale[i];
  }
}

void render() {}
