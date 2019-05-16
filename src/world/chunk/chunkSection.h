#ifndef CHUNKSECTION_H
#define CHUNKSECTION_H

#include <array>

#include "../../includes.h"
#include "../block/chunkBlock.h"
#include "../world.h"
#include "../worldConstants.h"
#include "chunkMesh.h"
#include "iChunk.h"

class World;

class ChunkSection : public IChunk {

  friend class Chunk;

  public:
	ChunkSection(const glm::vec3 &location, World &world);

	void setBlock(int x, int y, int z, ChunkBlock block) override;
	ChunkBlock getBlock(int x, int y, int z) const override;

	const glm::vec3 getLocation() const noexcept;

	bool hasMesh() const noexcept;


  private:
	glm::vec3 toWorldPosition(int x, int y, int z) const;

	static bool outOfBounds(int value);
	static int  getIndex(int x, int y, int z);

	std::array<ChunkBlock, CHUNK_VOLUME> m_blocks;
	ChunkMesh m_mesh;
	glm::vec3 m_location;

	World *m_pWorld;
	bool m_hasMesh = false;
};

#endif
