#include "../inc/assetManager.h"
#include "../inc/camera.h"
#include "../inc/glad.h"
#include "../inc/sceneManager.h"
#include <stdio.h>

void render(Scene *scene, unsigned int shaderProgram) {
  glUseProgram(shaderProgram);
  mat4 view;
  mat4 proj;
  Camera *cam = scene->camera;
  vec3 up = {0, 1, 0};
  lookAt(cam, up, view);
  genPerspectiveMat(cam->fov, 800.0f / 600.0f, .1, 100, proj);

  int viewLoc = glGetUniformLocation(shaderProgram, "view");
  float *viewOut = convertMat4ToArr(view);
  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, viewOut);
  free(viewOut);
  int projLoc = glGetUniformLocation(shaderProgram, "proj");
  float *projOut = convertMat4ToArr(proj);
  glUniformMatrix4fv(projLoc, 1, GL_FALSE, projOut);
  free(projOut);
  for (int i = 0; i < scene->numObjects; i++) {
    SceneObject obj = scene->sceneObjects[i];
    unsigned int meshID = obj.meshID;

    mat4 model;
    genModelMatV(obj.position, obj.rotation, obj.scale, model);

    int modelLoc = glGetUniformLocation(shaderProgram, "model");
    float *modelOut = convertMat4ToArr(model);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, modelOut);
    free(modelOut);

    MeshInfo meshInfo = MIA.meshInfo[meshID];

    glBindVertexArray(meshInfo.vao);
    glBindBuffer(GL_ARRAY_BUFFER, meshInfo.vbo);
    glDrawArrays(GL_TRIANGLES, 0, meshInfo.numVerts);
  }
}
