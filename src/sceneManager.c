#include "../inc/sceneManager.h"
#include "../inc/glMath.h"
#include <limits.h>
#include <stdlib.h>

IDQueue *createQueue(unsigned int size) {
  IDQueue *q;
  q->queue = malloc(size * sizeof(unsigned int));
  q->head = 0;
  q->tail = 0;
  q->len = 0;
  q->size = size;

  return q;
}

int resizeQueue(IDQueue *q, unsigned int size) {
  IDQueue *nq;
  nq->queue = malloc(size * sizeof(unsigned int));
  if (nq == NULL) {
    return -1;
  }
  int i = 0;
  while (q->head != q->tail) {
    nq->queue[i] = q->queue[q->head];
    q->head = q->head++ % q->size;
    i++;
  }
  nq->queue[i] = q->queue[q->tail];
  nq->size = size;
  nq->len = q->len;

  return 0;
}

int queuePush(IDQueue *q, unsigned int num) {
  if (q->tail - q->head == 1) {
    int e = resizeQueue(q, q->size * 2 * sizeof(unsigned int));
    if (e < 0)
      return -1;
    q->tail++;
    q->queue[q->tail] = num;
    q->len++;
    return 0;
  }
  if (q->head == 0 && q->tail == q->size - 1) {
    int e = resizeQueue(q, q->size * 2 * sizeof(unsigned int));
    if (e < 0)
      return -1;
    q->tail++;
    q->queue[q->tail] = num;
    q->len++;
    return 0;
  }
  if (q->len == 0) {
    q->queue[q->tail] = num;
    q->len++;
    return 0;
  }
  q->tail++;
  q->queue[q->tail] = num;
  q->len++;

  return 0;
}

unsigned int queuePop(IDQueue *q) {
  unsigned int out = q->queue[q->head];
  if (q->len == 0) {
    return UINT_MAX;
  }
  if (q->head == q->tail) {
    q->len--;
    return out;
  }
  q->head++;
  if (q->head == q->size)
    q->head = 0;
  return out;
}

Scene *initScene(unsigned int size) {
  Scene *scene;
  scene->sceneObjects = malloc(size * sizeof(unsigned int));
  scene->numObjects = 0;
  scene->sceneObjectsSize = size;
  scene->nextIDQueue = createQueue(100);

  return scene;
}

unsigned int addSceneObject(Scene *scene, vec3 pos, vec3 rot, vec3 scale,
                            unsigned int meshID) {
  SceneObject obj;
  copyVec3(pos, obj.position);
  copyVec3(rot, obj.rotation);
  copyVec3(scale, obj.scale);
  obj.meshID = meshID;
  if (scene->nextIDQueue->len == 0) {
    obj.objID = scene->numObjects;
    scene->sceneObjects[scene->numObjects] = obj;
    scene->numObjects++;
  } else {
    unsigned int id = queuePop(scene->nextIDQueue);
    obj.objID = id;
    scene->sceneObjects[id] = obj;
    scene->numObjects++;
  }

  return obj.objID;
}

void removeSceneObject(Scene scene, unsigned int objID) {
  // Set this objects objID at objID to max value so we can check it on render
  scene.sceneObjects[objID].objID = UINT_MAX;
  queuePush(scene.nextIDQueue, objID);
}
