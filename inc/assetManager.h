#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H
#include <stdint.h>
#endif

#include "linkedList.h"
#include <stdbool.h>

typedef struct StaticAssetArray {
  float *assetData;
  uint8_t dataPerVert;
  unsigned int len;
  unsigned int size;
} StaticAssetArray;

typedef struct {
  bool dynamic;
  int arrID;
  unsigned int arrOffset;
  unsigned int numDataPoints;
  LinkedList entities;
} MeshInfo;

typedef struct MeshInfoArray {
  MeshInfo *meshInfo;
  unsigned int len;
  unsigned int size;
} MeshInfoArray;
