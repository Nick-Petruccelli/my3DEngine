#include "../inc/assetManager.h"
#include "../inc/camera.h"
#include "../inc/glMath.h"
#include "../inc/glad.h"
#include "../inc/my3DEngine.h"
#include "../inc/renderer.h"
#include "../inc/shaders.h"
#include "../inc/textures.h"
#include <GLFW/glfw3.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
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

  // create shader program
  unsigned int shaderProgram =
      createShader("./src/shaders/vertex.glsl", "./src/shaders/fragment.glsl");

  // set the texture wrapping parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // create texture object
  unsigned int texture = generateTexture("box.png");

  // create list of verticies to render
  float *verts1 = loadCubeData();
  float *verts2 = loadPlaneData();

  initAssetManager(2);
  addAsset(verts1, 36, GL_STATIC_DRAW);
  printf("VBO: %d, VAO: %d\n", MIA.meshInfo[0].vbo, MIA.meshInfo[0].vao);

  // render loop
  glEnable(GL_DEPTH_TEST);

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw triangles
    glBindTexture(GL_TEXTURE_2D, texture);

    // transform vertecies
    glUseProgram(shaderProgram);

    mat4 model;
    mat4 trans;
    mat4 rot;
    mat4 scale;
    genRotationMat4(0, 0, 0, rot);
    genScaleMat4(1, 1, 1, 1, scale);
    genTranslationMat4(0, 0, 0, trans);
    genModelMat(trans, rot, scale, model);
    const float radius = 10.0f;
    float camx = sinf(glfwGetTime()) * radius;
    float camy = 0;
    float camz = cosf(glfwGetTime()) * radius;
    mat4 view;
    vec3 camPos = {camx, camy, camz};
    vec3 origin = {0, 0, 0};
    vec3 up = {0, 1, 0};
    lookAt(camPos, origin, up, view);
    mat4 proj;
    genPerspectiveMat(45, 800.0f / 600.0f, .1, 100, proj);
    int modelLoc = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, convertMat4ToArr(model));
    int viewLoc = glGetUniformLocation(shaderProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, convertMat4ToArr(view));
    int projLoc = glGetUniformLocation(shaderProgram, "proj");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, convertMat4ToArr(proj));

    render();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwTerminate();

  return 0;
}
