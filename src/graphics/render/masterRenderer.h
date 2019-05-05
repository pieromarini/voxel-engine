#ifndef MASTERRENDERER_H
#define MASTERRENDERER_H

#include <vector>
#include "../../world/chunk.h"

namespace graphics {

  class MasterRenderer {
	public:
	  MasterRenderer();
	  ~MasterRenderer();
	  void renderChunks(graphics::Shader &shader) const;
	  void addChunk(world::Chunk *chunk);

	private:
	  std::vector<world::Chunk *> chunks;
  };

}

#endif
