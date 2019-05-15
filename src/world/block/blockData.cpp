#include "blockData.h"

#include <fstream>

// NOTE: Probably create a prettier data format or use JSON or XML and adjust parsing accordingly.
BlockData::BlockData(const std::string& fileName) {

  std::ifstream inFile("resources/blocks/" + fileName + ".block");

  // NOTE: This shouldn't be an exception. Add hardcoded default data and continue execution normally?
  if (!inFile.is_open()) {
	throw std::runtime_error ("Unable to open block file: " + fileName + "!");
  }

  std::string line;
  while (std::getline(inFile, line)) {
	int x, y;

	if (line == "TexTop") {
	  inFile >> x >> y;
	  m_data.texTopCoord.x = x;
	  m_data.texTopCoord.y = y;
	} else if (line == "TexSide") {
	  inFile >> x >> y;
	  m_data.texSideCoord.x = x;
	  m_data.texSideCoord.y = y;

	} else if (line == "TexBottom") {
	  inFile >> x >> y;
	  m_data.texBottomCoord.x = x;
	  m_data.texBottomCoord.y = y;

	} else if (line == "TexAll") {
	  inFile >> x >> y;
	  m_data.texTopCoord.x = x;
	  m_data.texTopCoord.y = y;
	  m_data.texSideCoord.x = x;
	  m_data.texSideCoord.y = y;
	  m_data.texBottomCoord.x = x;
	  m_data.texBottomCoord.y = y;
	}
  }

}

const BlockDataHolder& BlockData::getBlockData() const {
  return m_data;
}
