#ifndef CHUNKRENDERER_H_INCLUDED
#define CHUNKRENDERER_H_INCLUDED

#include <vector>

#include "../includes.h"
#include "../graphics/shader.h"
#include "../graphics/camera.h"
#include "../world/chunk/chunkMesh.h"

class ChunkRenderer {
  public:
	ChunkRenderer();
	void add(const ChunkMesh &mesh);
	void render(const graphics::Camera &camera);

  private:
	std::vector<const ChunkMesh*> m_chunks;

	graphics::Shader m_shader;

};

#endif // CHUNKRENDERER_H_INCLUDED
