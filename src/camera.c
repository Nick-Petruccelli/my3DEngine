#include "../inc/camera.h"
#include <stdio.h>
#include <stdlib.h>

Camera *initCamera(vec3 pos, vec3 target, float fov) {
  Camera *cam = malloc(sizeof(Camera));
  copyVec3(pos, cam->position);
  copyVec3(target, cam->target);
  cam->fov = fov;

  return cam;
}

void lookAt(vec3 camPos, vec3 target, vec3 up, mat4 view) {
  vec3 zaxis;
  vec3 xaxis;
  vec3 yaxis;

  vec3 temp;
  for (int i = 0; i < 3; i++) {
    temp[i] = camPos[i] - target[i];
  }

  normalizeVec3(temp, zaxis);
  crossProduct3(up, zaxis, temp);
  normalizeVec3(temp, xaxis);

  crossProduct3(zaxis, xaxis, yaxis);

  mat4 left;
  genIdentityMat4(left);
  mat4 right;
  genIdentityMat4(right);
  for (int i = 0; i < 3; i++) {
    left[i][0] = xaxis[i];
    left[i][1] = yaxis[i];
    left[i][2] = zaxis[i];
    right[3][i] = -camPos[i];
  }

  multiplyMats4(left, right, view);
}
