#include <iostream>

#include "masterRenderer.h"

void MasterRenderer::drawQuad(const glm::vec3 &pos) {
  m_quadRenderer.add(pos);
}

void MasterRenderer::drawCube(const glm::vec3 &pos) {
  m_cubeRenderer.add(pos);
}

void MasterRenderer::drawChunk(const ChunkMesh &mesh) {
  m_chunkRenderer.add(mesh);
}

void MasterRenderer::finishRender(graphics::Window &window, const graphics::Camera &camera) {

  window.clear();

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  m_quadRenderer.renderQuads(camera);
  m_cubeRenderer.render(camera);
  m_chunkRenderer.render(camera);

  // window.update();
}
