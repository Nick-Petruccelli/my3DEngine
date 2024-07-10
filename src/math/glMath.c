#include "../../inc/glMath.h"
#include <math.h>
#include <stdio.h>

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
