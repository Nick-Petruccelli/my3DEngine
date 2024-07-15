#include "../inc/my3DEngine.h"
#include <stdio.h>

void testLoadPlaneData() {
  printf("load plane test\n\n");
  vec3 color = {1, 2, 3};
  float *data = loadPlaneData(color);

  for (int i = 0; i < 6; i++) {
    printf("%d:\t", i);
    for (int j = 0; j < 8; j++) {
      printf("%f ", data[(i * 8) + j]);
    }
    printf("\n");
  }
}

void testLoadCubeData() {
  printf("load cube test\n\n");
  vec3 color = {1, 2, 3};
  float *data = loadCubeData(color);

  for (int i = 0; i < 36; i++) {
    printf("%d:\t", i);
    for (int j = 0; j < 8; j++) {
      printf("%f ", data[(i * 8) + j]);
    }
    printf("\n");
  }
}
void my3DEngineTest() {
  testLoadPlaneData();
  testLoadCubeData();
}
