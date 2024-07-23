#include "../inc/assetManager.h"
#include "../inc/glMath.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

StaticAssetArray *SAA;
unsigned int nextArrID;
MeshInfoArray MIA;

void initAssetManager(int numStaticArrs, int numMeshes) {
  SAA = malloc(sizeof(StaticAssetArray) * numStaticArrs);
  nextArrID = 0;
  MIA.meshInfo = malloc(sizeof(MeshInfo) * numMeshes);
  MIA.len = 0;
  MIA.size = numMeshes;
}

int createStaticAssetArray(unsigned int size, uint8_t dataPerVert) {
  SAA[nextArrID].assetData = malloc(sizeof(float) * size);
  if (SAA == NULL) {
    printf("ERROR::ASSETMANAGER::CREATESTATICASSETARRAY\nfailed to alocate "
           "memory for SAA\n");
    return NULL;
  }
  nextArrID++;
  return nextArrID - 1;
}

int addAsset(unsigned int arrID, float *assetData, bool dynamic) {
  unsigned int offset = SAA[arrID].len;
  unsigned int i = 0;
  while (assetData[i] != '\0') {
    if (offset + i > SAA[arrID].size) {
      float *temp = realloc(SAA[arrID].assetData,
                            SAA[arrID].size * sizeof(StaticAssetArray) * 2);
      if (temp == NULL) {
        printf("ERROR::ASSETMANAGER::ADDASSET\nfailed to realocate memory for "
               "SAA %d\n",
               arrID);
        return -1;
      }
      SAA[arrID].assetData = temp;
    }
    SAA[arrID].assetData[offset + i] = assetData[i];
    i++;
  }

  if (MIA.len == MIA.size) {
    MeshInfo *temp;
    temp = realloc(MIA.meshInfo, MIA.size * sizeof(MeshInfo) * 2);
    if (temp == NULL) {
      printf("ERROR::ASSETMANAGER::ADDASSET\nfailed to realocate memory for "
             "MIA\n");
      return -1;
    }
    MIA.meshInfo = temp;
  }

  SAA[arrID].len += i;
  MeshInfo meshInfo;
  meshInfo.dynamic = dynamic;
  meshInfo.arrID = arrID;
  meshInfo.arrOffset = offset;
  meshInfo.numDataPoints = i;

  MIA.meshInfo[MIA.len] = meshInfo;
  MIA.len++;
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
