#include "instancedArrayRenderer.h"
#include "../../utils/loaders/textureLoader.h"

namespace graphics {

  InstancedArrayRenderer::InstancedArrayRenderer(std::vector<float> &vertices, std::vector<unsigned int> &indices, std::vector<glm::vec3> &offsets, int instances) 
	: vertices(vertices), indices(indices), offsets(offsets), instances(instances) {

	setupBuffers();

	// NOTE: Hardcoded texture
	texture = utils::TextureLoader::load2DTexture("resources/textures/stone.png", false);
  }

  InstancedArrayRenderer::~InstancedArrayRenderer() {
	glDeleteVertexArrays(1, &meshVAO);
	glDeleteBuffers(1, &meshVBO);
	glDeleteBuffers(1, &meshEBO);
	glDeleteBuffers(1, &instanceVBO);
  }


  void InstancedArrayRenderer::draw(graphics::Shader &shader) {

	// NOTE: Just hardcoding the texture.
	// TODO: Support multiple textures.
	shader.setUniform1i("texture_diffuse1", 0);
	texture->bind(0);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glBindVertexArray(meshVAO);
	glDrawElementsInstanced(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0, instances);
	glBindVertexArray(0);

	texture->unbind();
  }

  void InstancedArrayRenderer::setupBuffers() {

    glGenBuffers(1, &instanceVBO);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * instances, &offsets[0], GL_STATIC_DRAW);

    glGenVertexArrays(1, &meshVAO);
    glGenBuffers(1, &meshVBO);
	glGenBuffers(1, &meshEBO);

    glBindVertexArray(meshVAO);

    glBindBuffer(GL_ARRAY_BUFFER, meshVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);


	// Vertices, UVs, Normals (In Order)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT , GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));

	// Offsets
    glEnableVertexAttribArray(3);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glVertexAttribDivisor(3, 1);

  }

}
