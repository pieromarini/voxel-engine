#include "chunkManager.h"
#include "../utils/timer.h"

namespace world {

  ChunkManager::ChunkManager(graphics::Shader &shader) : shader(shader) { }

  void ChunkManager::update(float deltaTime) {
	render();
  }

  void ChunkManager::addChunk(Chunk *chunk) {
	chunks.emplace_back(chunk);
  }

  // NOTE: just to time chunk building easily.
  void ChunkManager::buildChunkMeshes() {
	utils::Timer t{};
	for (auto &chunk : chunks) {
	  chunk->buildMesh();
	}
	t.logTimer(std::to_string(chunks.size()) + " Chunks Build Time: ");
  }

  void ChunkManager::render() {
	glEnable(GL_CULL_FACE);

	for (auto &chunk : chunks) {
	  chunk->render(shader);
	}
  }

  void ChunkManager::loadChunksFromFile() {
	// TODO
  }

}
