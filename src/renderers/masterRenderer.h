#ifndef MASTERRENDERER_H
#define MASTERRENDERER_H

#include "../includes.h"

#include "quadRenderer.h"
#include "cubeRenderer.h"
#include "chunkRenderer.h"

#include "../graphics/window.h"

#include "../world/chunk/chunkMesh.h"

class MasterRenderer {
  public:
	// NOTE: These functions add a mesh to the render 'queue'
	void drawQuad(const glm::vec3 &pos);
	void drawCube(const glm::vec3 &pos);
	void drawChunk(const ChunkMesh &mesh);

	void finishRender(graphics::Window &window, graphics::Camera &camera);

  private:
	QuadRenderer m_quadRenderer;
	CubeRenderer m_cubeRenderer;
	ChunkRenderer m_chunkRenderer;
};

#endif
