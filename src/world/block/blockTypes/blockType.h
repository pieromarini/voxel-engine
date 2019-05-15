#ifndef BLOCKTYPE_H
#define BLOCKTYPE_H

#include "../../../includes.h"
#include "../blockData.h"

class BlockType {
  public:
	BlockType(const std::string& fileName);
	virtual ~BlockType() = default;

	const BlockData& getData() const;

  private:
	BlockData m_data;
};

class DefaultBlock : public BlockType {
  public:
	DefaultBlock(const std::string& fileName) : BlockType(fileName) { }
};

#endif
