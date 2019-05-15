#include <iostream>

#include "../world/block/blockDatabase.h"
#include "chunkRenderer.h"

ChunkRenderer::ChunkRenderer() : m_shader("chunk_vertex.glsl", "chunk_fragment.glsl") { }

void ChunkRenderer::add(const ChunkMesh &mesh) {
  m_chunks.push_back(&mesh);
}

void ChunkRenderer::render(const graphics::Camera &camera) {
  m_shader.enable();

  BlockDatabase::get().textureAtlas.bind();

  m_shader.setUniformMat4("view", camera.getViewMatrix());
  m_shader.setUniformMat4("projection", camera.getProjectionMatrix());

  for (const ChunkMesh *mesh : m_chunks) {
	const ChunkMesh &m = *mesh;

	m.getModel().bindVAO();
	glDrawElements(GL_TRIANGLES, m.getModel().getIndicesCount(), GL_UNSIGNED_INT, nullptr);
  }

  m_chunks.clear();
}
