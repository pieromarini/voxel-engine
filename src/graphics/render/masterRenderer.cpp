#include "masterRenderer.h"

namespace graphics {

  MasterRenderer::MasterRenderer() {

  }

  MasterRenderer::~MasterRenderer() {
	for (auto &chunk : chunks) {
	  delete chunk; 
	}
  }

  void MasterRenderer::renderChunks(graphics::Shader &shader) const {

	glEnable(GL_CULL_FACE);

	for (auto &chunk : chunks) {
	  chunk->render(shader); 
	}
  }

  void MasterRenderer::addChunk(world::Chunk *chunk) { 
	chunks.push_back(chunk); 
  }

}
