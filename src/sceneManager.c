#include "../inc/sceneManager.h"
#include "../inc/glMath.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

IDQueue *createQueue(unsigned int size) {
  IDQueue *q = malloc(sizeof(IDQueue));
  q->queue = malloc(size * sizeof(unsigned int));
  if (q->queue == NULL) {
    printf("ERROR::SCENEMANAGER::CREATEQUEUE\nfailed to allocate memory for "
           "queue\n");
    return NULL;
  }
  q->head = 0;
  q->tail = 0;
  q->len = 0;
  q->size = size;

  return q;
}

int resizeQueue(IDQueue *q, unsigned int size) {
  unsigned int *nq = malloc(size * sizeof(unsigned int));
  if (nq == NULL) {
    return -1;
  }
  for (unsigned int i = 0; i < q->size; i++) {
    unsigned int idx = (q->head + i) % q->size;
    nq[i] = q->queue[idx];
  }
  if (q->queue != NULL)
    free(q->queue);
  q->queue = nq;
  q->size = size;
  q->head = 0;
  q->tail = q->len - 1;

  return 0;
}

int queuePush(IDQueue *q, unsigned int num) {
  if (q->head - q->tail == 1) {
    int e = resizeQueue(q, q->size * 2);
    if (e < 0)
      return -1;
    q->tail++;
    if (q->tail >= q->size)
      q->tail = 0;
    q->queue[q->tail] = num;
    q->len++;
    return 0;
  }
  if (q->head == 0 && q->tail == q->size - 1) {
    int e = resizeQueue(q, q->size * 2);
    if (e < 0)
      return -1;
    q->tail++;
    if (q->tail >= q->size)
      q->tail = 0;
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
  if (q->tail >= q->size)
    q->tail = 0;
  q->queue[q->tail] = num;
  q->len++;

  return 0;
}

unsigned int queuePop(IDQueue *q) {
  if (q->len == 0) {
    return UINT_MAX;
  }
  unsigned int out = q->queue[q->head];
  q->head++;
  q->len--;
  if (q->head == q->size)
    q->head = 0;
  return out;
}

Scene *initScene(unsigned int size, Camera *cam) {
  Scene *scene = malloc(sizeof(Scene));
  scene->sceneObjects = malloc(size * sizeof(SceneObject));
  scene->numObjects = 0;
  scene->sceneObjectsSize = size;
  scene->nextIDQueue = createQueue(100);
  scene->camera = cam;

  return scene;
}

void deleteScene(Scene *scene) {
  free(scene->nextIDQueue->queue);
  free(scene->nextIDQueue);
  free(scene->sceneObjects);
  free(scene->camera);
  free(scene);
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
    scene->sceneObjects[obj.objID] = obj;
    scene->numObjects++;
  } else {
    obj.objID = queuePop(scene->nextIDQueue);
    scene->sceneObjects[obj.objID] = obj;
    scene->numObjects++;
  }
  printf("SceneObjectSize: %d\nObjID: %d\n", scene->sceneObjectsSize,
         obj.objID);

  return obj.objID;
}

void removeSceneObject(Scene scene, unsigned int objID) {
  // Set this objects objID at objID to max value so we can check it on render
  scene.sceneObjects[objID].objID = UINT_MAX;
  int e = queuePush(scene.nextIDQueue, objID);
  if (e < 0) {
    printf("ERROR::SCNENEMANAGER::REMOVESCENEOBJECT\nFailed queuePush.\n");
  }
}
