#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H
#include <stdint.h>
#endif

#include "linkedList.h"
#include <stdbool.h>

typedef struct {
  unsigned int vao;
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
