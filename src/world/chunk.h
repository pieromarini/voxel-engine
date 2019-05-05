#ifndef CHUNK_H
#define CHUNK_H

#include "../graphics/shader.h"
#include "../graphics/render/mesh.h"


namespace world {

  class Chunk {
	public:
	  Chunk(glm::vec3 position);
	  ~Chunk();

	  void update(float deltaTime);
	  void render(graphics::Shader &shader);
	  graphics::Mesh getMeshFace(graphics::BlockFace face);

	  static const int CHUNK_SIZE = 16;

	private:
	  bool blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
	  unsigned int VAO, VBO, EBO;
	  glm::vec3 position;
	  int triangleCount;
	  std::vector<float> vertices;

	  void buildMesh();

  };



}

#endif
