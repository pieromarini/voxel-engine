#ifndef MESH_H
#define MESH_H

#include <vector>

namespace graphics {

  enum class BlockFace {
	Top, Bottom, Front, Back, Right, Left
  };

  struct Mesh {
	Mesh() = default;
	Mesh(std::vector<float> vertices, std::vector<float> normals, std::vector<float> texCoords);
	void update(const Mesh& other, std::size_t x, std::size_t y, std::size_t z);

	inline std::size_t triangleCount() { return vertices.size() / 3; }

	std::vector<float> vertices, normals, texCoords;
  };

}
#endif
