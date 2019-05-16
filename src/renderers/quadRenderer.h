#ifndef QUADRENDERER_H
#define QUADRENDERER_H

#include "../includes.h"
#include "../graphics/shader.h"
#include "../graphics/model.h"
#include "../graphics/texture/texture.h"
#include "../graphics/camera.h"

namespace graphics {
  class Camera;
}

class QuadRenderer {
  public:
	QuadRenderer();

	void add(const glm::vec3 &position);
	void renderQuads(const graphics::Camera &camera);

  private:
	std::vector<glm::vec3> m_quads;

	graphics::Model m_quadModel;
	graphics::Shader m_shader;
	graphics::Texture m_texture;
};

#endif
