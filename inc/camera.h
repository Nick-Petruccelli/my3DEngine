#ifndef CAMERA_H
#define CAMERA_H

#include "glMath.h"

typedef struct Camera {
  vec3 position;
  vec3 target;
  float fov;
} Camera;

Camera *initCamera(vec3 pos, vec3 target, float fov);

void lookAt(vec3 camPos, vec3 target, vec3 up, mat4 view);
#endif
