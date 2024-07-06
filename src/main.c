#include "../glad/glad.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

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

  // create list of verticies to render
  float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};

  // create vertex buffer object
  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  // load verticies data into vbo
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // load in vertex shader
  FILE *vertexShaderFile = fopen("./src/shaders/vertex.glsl", "r");
  if (vertexShaderFile == NULL) {
    printf("Failed to open vertex shader source file\n");
    fclose(vertexShaderFile);
    return -1;
  }
  fseek(vertexShaderFile, 0L, SEEK_END);
  int size = ftell(vertexShaderFile);
  rewind(vertexShaderFile);
  char *vertexShaderSource = malloc(sizeof(char) * size);
  int i = 0;
  char c;
  while ((c = fgetc(vertexShaderFile)) != EOF) {
    vertexShaderSource[i] = c;
    i++;
  }
  fclose(vertexShaderFile);

  // create shader object from source code
  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infoLog);
  }

  // render loop
  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwTerminate();

  return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}
