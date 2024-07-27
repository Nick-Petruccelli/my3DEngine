#ifndef CAMERA_H
#define CAMERA_H

#include "glMath.h"

typedef struct Camera {
  vec3 position;
  vec3 target;
  float fov;
} Camera;

Camera *initCamera(vec3 pos, vec3 target, float fov);
void deleteCamera(Camera *cam);

void lookAt(Camera *cam, vec3 up, mat4 view);
void camMove(Camera *cam, vec3 newPos);
void camTargetUpdate(Camera *cam, vec3 newTarget);
#endif
