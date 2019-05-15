#include "chunkMesh.h"

#include "../worldConstants.h"

#include <iostream>

ChunkMesh::ChunkMesh() { }

void ChunkMesh::addFace(const std::vector<float> &blockFace, const std::vector<float> &textureCoords, const glm::vec3 &chunkPosition, const glm::vec3 &blockPosition) {

  auto &vertices = m_mesh.vertexPositions;
  auto &texCoords = m_mesh.textureCoords;
  auto &indices = m_mesh.indices;

  texCoords.insert(texCoords.end(), textureCoords.begin(), textureCoords.end());

  // Vertex: The current vertex in the "blockFace" vector, 4 vertex in total hence "< 4"
  // Index: X, Y, Z
  for (int i = 0, index = 0; i < 4; ++i) {
	vertices.push_back(blockFace[index++] + chunkPosition.x * CHUNK_SIZE + blockPosition.x);
	vertices.push_back(blockFace[index++] + chunkPosition.y * CHUNK_SIZE + blockPosition.y);
	vertices.push_back(blockFace[index++] + chunkPosition.z * CHUNK_SIZE + blockPosition.z);
  }

  indices.insert(indices.end(),
  {
	m_indexIndex,
	m_indexIndex + 1,
	m_indexIndex + 2,

	m_indexIndex + 2,
	m_indexIndex + 3,
	m_indexIndex
  });
  m_indexIndex += 4;
}

void ChunkMesh::bufferMesh() {
  m_model.addData(m_mesh);

  m_mesh.vertexPositions.clear();
  m_mesh.textureCoords.clear();
  m_mesh.indices.clear();

  m_mesh.vertexPositions.shrink_to_fit();
  m_mesh.textureCoords.shrink_to_fit();
  m_mesh.indices.shrink_to_fit();

  m_indexIndex = 0;
}

const graphics::Model &ChunkMesh::getModel() const {
  return m_model;
}
