#include <iostream>

#include "../block/blockId.h"
#include "../world.h"

#include "chunkSection.h"

ChunkSection::ChunkSection(const glm::vec3 &location, World &world) : m_location(location), m_pWorld(&world) {
  static_assert(sizeof(m_blocks) == CHUNK_VOLUME, "Chunk size too big.");
  // std::cout << "ChunkSection: " << sizeof(m_blocks) << " " << sizeof(*this) << '\n';
}

void ChunkSection::setBlock(int x, int y, int z, ChunkBlock block) {
  if (outOfBounds(x) || outOfBounds(y) || outOfBounds(z)) {
	auto location = toWorldPosition(x, y, z);
	m_pWorld->setBlock(location.x, location.y, location.z, block);
	return;
  }

  m_blocks[getIndex(x, y, z)] = block;
}

ChunkBlock ChunkSection::getBlock(int x, int y, int z) const {
  if (outOfBounds(x) || outOfBounds(y) || outOfBounds(z)) {
	auto location = toWorldPosition(x, y, z);
	return m_pWorld->getBlock(location.x, location.y, location.z);
  }

  return m_blocks[getIndex(x, y, z)];
}

const glm::vec3 ChunkSection::getLocation() const noexcept {
  return m_location;
}

bool ChunkSection::hasMesh() const noexcept {
  return m_hasMesh;
}

glm::vec3 ChunkSection::toWorldPosition(int x, int y, int z) const {
  return {
	m_location.x * CHUNK_SIZE + x,
	m_location.y * CHUNK_SIZE + y,
	m_location.z * CHUNK_SIZE + z
  };
}

bool ChunkSection::outOfBounds(int value) {
  return value >= CHUNK_SIZE || value < 0;
}

int ChunkSection::getIndex(int x, int y, int z) {
  return y * CHUNK_AREA + z * CHUNK_SIZE + x;
}
