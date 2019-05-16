#ifndef CHUNKBLOCK_H
#define CHUNKBLOCK_H

#include "blockId.h"
#include "blockData.h"
#include "blockTypes/blockType.h"

struct ChunkBlock {
  ChunkBlock() = default;

  ChunkBlock(Block_t id);
  ChunkBlock(BlockId id);

  const BlockData& getData() const;
  const BlockType& getType() const;

  bool operator==(ChunkBlock other) { return id == other.id; }
  bool operator!=(ChunkBlock other) { return id != other.id; }

  Block_t id = 0;
};

#endif
