#include "../glad/glad.h"
#include <GLFW/glfw3.h>
#include <stdio.h>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

int main() {
  // window settings init
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // create window
  GLFWwindow *window = glfwCreateWindow(800, 600, "my3DEngine", NULL, NULL);
  if (window == NULL) {
    printf("Error Createing Window");
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  // initilize openGL function pointers with glad
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    printf("Error loading GLAD.");
    return -1;
  }

  // init opengl viewport
  glViewport(0, 0, 800, 600);

  // set up window resizing
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // render loop
  while (!glfwWindowShouldClose(window)) {
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwTerminate();

  return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}
