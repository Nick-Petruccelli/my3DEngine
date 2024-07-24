#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H
#include <stdint.h>
#endif

#include "glMath.h"
#include "glad.h"
#include "linkedList.h"
#include <stdbool.h>

typedef struct {
  unsigned int vao;
  unsigned int vbo;
  bool dynamic;
  int meshID;
  unsigned int numVerts;
} MeshInfo;

typedef struct MeshInfoArray {
  MeshInfo *meshInfo;
  unsigned int len;
  unsigned int size;
} MeshInfoArray;

extern MeshInfoArray MIA;

void initAssetManager(unsigned int numMeshes);
int addAsset(float *assetData, unsigned int assetVerts, GLenum usage);

float *loadPlaneData();
float *loadCubeData();
