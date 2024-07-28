#include "../inc/assetManager.h"
#include "../inc/camera.h"
#include "../inc/glad.h"
#include "../inc/sceneManager.h"
#include <stdio.h>

void render(Scene *scene, unsigned int objShader, unsigned int lightShader) {
  mat4 view;
  mat4 proj;
  Camera *cam = scene->camera;
  vec3 up = {0, 1, 0};
  lookAt(cam, up, view);
  genPerspectiveMat(cam->fov, 800.0f / 600.0f, .1, 100, proj);

  glUseProgram(objShader);
  int viewLoc = glGetUniformLocation(objShader, "view");
  float *viewOut = convertMat4ToArr(view);
  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, viewOut);
  int projLoc = glGetUniformLocation(objShader, "proj");
  float *projOut = convertMat4ToArr(proj);
  glUniformMatrix4fv(projLoc, 1, GL_FALSE, projOut);
  int objModelLoc = glGetUniformLocation(objShader, "model");

  int lightPosLoc = glGetUniformLocation(objShader, "lightPos");
  glUniform3fv(lightPosLoc, 1, scene->sceneLights[0].position);

  for (int i = 0; i < scene->numObjects; i++) {
    SceneObject obj = scene->sceneObjects[i];
    unsigned int meshID = obj.meshID;

    mat4 model;
    genModelMatV(obj.position, obj.rotation, obj.scale, model);

    float *modelOut = convertMat4ToArr(model);
    glUniformMatrix4fv(objModelLoc, 1, GL_FALSE, modelOut);
    free(modelOut);

    MeshInfo meshInfo = MIA.meshInfo[meshID];

    glBindVertexArray(meshInfo.vao);
    glBindBuffer(GL_ARRAY_BUFFER, meshInfo.vbo);
    glDrawArrays(GL_TRIANGLES, 0, meshInfo.numVerts);
  }

  glUseProgram(lightShader);
  viewLoc = glGetUniformLocation(lightShader, "view");
  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, viewOut);
  free(viewOut);
  projLoc = glGetUniformLocation(lightShader, "proj");
  glUniformMatrix4fv(projLoc, 1, GL_FALSE, projOut);
  free(projOut);
  int lightModelLoc = glGetUniformLocation(lightShader, "model");

  for (int i = 0; i < scene->numLights; i++) {
    SceneLight light = scene->sceneLights[i];
    unsigned int meshID = light.meshID;

    mat4 model;
    genModelMatV(light.position, light.rotation, light.scale, model);

    float *modelOut = convertMat4ToArr(model);
    glUniformMatrix4fv(lightModelLoc, 1, GL_FALSE, modelOut);
    free(modelOut);

    MeshInfo meshInfo = MIA.meshInfo[meshID];

    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, meshInfo.vbo);
    glDrawArrays(GL_TRIANGLES, 0, meshInfo.numVerts);
  }
}
