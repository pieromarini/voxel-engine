#ifndef CHUNKMESH_H_INCLUDED
#define CHUNKMESH_H_INCLUDED

#include "../../includes.h"
#include "../../graphics/model.h"

#include <vector>

class ChunkMesh {
  public:
	ChunkMesh();

	void addFace(const std::vector<float> &blockFace,
				 const std::vector<float> &textureCoords,
				 const glm::vec3 &chunkPosition,
				 const glm::vec3 &blockPosition);

	void bufferMesh();

	const graphics::Model& getModel() const;


  private:
	Mesh m_mesh;
	graphics::Model m_model;
	unsigned int m_indexIndex = 0;
};

#endif // CHUNKMESH_H_INCLUDED
