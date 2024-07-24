#include "../inc/assetManager.h"
#include "../inc/glMath.h"
#include "../inc/glad.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

MeshInfoArray MIA;

void initAssetManager(int numMeshes) {
  MIA.meshInfo = malloc(sizeof(MeshInfo) * numMeshes);
  MIA.len = 0;
  MIA.size = numMeshes;
}

int addAsset(float *assetData, unsigned int assetVerts, GLenum usage) {
  if (MIA.len > MIA.size) {
    MeshInfo *temp = realloc(MIA.meshInfo, MIA.size * 2 * sizeof(float));
    if (temp == NULL) {
      printf("ERROR::ASSETMANAGER::ADDASSET\nFailed to reallocate memory for "
             "MeshInfoArray\n");
      return -1;
    }
    MIA.meshInfo = temp;
  }
  unsigned int VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  int size = 0;
  while (assetData[size] != '\0') {
    size++;
  }
  glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), assetData, usage);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8,
                        (void *)(sizeof(float) * 3));
  glEnableVertexAttribArray(1);

  MeshInfo meshInfo = MIA.meshInfo[MIA.len];
  meshInfo.vao = VAO;
  meshInfo.numVerts = size / 8;
  meshInfo.meshID = MIA.len;
  MIA.len++;

  glBindVertexArray(0);
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  return 0;
}

float *loadPlaneDataa() {
  static float data[] = {-0.500000, -0.500000, 0.000000, 0.000000, 0.000000,
                         0.500000,  -0.500000, 0.000000, 1.000000, 0.000000,
                         0.500000,  0.500000,  0.000000, 1.000000, 1.000000,
                         0.500000,  0.500000,  0.000000, 1.000000, 1.000000,
                         -0.500000, 0.500000,  0.000000, 0.000000, 1.000000,
                         -0.500000, -0.500000, 0.000000, 0.000000, 0.000000};

  return data;
}

float *loadCubeData(vec3 color) {
  static float data[] = {
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

  return data;
}
