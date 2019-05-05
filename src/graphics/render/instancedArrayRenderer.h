#ifndef INSTANCEDARRAYRENDERER_H
#define INSTANCEDARRAYRENDERER_H

#include "../../includes.h"
#include "../texture/texture.h"
#include "../shader.h"

namespace graphics {

  class InstancedArrayRenderer {
	public:
	  InstancedArrayRenderer(std::vector<float> &vertices, std::vector<unsigned int> &indices, std::vector<glm::vec3> &offsets, int instances);
	  ~InstancedArrayRenderer();

	  void draw(graphics::Shader &shader);

	private:
	  std::vector<float> vertices;
	  std::vector<unsigned int> indices;
	  std::vector<glm::vec3> offsets;
	  int instances, verticesPerMesh;
	  unsigned int instanceVBO, meshVAO, meshVBO, meshEBO;
	  graphics::Texture *texture;

	  void setupBuffers();

  };

}
#endif
