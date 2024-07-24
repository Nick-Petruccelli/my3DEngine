#include "../inc/assetManager.h"
#include "../inc/glad.h"

void render() {
  for (int i = 0; i < MIA.len; i++) {
    MeshInfo meshInfo = MIA.meshInfo[i];

    glBindVertexArray(meshInfo.vao);
    glBindBuffer(GL_ARRAY_BUFFER, meshInfo.vbo);
    glDrawArrays(GL_TRIANGLES, 0, meshInfo.numVerts);
  }
}
