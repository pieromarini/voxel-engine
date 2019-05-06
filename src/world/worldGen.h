#ifndef WORLDGEN_H
#define WORLDGEN_H

#include "../includes.h"
#include "chunk.h"


namespace world {

  class WorldGen {
	public:
	  WorldGen();

	private:
	  std::vector<Chunk *> chunks;	
  };

}

#endif
