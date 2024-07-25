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
  IDQueue *nextIDQueue;
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
#endif
