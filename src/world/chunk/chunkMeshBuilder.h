#ifndef CHUNKMESHBUILDER_H
#define CHUNKMESHBUILDER_H

#include <vector>
#include <GL/glew.h>
#include "chunkSection.h"
#include "chunkMesh.h"
#include "../block/blockData.h"

class ChunkMeshBuilder {
  public:
	ChunkMeshBuilder(const ChunkSection &chunk, ChunkMesh &mesh);
	void buildMesh();

  private:
	void tryAddFaceToMesh(const std::vector<float> &blockFace, const glm::vec2 &textureCoords, const glm::vec3 &blockPosition, const glm::vec3 &blockFacing); 
	bool shouldMakeFace (const glm::vec3 &blockPosition, const BlockDataHolder& blockData);

	const ChunkSection *m_pChunk = nullptr;
	const BlockDataHolder *m_pBlockData = nullptr;
	ChunkMesh *m_pMesh = nullptr;
};

#endif
