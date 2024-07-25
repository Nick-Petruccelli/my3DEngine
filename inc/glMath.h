#ifndef GLMATH_H
#define GLMATH_H
#endif

typedef float mat2[2][2];
typedef float mat3[3][3];
typedef float mat4[4][4];
typedef float vec2[2];
typedef float vec3[3];
typedef float vec4[4];

float *convertMat4ToArr(mat4 mat);
void copyVec2(vec2 src, vec2 dest);
void copyVec3(vec3 src, vec3 dest);
void copyVec4(vec4 src, vec4 dest);

void genIdentityMat2(mat2 mat);
void genIdentityMat3(mat3 mat);
void genIdentityMat4(mat4 mat);

void genRoatationMat2(float theta, mat2 mat);
void genRoatationMat3(float x, float y, float z, mat3 mat);
void genRotationMat4(float x, float y, float z, mat4 mat);

void genTranslationMat3(float x, float y, mat3 mat);
void genTranslationMat4(float x, float y, float z, mat4 mat);

void genScaleMat2(float x, float y, mat2 mat);
void genScaleMat3(float x, float y, float z, mat3 mat);
void genScaleMat4(float x, float y, float z, float w, mat4 mat);

void genModelMat(mat4 transMat, mat4 rotMat, mat4 scaleMat, mat4 outMat);
void genModelMatV(vec3 trans, vec3 rot, vec3 scale, mat4 out);
void genViewMat(mat4 transMat, mat4 rotMat, mat4 outMat);
void genViewMatV(vec3 trans, vec3 rot, mat4 outMat);
void genPerspectiveMat(float fov, float aspectRatio, float nearPlane,
                       float farPlane, mat4 out);
void genOrthographicMat(float r, float l, float t, float b, float n, float f,
                        mat4 out);

void multiplyMatVec2(mat2 mat, vec2 vecIn, vec2 vecOut);
void multiplyMatVec3(mat3 mat, vec3 vecIn, vec3 vecOut);
void multiplyMatVec4(mat4 mat, vec4 vec, vec3 vecOut);

void rotateVec2(float theta, vec2 vec, vec2 vecOut);
void rotateVec3(float x, float y, float z, vec3 vecIn, vec3 vecOut);
void rotateVec4(float x, float y, float z, float w, vec4 vecIn, vec4 vecOut);

void translateVec2(float x, float y, vec2 vecIn, vec2 vecOut);
void translateVec3(float x, float y, float z, vec3 vecIn, vec3 vecOut);
void translateVec4(float x, float y, float z, float w, vec4 vecIn, vec4 vecOut);

void scaleVec2(float x, float y, vec2 vecIn, vec2 vecOut);
void scaleVec3(float x, float y, float z, vec3 vecIn, vec3 vecOut);
void scaleVec4(float x, float y, float z, float w, vec4 vecIn, vec4 vecOut);

void multiplyMats2(mat2 lmat, mat2 rmat, mat2 matOut);
void multiplyMats3(mat3 lmat, mat3 rmat, mat3 matOut);
void multiplyMats4(mat4 lmat, mat4 rmat, mat4 matOut);

void crossProduct3(vec3 left, vec3 right, vec3 out);
void normalizeVec3(vec3 in, vec3 out);
