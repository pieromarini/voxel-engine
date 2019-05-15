#include "chunkMeshBuilder.h"

#include "chunkSection.h"
#include "chunkMesh.h"

#include "../block/blockData.h"
#include "../block/blockDatabase.h"

#include "../../includes.h"

namespace {

  const std::vector<float> frontFace {
	0, 0, 1,
	1, 0, 1,
	1, 1, 1,
	0, 1, 1,
  };

  const std::vector<float> backFace {
	1, 0, 0,
	0, 0, 0,
	0, 1, 0,
	1, 1, 0,
  };

  const std::vector<float> leftFace {
	0, 0, 0,
	0, 0, 1,
	0, 1, 1,
	0, 1, 0,
  };

  const std::vector<float> rightFace {
	1, 0, 1,
	1, 0, 0,
	1, 1, 0,
	1, 1, 1,
  };

  const std::vector<float> topFace {
	0, 1, 1,
	1, 1, 1,
	1, 1, 0,
	0, 1, 0,
  };

  const std::vector<float> bottomFace {
	0, 0, 0,
	1, 0, 0,
	1, 0, 1,
	0, 0, 1
  };

}

ChunkMeshBuilder::ChunkMeshBuilder(const ChunkSection &chunk, ChunkMesh &mesh) : m_pChunk(&chunk), m_pMesh(&mesh) { } 

struct AdjacentBlockPositions {

  void update(int x, int y, int z) {
	up      =   {x,     y + 1,  z};
	down    =   {x,     y - 1,  z};
	left    =   {x - 1, y,      z};
	right   =   {x + 1, y,      z};
	front   =   {x,     y,      z + 1};
	back    =   {x,     y,      z - 1};
  }

  glm::vec3 up;
  glm::vec3 down;
  glm::vec3 left;
  glm::vec3 right;
  glm::vec3 front;
  glm::vec3 back;
};

int faces;

void ChunkMeshBuilder::buildMesh() {

  AdjacentBlockPositions directions;

  faces = 0;
  for (int8_t y = 0; y < CHUNK_SIZE; ++y)
	for (int8_t x = 0; x < CHUNK_SIZE; ++x)
	  for (int8_t z = 0; z < CHUNK_SIZE; ++z) {
		glm::vec3 position(x, y, z);
		ChunkBlock block = m_pChunk->getBlock(x, y, z);

		if (block == BlockId::Air) { continue; }

		m_pBlockData = &block.getData().getBlockData();
		auto &data = *m_pBlockData;
		directions.update(x, y, z);


		//Up/ Down
		tryAddFaceToMesh(bottomFace,    data.texBottomCoord,    position, directions.down);
		tryAddFaceToMesh(topFace,       data.texTopCoord,       position, directions.up);

		//Left/ Right
		tryAddFaceToMesh(leftFace,      data.texSideCoord,      position, directions.left);
		tryAddFaceToMesh(rightFace,     data.texSideCoord,      position, directions.right);

		//Front/ Back
		tryAddFaceToMesh(frontFace,     data.texSideCoord,      position, directions.front);
		tryAddFaceToMesh(backFace,      data.texSideCoord,      position, directions.back);
	  }
}

void ChunkMeshBuilder::tryAddFaceToMesh(const std::vector<float> &blockFace, const glm::vec2 &textureCoords, const glm::vec3 &blockPosition, const glm::vec3 &blockFacing) {
  if (shouldMakeFace(blockFacing, *m_pBlockData)) {
	faces++;

	auto texCoords = BlockDatabase::get().textureAtlas.getTexture(textureCoords);

	m_pMesh->addFace(blockFace, texCoords, m_pChunk->getLocation(), blockPosition);
  }
}


bool ChunkMeshBuilder::shouldMakeFace(const glm::vec3 &adjBlock, const BlockDataHolder &blockData) {

  auto block = m_pChunk->getBlock(adjBlock.x, adjBlock.y, adjBlock.z);

  return block == BlockId::Air;

  ///TODO: Transparent Blocks
}
