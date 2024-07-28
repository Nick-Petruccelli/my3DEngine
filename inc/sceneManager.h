#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "camera.h"
#include "glMath.h"

typedef struct SceneObject {
  unsigned int objID;
  vec3 position;
  vec3 rotation;
  vec3 scale;
  unsigned int meshID;
} SceneObject;

typedef struct SceneLight {
  unsigned int lightID;
  vec3 color;
  vec3 position;
  vec3 rotation;
  vec3 scale;
  unsigned int meshID;
} SceneLight;

typedef struct IDQueue {
  unsigned int head;
  unsigned int tail;
  unsigned int *queue;
  unsigned int len;
  unsigned int size;
} IDQueue;

typedef struct Scene {
  SceneObject *sceneObjects;
  unsigned int numObjects;
  unsigned int sceneObjectsSize;
  IDQueue *nextObjID;
  SceneLight *sceneLights;
  unsigned int numLights;
  unsigned int sceneLightsSize;
  IDQueue *nextLightID;
  Camera *camera;
} Scene;

IDQueue *createQueue(unsigned int size);
int resizeQueue(IDQueue *q, unsigned int size);
int queuePush(IDQueue *q, unsigned int num);
unsigned int queuePop(IDQueue *q);
Scene *initScene(unsigned int size, Camera *cam);
unsigned int addSceneObject(Scene *scene, vec3 pos, vec3 rot, vec3 scale,
                            unsigned int meshID);
void removeSceneObject(Scene scene, unsigned int objID);
unsigned int addSceneLight(Scene *scene, vec3 color, vec3 pos, vec3 rot,
                           vec3 scale, unsigned int meshID);
void removeSceneLight(Scene scene, unsigned int lightID);
void deleteScene(Scene *scene);
#endif
