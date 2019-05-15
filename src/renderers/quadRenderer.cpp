#include "quadRenderer.h"
#include "../utils/loaders/textureLoader.h"

#include <iostream>


QuadRenderer::QuadRenderer() : m_shader("default_vertex.glsl", "default_fragment.glsl") {

  m_quadModel.addData({
	  {
		-0.5,  0.5, 0,
		0.5,  0.5, 0,
		0.5, -0.5, 0,
		-0.5, -0.5, 0,
	  },
	  {
		0, 1,
		1, 1,
		1, 0,
		0, 0,
	  },
	  {
		0, 1, 2,
		2, 3, 0
	  }
	});
}

void QuadRenderer::add(const glm::vec3 &position) {
  m_quads.push_back(position);
}

void QuadRenderer::renderQuads(const graphics::Camera &camera) {
  m_shader.enable();
  m_quadModel.bindVAO();
  m_texture.bind();

  m_shader.setUniformMat4("view", camera.getViewMatrix());
  m_shader.setUniformMat4("projection", camera.getProjectionMatrix());

  for (auto &quad : m_quads) {
	m_shader.setUniformMat4("model", camera.makeModelMatrix({quad, {0, 0, 0}}));
	glDrawElements(GL_TRIANGLES, m_quadModel.getIndicesCount(), GL_UNSIGNED_INT, nullptr);
  }

  m_quads.clear();
}

