#include "../../inc/glMath.h"

vec2 *multiplyMatVec2(mat2 matrix, vec2 vector) {
  static vec2 out;
  out[0] = matrix[0][0] * vector[0] + matrix[1][0] * vector[0];
  out[1] = matrix[1][1] * vector[1] + matrix[2][1] * vector[1];
  return &out;
}

vec3 *multiplyMatVec3(mat3 matrix, vec3 vector) {
  static vec3 out;
  out[0] = matrix[0][0] * vector[0] + matrix[1][0] * vector[0] +
           matrix[2][0] * vector[0];
  out[1] = matrix[0][1] * vector[1] + matrix[1][1] * vector[1] +
           matrix[2][1] * vector[1];
  out[2] = matrix[0][2] * vector[1] + matrix[1][2] * vector[1] +
           matrix[2][2] * vector[1];
  return &out;
}

vec4 *multiplyMatVec4(mat4 mat, vec4 vec) {
  static vec4 out;
  out[0] = mat[0][0] * vec[0] + mat[1][0] * vec[1] + mat[2][0] * vec[2] +
           mat[3][0] * vec[3];
  out[1] = mat[0][1] * vec[0] + mat[1][1] * vec[1] + mat[2][1] * vec[2] +
           mat[3][1] * vec[3];
  out[2] = mat[0][2] * vec[0] + mat[1][2] * vec[1] + mat[2][2] * vec[2] +
           mat[3][2] * vec[3];
  out[3] = mat[0][3] * vec[0] + mat[1][3] * vec[1] + mat[2][3] * vec[2] +
           mat[3][3] * vec[3];
  return &out;
}

mat2 *rotateMat2(mat2 matrix) {}

mat3 *rotateMat3(mat3 matrix) {}

mat4 *rotateMat4(mat4 matrix) {}
