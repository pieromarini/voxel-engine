#ifndef CHUNK_H
#define CHUNK_H

#include "../graphics/shader.h"
#include "../graphics/render/mesh.h"
#include "block/block.h"


namespace world {

  class Chunk {
	public:
	  Chunk(glm::vec3 position);
	  ~Chunk();

	  void update(float deltaTime);
	  void render(graphics::Shader &shader);
	  void buildMesh();

	  inline glm::vec3 getPosition() { return position; }
	  inline graphics::Mesh getMesh() { return chunkMesh; }

	  static const int CHUNK_SIZE = 16;

	private:
	  Block ***blocks;

	  unsigned int VAO, VBO, EBO;
	  std::vector<float> vertices;
	  std::vector<unsigned int> indices;

	  glm::vec3 position;
	  graphics::Mesh chunkMesh;

	  graphics::Mesh getMeshFace(graphics::BlockFace face);
	  void setupLandscape();
	  void setupBuffers();
	  void initChunkBlocks();
	  void destroyChunkBlocks();

  };

}

#endif
