#include "../inc/glMath.h"
#include <math.h>
#include <stdlib.h>

float *convertMat4ToArr(mat4 mat) {
  float *arr = malloc(sizeof(float) * 16);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      arr[(i * 4) + j] = mat[i][j];
    }
  }

  return arr;
}

void genIdentityMat2(mat2 mat) {
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      if (i == j) {
        mat[i][j] = 1;
      } else {
        mat[i][j] = 0;
      }
    }
  }
}

void genIdentityMat3(mat3 mat) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (i == j) {
        mat[i][j] = 1;
      } else {
        mat[i][j] = 0;
      }
    }
  }
}

void genIdentityMat4(mat4 mat) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (i == j) {
        mat[i][j] = 1;
      } else {
        mat[i][j] = 0;
      }
    }
  }
}

void genRoatationMat2(float theta, mat2 mat) {
  mat2 rotMat = {{cosf(theta), sinf(theta)}, {-sinf(theta), cosf(theta)}};

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      mat[i][j] = rotMat[i][j];
    }
  }
}

void genRoatationMat3(float x, float y, float z, mat3 mat) {
  mat3 rotMat = {
      {cosf(z) * cosf(y), cosf(y) * sinf(z), -sinf(y)},
      {sinf(x) * sinf(y) * cosf(z) - cosf(x) * sinf(z),
       sinf(z) * sinf(y) * sinf(x) + cosf(z) * cosf(x), sinf(x) * cosf(y)},
      {cosf(x) * sinf(y) * cosf(z) + sinf(x) * sinf(z),
       cosf(x) * sinf(y) * sinf(z) - sinf(x) * cosf(z), cosf(x) * cosf(y)}};

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      mat[i][j] = rotMat[i][j];
    }
  }
}

void genRotationMat4(float x, float y, float z, mat4 mat) {
  mat4 rotMat = {
      {cosf(z) * cosf(y), cosf(y) * sinf(z), -sinf(y), 0},
      {sinf(x) * sinf(y) * cosf(z) - cosf(x) * sinf(z),
       sinf(z) * sinf(y) * sinf(x) + cosf(z) * cosf(x), sinf(x) * cosf(y), 0},
      {cosf(x) * sinf(y) * cosf(z) + sinf(x) * sinf(z),
       cosf(x) * sinf(y) * sinf(z) - sinf(x) * cosf(z), cosf(x) * cosf(y), 0},
      {0, 0, 0, 1}};

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      mat[i][j] = rotMat[i][j];
    }
  }
}

void genTranslationMat3(float x, float y, mat3 mat) {
  genIdentityMat3(mat);

  mat[2][0] = x;
  mat[2][1] = y;
}

void genTranslationMat4(float x, float y, float z, mat4 mat) {
  genIdentityMat4(mat);

  mat[3][0] = x;
  mat[3][1] = y;
  mat[3][2] = z;
}

void genScaleMat2(float x, float y, mat2 mat) {
  genIdentityMat2(mat);

  mat[0][0] = x;
  mat[1][1] = y;
}

void genScaleMat3(float x, float y, float z, mat3 mat) {
  genIdentityMat3(mat);

  mat[0][0] = x;
  mat[1][1] = y;
  mat[2][2] = z;
}

void genScaleMat4(float x, float y, float z, float w, mat4 mat) {
  genIdentityMat4(mat);

  mat[0][0] = x;
  mat[1][1] = y;
  mat[2][2] = z;
  mat[3][3] = w;
}

void genModelMat(mat4 trans, mat4 rot, mat4 scale, mat4 out) {
  mat4 temp;
  multiplyMats4(trans, rot, temp);
  multiplyMats4(scale, temp, out);
}

void genViewMat(mat4 trans, mat4 rot, mat4 out) {
  multiplyMats4(trans, rot, out);
}

void genPerspectiveMat(float fov, float aspectRatio, float near, float far,
                       mat4 out) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      out[i][j] = 0;
    }
  }

  const float DEG2RAD = acos(-1.0f) / 180;

  float tangent = tan(fov / 2 * DEG2RAD); // tangent of half fovX
  float right = near * tangent;           // half width of near plane
  float top = right / aspectRatio;        // half height of near plane

  // params: left, right, bottom, top, near(front), far(back)
  out[0][0] = near / right;
  out[1][1] = near / top;
  out[2][2] = -(far + near) / (far - near);
  out[2][3] = -1;
  out[3][2] = -(2 * far * near) / (far - near);
}

void genOrthographicMat(float r, float l, float t, float b, float n, float f,
                        mat4 out) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      out[i][j] = 0;
    }
  }

  out[0][0] = 2 / (r - l);
  out[1][1] = 2 / (t - b);
  out[2][2] = -2 / (f - n);
  out[3][0] = -((r + l) / (r - l));
  out[3][1] = -((t + b) / (t - b));
  out[3][2] = -((f + n) / (f - n));
  out[3][3] = 1;
}

void multiplyMatVec2(mat2 matrix, vec2 vecIn, vec2 vecOut) {
  vecOut[0] = matrix[0][0] * vecIn[0] + matrix[1][0] * vecIn[0];
  vecOut[1] = matrix[1][1] * vecIn[1] + matrix[2][1] * vecIn[1];
}

