#include "../inc/glMath.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

void testMultiplyMatVec4(void) {
  mat4 mat = {{2, 0, 0, 0}, {0, 3, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
  vec4 vec = {4, 8, 10, 5};
  vec4 expected = {8, 24, 10, 5};
  vec4 acctual;
  multiplyMatVec4(mat, vec, acctual);
  bool passed = true;

  for (int i = 0; i < 4; i++) {
    if (fabsf(acctual[i] - expected[i]) > .0001) {
      passed = false;
      break;
    }
  }

  if (passed) {
    printf("Test multiplyMatVec4: PASSED\n");
  } else {
    printf("Test multiplyMatVec4: FAILED\n");
  }
}

void testMultiplyMatVec3(void) {
  mat3 mat = {{2, 5, 3}, {2, 3, 8}, {20, 0, 4.5}};
  vec3 vec = {4, 8.99, 10};
  vec3 acctual;
  multiplyMatVec3(mat, vec, acctual);
  vec3 expected = {225.98, 46.97, 128.92};
  bool passed = true;

  for (int i = 0; i < 3; i++) {
    if (fabsf(acctual[i] - expected[i]) > .0001) {
      passed = false;
      break;
    }
  }

  if (passed) {
    printf("Test multiplyMatVec3: PASSED\n");
  } else {
    printf("Test multiplyMatVec3: FAILED\n");
  }
}

int main() {
  testMultiplyMatVec4();
  testMultiplyMatVec3();
}
