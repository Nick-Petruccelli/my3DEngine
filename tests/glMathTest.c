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
    if (fabsf(acctual[i] - expected[i]) > .001) {
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

void testMultiplyMats4(void) {
  mat4 lmat = {{12, 43.2, 65.33, 10},
               {32.43, 23.23, 32.12, 30},
               {23.12, 0, 42.23223532, 23},
               {96, 9, 20, 5}};
  mat4 rmat = {{3.245, 34.32, 42.534, 32.4},
               {14.123, 33.2, 32, 52.2},
               {34.3, 32, 23.34, 32},
               {33.2, 87.76, 54.54, 99}};
  mat4 acctual;
  mat4 expected = {{5245.72368, 1229.0376, 3758.66014710088, 2202.332},
                   {6997.192, 1851.1496, 4384.47112024, 2134.23},
                   {5060.9808, 2513.12, 4894.3593723688, 1999.82},
                   {14009.4216, 4363.9048, 9271.1533143528, 4714.22}};
  multiplyMats4(lmat, rmat, acctual);
  bool passed = true;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (fabsf(acctual[i][j] - expected[i][j]) > .01) {
        printf("Failed at pos [%d][%d] with\nacctual: %f expected %f\n\n", i, j,
               acctual[i][j], expected[i][j]);
        passed = false;
        break;
      }
    }
    if (!passed)
      break;
  }

  if (passed) {
    printf("Test multiplyMats4: PASSED\n");
  } else {
    printf("Test multiplyMats4: FAILED\n");
  }
}

void testCrossProduct3() {
  vec3 left = {4, 5, 10};
  vec3 right = {2, 8, 4};
  vec3 acctual;
  vec3 expected = {-60, 4, 22};
  crossProduct3(left, right, acctual);
  bool passed = true;

  for (int i = 0; i < 3; i++) {
    if (acctual[i] != expected[i]) {
      passed = false;
      break;
    }
  }

  if (passed) {
    printf("Test crossProduct3: PASSED\n");
  } else {
    printf("Test crossProduct3: FAILED\n");
  }
}

void testNormalizeVec3() {
  vec3 in = {4, 2, 5};
  vec3 acctual;
  vec3 expected = {0.596285, 0.298142, 0.745356};
  bool passed = true;

  normalizeVec3(in, acctual);
  for (int i = 0; i < 3; i++) {
    if (fabsf(expected[i] - acctual[i]) > .01) {
      passed = false;
      break;
    }
  }

  if (passed) {
    printf("Test normalizeVec3: PASSED\n");
  } else {
    printf("Test normalizeVec3: FAILED\n");
  }
}

int main() {
  testMultiplyMatVec4();
  testMultiplyMatVec3();
  testMultiplyMats4();
  testCrossProduct3();
  testNormalizeVec3();
}
