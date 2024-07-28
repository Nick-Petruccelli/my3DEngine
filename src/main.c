#include "../inc/assetManager.h"
#include "../inc/camera.h"
#include "../inc/glMath.h"
#include "../inc/glad.h"
#include "../inc/my3DEngine.h"
#include "../inc/renderer.h"
#include "../inc/sceneManager.h"
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
  unsigned int objShader =
      createShader("./src/shaders/vertex.glsl", "./src/shaders/objFrag.glsl");
  unsigned int lightShader =
      createShader("./src/shaders/vertex.glsl", "./src/shaders/lightFrag.glsl");

  // set the texture wrapping parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // create texture object
  unsigned int texture = generateTexture("box.png");

  // create list of verticies to render
  float *cubeData = loadCubeData();

  initAssetManager(2);
  vec3 camPos = {0, 0, 10};
  vec3 origin = {0, 0, 0};
  Camera *cam = initCamera(camPos, origin, 45);
  Scene *mainScene = initScene(10, cam);
  int cubeMeshID = addAsset(cubeData, 36, GL_STATIC_DRAW);
  vec3 cubePos = {1, 0, 3};
  vec3 cubeRot = {1.2, 3.2, .43};
  vec3 cubeScale = {1, 1, 1};
  addSceneObject(mainScene, cubePos, cubeRot, cubeScale, cubeMeshID);

  vec3 lightColor = {1, 1, 1};
  vec3 lightPos = {0, 2, 0};
  vec3 lightRot = {1.2, 3.2, .43};
  vec3 lightScale = {.2, .2, .2};
  addSceneLight(mainScene, lightColor, lightPos, lightRot, lightScale,
                cubeMeshID);

  // render loop
  glEnable(GL_DEPTH_TEST);

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // move Camera
    camPos[0] = sinf(glfwGetTime()) * 10;
    camPos[2] = cosf(glfwGetTime()) * 10;
    camMove(cam, camPos);

    // draw triangles
    glBindTexture(GL_TEXTURE_2D, texture);
    render(mainScene, objShader, lightShader);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  deleteScene(mainScene);
  deleteAssetManager();
  glfwTerminate();

  return 0;
}
