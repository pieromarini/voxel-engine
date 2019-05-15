#ifndef MASTERRENDERER_H_INCLUDED
#define MASTERRENDERER_H_INCLUDED


#include "../includes.h"
#include "../world/chunk/chunkMesh.h"

#include "quadRenderer.h"
#include "cubeRenderer.h"
#include "chunkRenderer.h"

class MasterRenderer {
  public:
	// NOTE: This functions add a mesh to the render 'queue'
	void drawQuad(const glm::vec3 &pos);
	void drawCube(const glm::vec3 &pos);
	void drawChunk(const ChunkMesh &mesh);

	void finishRender(graphics::Window &window, const graphics::Camera &camera);

  private:
	QuadRenderer m_quadRenderer;
	CubeRenderer m_cubeRenderer;
	ChunkRenderer m_chunkRenderer;
};



#endif
