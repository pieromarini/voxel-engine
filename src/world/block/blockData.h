#ifndef BLOCKDATA_H_INCLUDED
#define BLOCKDATA_H_INCLUDED

#include "../../includes.h"

struct BlockDataHolder {
  glm::vec3 texTopCoord;
  glm::vec3 texSideCoord;
  glm::vec3 texBottomCoord;
};

class BlockData {
  public:
	BlockData(const std::string& fileName);

	const BlockDataHolder& getBlockData() const;

	std::string name;
  private:
	BlockDataHolder m_data;

};

#endif // BLOCKDATA_H_INCLUDED
