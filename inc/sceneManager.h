#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "assetManager.h"
#include "camera.h"
#include "glMath.h"
#include "lighting.h"

typedef struct SceneObject {
  unsigned int objID;
  vec3 position;
  vec3 rotation;
  vec3 scale;
  unsigned int meshID;
  Material material;
} SceneObject;

typedef enum LightType { DIR_LIGHT, POINT_LIGHT, SPOT_LIGHT } LightType;

typedef struct SceneLight {
  unsigned int lightID;
  vec3 color;
  vec3 position;
  vec3 rotation;
  vec3 scale;
  unsigned int meshID;

  LightType lightType;
  void *lightStruct;
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
                            unsigned int meshID, Material materialID);
void removeSceneObject(Scene scene, unsigned int objID);
unsigned int addPointLight(Scene *scene, PointLight *lightStruct, vec3 color,
                           vec3 pos, vec3 rot, vec3 scale, unsigned int meshID);
void removeSceneLight(Scene scene, unsigned int lightID);
void deleteScene(Scene *scene);
#endif
