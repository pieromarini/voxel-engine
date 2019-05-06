#ifndef BLOCK_H
#define BLOCK_H

namespace world {

  enum BlockType {
	BlockType_Default = 0,

	BlockType_Grass,
	BlockType_Dirt,
	BlockType_Stone,
	BlockType_Sand,
	BlockType_Wood,
	BlockType_Water,

	BlockType_NumTypes,
  };

  class Block {
	public:
	  Block() : blockType(BlockType_Default) { }
	  Block(BlockType type) : blockType(type) { }

	  inline void setBlockType(BlockType type) { blockType = type; }
	  inline void setActive(bool value) { active = value; }

	  inline bool isActive() { return active; }
	  inline BlockType getType() { return blockType; }

	private:
	  BlockType blockType;
	  bool active = false;

  };

}

#endif
