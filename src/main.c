#include "../inc/camera.h"
#include "../inc/glMath.h"
#include "../inc/glad.h"
#include "../inc/my3DEngine.h"
#include "../inc/shaders.h"
#include "../inc/textures.h"
#include <GLFW/glfw3.h>
#include <math.h>
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
  vec3 cubeColor = {0, 50, 0};
  float *verts1 = loadCubeData(cubeColor);
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

  vec3 planeColor = {50, 0, 0};
  float *verts2 = loadPlaneData(planeColor);

  // create vertex buffer object
  unsigned int VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  printf("size of verts1:\t%lu\n", 180 * sizeof(float));
  printf("size of vertices:\t%lu\n", sizeof(vertices));
  glBufferData(GL_ARRAY_BUFFER, 288 * sizeof(float), verts1, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8,
                        (void *)(sizeof(float) * 3));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  // create cube array
  vec3 cubePositions[] = {{0.0f, 0.0f, 0.0f},    {2.0f, 5.0f, -15.0f},
                          {-1.5f, -2.2f, -2.5f}, {-3.8f, -2.0f, -12.3f},
                          {2.4f, -0.4f, -3.5f},  {-1.7f, 3.0f, -7.5f},
                          {1.3f, -2.0f, -2.5f},  {1.5f, 2.0f, -2.5f},
                          {1.5f, 0.2f, -1.5f},   {-1.3f, 1.0f, -1.5f}};

  // render loop
  glEnable(GL_DEPTH_TEST);

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (floorf(glfwGetTime() / 5) < 1) {
      glBindBuffer(GL_ARRAY_BUFFER, VBO);
      glBufferData(GL_ARRAY_BUFFER, 288 * sizeof(float), verts1,
                   GL_DYNAMIC_DRAW);
    } else {
      printf("hit");
      glBindBuffer(GL_ARRAY_BUFFER, VBO);
      glBufferData(GL_ARRAY_BUFFER, 48 * sizeof(float), verts2,
                   GL_DYNAMIC_DRAW);
    }

    // draw triangles
    glBindTexture(GL_TEXTURE_2D, texture);

    // transform vertecies
    glUseProgram(shaderProgram);

    glBindVertexArray(VAO);
    for (int i = 0; i < 10; i++) {
      mat4 model;
      mat4 trans;
      mat4 rot;
      mat4 scale;
      genTranslationMat4(cubePositions[i][0], cubePositions[i][1],
                         cubePositions[i][2], trans);
      // genRotationMat4(glfwGetTime(), glfwGetTime() * .5, glfwGetTime()
      // * 1.5,
      //                 rot);
      genRotationMat4(0, 0, 0, rot);
      genScaleMat4(1, 1, 1, 1, scale);
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
      // genOrthographicMat(0, 600, 0, 800, .1, 100, proj);
      genPerspectiveMat(45, 800.0f / 600.0f, .1, 100, proj);
      int modelLoc = glGetUniformLocation(shaderProgram, "model");
      glUniformMatrix4fv(modelLoc, 1, GL_FALSE, convertMat4ToArr(model));
      int viewLoc = glGetUniformLocation(shaderProgram, "view");
      glUniformMatrix4fv(viewLoc, 1, GL_FALSE, convertMat4ToArr(view));
      int projLoc = glGetUniformLocation(shaderProgram, "proj");
      glUniformMatrix4fv(projLoc, 1, GL_FALSE, convertMat4ToArr(proj));

      glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    //    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwTerminate();

  return 0;
}
