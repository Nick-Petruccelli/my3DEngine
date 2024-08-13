#include "../inc/assetManager.h"
#include "../inc/camera.h"
#include "../inc/glad.h"
#include "../inc/lighting.h"
#include "../inc/sceneManager.h"
#include "../inc/shaders.h"
#include "../inc/textures.h"
#include <stdio.h>

void setLightUniforms(Scene *scene, unsigned int objShader);

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

  int ambientLoc = glGetUniformLocation(objShader, "material.ambient");
  int diffLoc = glGetUniformLocation(objShader, "material.diffuse");
  int specLoc = glGetUniformLocation(objShader, "material.specular");
  int shinnyLoc = glGetUniformLocation(objShader, "material.shininess");

  setLightUniforms(scene, objShader);

  for (int i = 0; i < scene->numObjects; i++) {
    SceneObject obj = scene->sceneObjects[i];
    unsigned int meshID = obj.meshID;

    mat4 model;
    genModelMatV(obj.position, obj.rotation, obj.scale, model);

    float *modelOut = convertMat4ToArr(model);
    glUniformMatrix4fv(objModelLoc, 1, GL_FALSE, modelOut);
    free(modelOut);

    MeshInfo meshInfo = MIA.meshInfo[meshID];

    // temporary
    // set Material uniform
    glUniform1i(diffLoc, 0);
    glUniform1i(specLoc, 1);
    glUniform1f(shinnyLoc, obj.material.shininess);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, obj.material.diffMap);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, obj.material.specMap);
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

void setLightUniforms(Scene *scene, unsigned int objShader) {
  int numDirLights = 0;
  int numPointLights = 0;
  int numSpotLights = 0;
  for (int i = 0; i < scene->numLights; i++) {
    SceneLight light = scene->sceneLights[i];
    switch (light.lightType) {
    case DIR_LIGHT: {
      DirLight *dirLight = (DirLight *)light.lightStruct;
      char dirName[50];
      sprintf(dirName, "dirLights[%d].direction", numDirLights);
      setUniform3fv(objShader, dirName, dirLight->direction);

      char ambName[50];
      sprintf(ambName, "dirLights[%d].ambient", numDirLights);
      setUniform3fv(objShader, ambName, dirLight->ambient);

      char diffName[50];
      sprintf(diffName, "dirLights[%d].diffuse", numDirLights);
      setUniform3fv(objShader, diffName, dirLight->diffuse);

      char specName[50];
      sprintf(specName, "dirLights[%d].specular", numDirLights);
      setUniform3fv(objShader, specName, dirLight->specular);

      numDirLights++;
      break;
    }
    case POINT_LIGHT: {
      PointLight *pointLight = (PointLight *)light.lightStruct;
      char posName[50];
      sprintf(posName, "pointLights[%d].position", numPointLights);
      setUniform3fv(objShader, posName, pointLight->position);

      char constName[50];
      sprintf(constName, "pointLights[%d].constant", numPointLights);
      setUniform1f(objShader, constName, pointLight->constant);

      char linName[50];
      sprintf(linName, "pointLights[%d].linear", numPointLights);
      setUniform1f(objShader, linName, pointLight->linear);

      char quadName[50];
      sprintf(quadName, "pointLights[%d].quadradic", numPointLights);
      setUniform1f(objShader, quadName, pointLight->quadradic);

      char ambName[50];
      sprintf(ambName, "pointLights[%d].ambient", numPointLights);
      setUniform3fv(objShader, ambName, pointLight->ambient);

      char diffName[50];
      sprintf(diffName, "pointLights[%d].diffuse", numPointLights);
      setUniform3fv(objShader, diffName, pointLight->diffuse);

      char specName[50];
      sprintf(specName, "pointLights[%d].specular", numPointLights);
      setUniform3fv(objShader, specName, pointLight->specular);

      numPointLights++;
      break;
    }
    case SPOT_LIGHT: {
      SpotLight *spotLight = (SpotLight *)light.lightStruct;
      char posName[50];
      sprintf(posName, "spotLights[%d].position", numPointLights);
      setUniform3fv(objShader, posName, spotLight->position);

      char dirName[50];
      sprintf(dirName, "spotLights[%d].direction", numSpotLights);
      setUniform3fv(objShader, dirName, spotLight->direction);

      char innerName[50];
      sprintf(innerName, "spotLights[%d].innerCutoff", numSpotLights);
      setUniform1f(objShader, innerName, spotLight->innerCutoff);

      char outerName[50];
      sprintf(outerName, "spotLights[%d].outterCutoff", numSpotLights);
      setUniform1f(objShader, outerName, spotLight->outerCutoff);

      char ambName[50];
      sprintf(ambName, "spotLights[%d].ambient", numSpotLights);
      setUniform3fv(objShader, ambName, spotLight->ambient);

      char diffName[50];
      sprintf(diffName, "spotLights[%d].diffuse", numSpotLights);
      setUniform3fv(objShader, diffName, spotLight->diffuse);

      char specName[50];
      sprintf(specName, "spotLights[%d].specular", numSpotLights);
      setUniform3fv(objShader, specName, spotLight->specular);

      numSpotLights++;
      break;
    }
    }
  }
  setUniform1i(objShader, "numDirLights", numDirLights);
  setUniform1i(objShader, "numPointLights", numPointLights);
  setUniform1i(objShader, "numSpotLights", numSpotLights);
}
