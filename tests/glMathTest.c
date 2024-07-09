#include "../inc/glMath.h"
#include <stdbool.h>
#include <stdio.h>

int main() {
  mat4 mat = {{2, 0, 0, 0}, {0, 3, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
  vec4 vec = {4, 8, 10, 5};
  vec4 expected = {8, 24, 10, 5};
  vec4 *acctual = multiplyMatVec4(mat, vec);
  bool passed = true;

  for (int i = 0; i < 4; i++) {
    if (*acctual[i] != expected[i]) {
      passed = false;
      break;
    }
  }

  if (passed) {
    printf("Test multiplyMatVec4 1: FAILED\n");
  } else {
    printf("Test multiplyMatVec4 1: PASSED\n");
  }
}
