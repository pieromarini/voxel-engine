#include "blockDatabase.h"

// NOTE: Declare all Block Types here so they are initialized and their data is loaded.
BlockDatabase::BlockDatabase() {
  m_blocks[(int)BlockId::Air] = std::make_unique<DefaultBlock>("air");
  m_blocks[(int)BlockId::Grass] = std::make_unique<DefaultBlock>("grass");
  m_blocks[(int)BlockId::Dirt] = std::make_unique<DefaultBlock>("dirt");
  m_blocks[(int)BlockId::Stone] = std::make_unique<DefaultBlock>("stone");
}

BlockDatabase& BlockDatabase::get() {
  static BlockDatabase d;
  return d;
}

const BlockType& BlockDatabase::getBlock(BlockId id) const {
  return *m_blocks[(int)id];
}

const BlockData& BlockDatabase::getData(BlockId id) const {
  return m_blocks[(int)id]->getData();
}


