#include "mesh.h"
#include <iostream>

namespace graphics {

  Mesh::Mesh(std::vector<float> vertices, std::vector<float> normals, std::vector<float> texCoords) : vertices(vertices), normals(normals), texCoords(texCoords) { 
	currentIndex = 0;
  }

  void Mesh::update(const Mesh& other, std::size_t x, std::size_t y, std::size_t z) {

	for (std::size_t i = 0; i < other.vertices.size() / 3; ++i) {
	  vertices.push_back(other.vertices[i * 3] + x);
	  vertices.push_back(other.vertices[1 + i * 3] + y);
	  vertices.push_back(other.vertices[2 + i * 3] + z);
	}

	// Insert indices corresponding to the specified vertices.
	indices.insert(indices.end(), {
	  currentIndex,
	  currentIndex + 1,
	  currentIndex + 2,
	  currentIndex + 2,
	  currentIndex + 3,
	  currentIndex
	});
	currentIndex += 4;

	normals.insert(normals.end(), other.normals.begin(), other.normals.end());
	texCoords.insert(texCoords.end(), other.texCoords.begin(), other.texCoords.end());
  }


}

