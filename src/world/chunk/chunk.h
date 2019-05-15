#ifndef CHUNK_H_INCLUDED
#define CHUNK_H_INCLUDED

#include <vector>
#include "../../renderers/masterRenderer.h"
#include "../block/chunkBlock.h"
#include "../world.h"
#include "iChunk.h"
#include "chunkSection.h"

class ChunkSection;
class World;

class Chunk : public IChunk {
  public:
	Chunk(World &world, const glm::vec2 &location);

	void makeMesh();

	void setBlock(int x, int y, int z, ChunkBlock block) override;
	ChunkBlock getBlock(int x, int y, int z) const override;

	void drawChunks(MasterRenderer &renderer);

  private:
	bool outOfBound(int x, int y, int z) const;

	std::vector<ChunkSection> m_chunks;
	glm::vec2 m_location;

	World *m_pWorld;

	bool m_isLoaded = false;

};

#endif // CHUNK_H_INCLUDED
