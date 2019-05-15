#ifndef MESH_H_INCLUDED
#define MESH_H_INCLUDED

#include <vector>

struct Mesh {
  std::vector<float> vertexPositions;
  std::vector<float> textureCoords;
  std::vector<unsigned int>  indices;
};

#endif
