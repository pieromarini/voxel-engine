#include "cubeRenderer.h"

#include <iostream>

CubeRenderer::CubeRenderer() : m_shader("default_vertex.glsl", "default_fragment.glsl") {

    std::vector<float> vertexCoords {
        //Back
        1, 0, 0,
        0, 0, 0,
        0, 1, 0,
        1, 1, 0,

        //Front
        0, 0, 1,
        1, 0, 1,
        1, 1, 1,
        0, 1, 1,

        //Right
        1, 0, 1,
        1, 0, 0,
        1, 1, 0,
        1, 1, 1,

        //Left
        0, 0, 0,
        0, 0, 1,
        0, 1, 1,
        0, 1, 0,

        //Top
        0, 1, 1,
        1, 1, 1,
        1, 1, 0,
        0, 1, 0,

        //Bottom
        0, 0, 0,
        1, 0, 0,
        1, 0, 1,
        0, 0, 1.
    };

    auto top = m_atlasTest.getTexture({0, 0});
    auto side = m_atlasTest.getTexture({1, 0});
    auto bottom = m_atlasTest.getTexture({2, 0});

    std::vector<float> texCoords;
    texCoords.insert(texCoords.end(), side.begin(),     side.end());
    texCoords.insert(texCoords.end(), side.begin(),     side.end());
    texCoords.insert(texCoords.end(), side.begin(),     side.end());
    texCoords.insert(texCoords.end(), side.begin(),     side.end());
    texCoords.insert(texCoords.end(), top.begin(),      top.end());
    texCoords.insert(texCoords.end(), bottom.begin(),   bottom.end());


    std::vector<unsigned int> indices {
        0, 1, 2,
        2, 3, 0,

        4, 5, 6,
        6, 7, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    m_cubeModel.addData({vertexCoords, texCoords, indices});
}

void CubeRenderer::add(const glm::vec3 &position) {
    m_quads.push_back(position);
}

void CubeRenderer::render(const graphics::Camera &camera) {
    m_shader.enable();
    m_cubeModel.bindVAO();
	m_atlasTest.bind();

	m_shader.setUniformMat4("view", camera.getViewMatrix());
	m_shader.setUniformMat4("projection", camera.getProjectionMatrix());

	for (auto &quad : m_quads) {
	  m_shader.setUniformMat4("model", camera.makeModelMatrix({quad, {0, 0, 0}}));
	  glDrawElements(GL_TRIANGLES, m_cubeModel.getIndicesCount(), GL_UNSIGNED_INT, nullptr);
	}

	m_quads.clear();
}

