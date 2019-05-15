#ifndef BLOCKDATABASE_H
#define BLOCKDATABASE_H

#include <memory>
#include <array>

#include "../../graphics/texture/textureAtlas.h"
#include "../../utils/singleton.h"

#include "blockTypes/blockType.h"
#include "blockId.h"


class BlockDatabase : public utils::Singleton {
  public:
	static BlockDatabase& get();

	const BlockType& getBlock(BlockId id) const;
	const BlockData& getData(BlockId id) const;

	graphics::TextureAtlas textureAtlas;

  private:
	BlockDatabase();

	std::array<std::unique_ptr<BlockType>, (unsigned)BlockId::NUM_TYPES> m_blocks;
};

#endif