void multiplyMatVec3(mat3 matrix, vec3 vecIn, vec3 vecOut) {
  vecOut[0] = matrix[0][0] * vecIn[0] + matrix[1][0] * vecIn[1] +
              matrix[2][0] * vecIn[2];
  vecOut[1] = matrix[0][1] * vecIn[0] + matrix[1][1] * vecIn[1] +
              matrix[2][1] * vecIn[2];
  vecOut[2] = matrix[0][2] * vecIn[0] + matrix[1][2] * vecIn[1] +
              matrix[2][2] * vecIn[2];
}

void multiplyMatVec4(mat4 mat, vec4 vecIn, vec4 vecOut) {
  vecOut[0] = mat[0][0] * vecIn[0] + mat[1][0] * vecIn[1] +
              mat[2][0] * vecIn[2] + mat[3][0] * vecIn[3];
  vecOut[1] = mat[0][1] * vecIn[0] + mat[1][1] * vecIn[1] +
              mat[2][1] * vecIn[2] + mat[3][1] * vecIn[3];
  vecOut[2] = mat[0][2] * vecIn[0] + mat[1][2] * vecIn[1] +
              mat[2][2] * vecIn[2] + mat[3][2] * vecIn[3];
  vecOut[3] = mat[0][3] * vecIn[0] + mat[1][3] * vecIn[1] +
              mat[2][3] * vecIn[2] + mat[3][3] * vecIn[3];
}

void rotateVec2(float theta, vec2 vecIn, vec2 vecOut) {
  mat2 rotationMatrix = {{cosf(theta), sinf(theta)},
                         {-sinf(theta), cosf(theta)}};
  multiplyMatVec2(rotationMatrix, vecIn, vecOut);
}

void rotateVec3(float x, float y, float z, vec3 vecIn, vec3 vecOut) {
  mat3 rotationMatrix = {
      {cosf(z) * cosf(y), cosf(y) * sinf(z), -sinf(y)},
      {sinf(x) * sinf(y) * cosf(z) - cosf(x) * sinf(z),
       sinf(x) * sinf(y) * cosf(z) + cosf(x) * sinf(z), sinf(x) * cosf(y)},
      {cosf(x) * sinf(y) * cosf(z) + sinf(x) * sinf(z),
       cosf(x) * sinf(y) * cosf(z) - sinf(x) * sinf(z), cosf(x) * cosf(y)}};
  multiplyMatVec3(rotationMatrix, vecIn, vecOut);
}

void rotateVec4(float x, float y, float z, float w, vec4 vecIn, vec4 vecOut) {
  mat4 rotationMatrix = {
      {cosf(z) * cosf(y), cosf(y) * sinf(z), -sinf(y), 0},
      {sinf(x) * sinf(y) * cosf(z) - cosf(x) * sinf(z),
       sinf(x) * sinf(y) * cosf(z) + cosf(x) * sinf(z), sinf(x) * cosf(y), 0},
      {cosf(x) * sinf(y) * cosf(z) + sinf(x) * sinf(z),
       cosf(x) * sinf(y) * cosf(z) - sinf(x) * sinf(z), cosf(x) * cosf(y), 0},
      {0, 0, 0, 1}};
  multiplyMatVec4(rotationMatrix, vecIn, vecOut);
}

void translateVec2(float x, float y, float *vecIn, float *vecOut) {
  vecOut[0] = vecIn[0] + x;
  vecOut[1] = vecIn[1] + y;
}

void translateVec3(float x, float y, float z, float *vecIn, float *vecOut) {
  vecOut[0] = vecIn[0] + x;
  vecOut[1] = vecIn[1] + y;
  vecOut[2] = vecIn[2] + z;
}

void translateVec4(float x, float y, float z, float w, float *vecIn,
                   float *vecOut) {
  vecOut[0] = vecIn[0] + x;
  vecOut[1] = vecIn[1] + y;
  vecOut[2] = vecIn[2] + z;
  vecOut[3] = vecIn[3] + w;
}

void scaleVec2(float x, float y, float *vecIn, float *vecOut) {
  vecOut[0] = vecIn[0] * x;
  vecOut[1] = vecIn[1] * y;
}

void scaleVec3(float x, float y, float z, float *vecIn, float *vecOut) {
  vecOut[0] = vecIn[0] * x;
  vecOut[1] = vecIn[1] * y;
  vecOut[2] = vecIn[2] * z;
}

void scaleVec4(float x, float y, float z, float w, float *vecIn,
               float *vecOut) {
  vecOut[0] = vecIn[0] * x;
  vecOut[1] = vecIn[1] * y;
  vecOut[2] = vecIn[2] * z;
  vecOut[3] = vecIn[3] * w;
}

void multiplyMats2(mat2 lmat, mat2 rmat, mat2 outMat) {
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      outMat[i][j] = 0;
      for (int k = 0; k < 2; k++) {
        outMat[i][j] += lmat[k][j] * rmat[i][k];
      }
    }
  }
}

void multiplyMats3(mat3 lmat, mat3 rmat, mat3 outMat) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      outMat[i][j] = 0;
      for (int k = 0; k < 3; k++) {
        outMat[i][j] += lmat[k][j] * rmat[i][k];
      }
    }
  }
}

void multiplyMats4(mat4 lmat, mat4 rmat, mat4 outMat) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      outMat[i][j] = 0;
      for (int k = 0; k < 4; k++) {
        outMat[i][j] += lmat[k][j] * rmat[i][k];
      }
    }
  }
}

void crossProduct3(vec3 left, vec3 right, vec3 out) {
  out[0] = left[1] * right[2] - left[2] * right[1];
  out[1] = -1 * left[0] * right[2] + left[2] * right[0];
  out[2] = left[0] * right[1] - left[1] * right[0];
}
