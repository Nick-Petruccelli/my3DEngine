#include "../inc/assetManager.h"
#include "../inc/camera.h"
#include "../inc/glad.h"
#include "../inc/sceneManager.h"
#include <stdio.h>

void render(Scene *scene, unsigned int shaderProgram) {
  glUseProgram(shaderProgram);
  for (int i = 0; i < scene->numObjects; i++) {
    SceneObject obj = scene->sceneObjects[i];
    Camera *cam = scene->camera;
    unsigned int meshID = obj.meshID;

    mat4 model;
    mat4 view;
    mat4 proj;
    genModelMatV(obj.position, obj.rotation, obj.scale, model);
    vec3 up = {0, 1, 0};
    lookAt(cam->position, cam->target, up, view);
    genPerspectiveMat(cam->fov, 800.0f / 600.0f, .1, 100, proj);

    int modelLoc = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, convertMat4ToArr(model));
    int viewLoc = glGetUniformLocation(shaderProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, convertMat4ToArr(view));
    int projLoc = glGetUniformLocation(shaderProgram, "proj");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, convertMat4ToArr(proj));

    MeshInfo meshInfo = MIA.meshInfo[meshID];

    glBindVertexArray(meshInfo.vao);
    glBindBuffer(GL_ARRAY_BUFFER, meshInfo.vbo);
    glDrawArrays(GL_TRIANGLES, 0, meshInfo.numVerts);
  }
}
