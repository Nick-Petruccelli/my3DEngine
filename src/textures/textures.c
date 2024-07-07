#define STB_IMAGE_IMPLEMENTATION
#include "../../glad/glad.h"
#include "../../inc/stb_image.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define textureFolderPath "./resources/"

unsigned int generateTexture(char *textureName) {
  int width, height, nrcolors;
  char *filePath;
  if ((filePath = malloc(strlen(textureFolderPath) + strlen(textureName) +
                         1)) != NULL) {
    filePath[0] = '\0';
    strcat(filePath, textureFolderPath);
    strcat(filePath, textureName);
  } else {
    printf("ERROR::TEXTURE::LOADING\nPath memory allocation failed\n");
    return 0;
  }

  unsigned char *data =
      stbi_load(filePath, &width, &height, &nrcolors, STBI_rgb_alpha);
  free(filePath);

  if (data == NULL) {
    printf("ERROR::TEXTURE::LOADING\nFailed to load texture image data\n");
    return 0;
  }
  unsigned int texture;
  glGenTextures(1, &texture);

  glBindTexture(GL_TEXTURE_2D, texture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);
  stbi_image_free(data);
  glBindTexture(GL_TEXTURE_2D, 0);

  return texture;
}
