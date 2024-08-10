#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H
#include <stdint.h>

#include "glMath.h"
#include "glad.h"
#include "linkedList.h"
#include <stdbool.h>

typedef struct MeshInfo {
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

typedef struct Material {
  unsigned int diffMap;
  unsigned int specMap;
  float shininess;
} Material;

extern MeshInfoArray MIA;
extern unsigned int lightVAO;

void initAssetManager(unsigned int numMeshes);
void deleteAssetManager();
int addAsset(float *assetData, unsigned int assetVerts, GLenum usage);
Material createMaterial(unsigned int diffMap, unsigned int specMap,
                        float shininess);

float *loadPlaneData();
float *loadCubeData();
#endif
