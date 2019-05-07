#ifndef CHUNKMANAGER_H
#define CHUNKMANAGER_H

#include "../includes.h"
#include "../graphics/camera.h"
#include "chunk.h"
#include "../graphics/shader.h"

/*
 * TODO:
 * 1) Check if Chunks need to be loaded
 * 2) Configure loaded Chunks
 * 3) Check if Chunks need to be rebuilt
 * 4) Check if Chunks need to be unloaded
 * 5) Update render list
 */

namespace world {

  // NOTE: this renders all added chunks to the vector.
  class ChunkManager {
	public:
	  ChunkManager(graphics::Shader &shader);
	  void update(float deltaTime);
	  void buildChunkMeshes();
	  void addChunk(Chunk *chunk);
	  void loadChunksFromFile();

	private:
	  glm::vec3 cameraPos;
	  glm::vec3 cameraView;
	  graphics::Shader shader;
	  std::vector<std::unique_ptr<Chunk>> chunks;
	  void render();

  };

}
#endif
