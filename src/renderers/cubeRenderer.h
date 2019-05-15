#ifndef CUBERENDERER_H_INCLUDED
#define CUBERENDERER_H_INCLUDED

#include <vector>

#include "../includes.h"
#include "../graphics/camera.h"
#include "../graphics/model.h"
#include "../graphics/shader.h"
#include "../graphics/texture/textureAtlas.h"


class CubeRenderer {
  public:
	CubeRenderer();

	void add(const glm::vec3 &position);

	void render(const graphics::Camera &camera);

  private:
	std::vector<glm::vec3> m_quads;

	graphics::Model m_cubeModel;
	graphics::Shader m_shader;
	graphics::Texture m_texture;
	graphics::TextureAtlas m_atlasTest;
};

#endif // CUBERENDERER_H_INCLUDED
