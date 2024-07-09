#ifndef GLMATH_H
#define GLMATH_H
#endif

typedef float mat2[2][2];
typedef float mat3[3][3];
typedef float mat4[4][4];
typedef float vec2[2];
typedef float vec3[3];
typedef float vec4[4];

vec2 *multiplyMatVec2(mat2 mat, vec2 vec);
vec3 *multiplyMatVec3(mat3 mat, vec3 vec);
vec4 *multiplyMatVec4(mat4 mat, vec4 vec);

mat2 *rotateMat2(mat2 matrix);
mat3 *rotateMat3(mat3 matrix);
mat4 *rotateMat4(mat4 matrix);
