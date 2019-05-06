#include "chunkManager.h"

namespace world {

  ChunkManager::ChunkManager(graphics::Shader &shader) : shader(shader) {

  }

  void ChunkManager::update(float deltaTime) {
	render();
  }

  void ChunkManager::loadChunksFromFile() {

  }

  void ChunkManager::addChunk(Chunk *chunk) {
	chunks.emplace_back(chunk);
  }

  void ChunkManager::render() {
	glEnable(GL_CULL_FACE);

	for (auto &chunk : chunks) {
	  chunk->render(shader);
	}
  }

}
