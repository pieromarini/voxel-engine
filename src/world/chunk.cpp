#include "chunk.h"
#include <GL/glew.h>
#include "../utils/timer.h"
#include "../math/noiseGenerator.h"

namespace world {

  Chunk::Chunk(glm::vec3 position) : position(position) {
	initChunkBlocks();
	setupLandscape();
	buildMesh();
	setupBuffers();
  }

  Chunk::~Chunk() { 
	destroyChunkBlocks(); 
  }

  void Chunk::initChunkBlocks() {
	blocks = new Block**[CHUNK_SIZE];

	for(int i = 0; i < CHUNK_SIZE; ++i) {
	  blocks[i] = new Block*[CHUNK_SIZE];

	  for(int j = 0; j < CHUNK_SIZE; ++j)
		blocks[i][j] = new Block[CHUNK_SIZE];
	}
  }

  void Chunk::destroyChunkBlocks() {
	for (int i = 0; i < CHUNK_SIZE; ++i) {
	  for (int j = 0; j < CHUNK_SIZE; ++j) {
		delete [] blocks[i][j];
	  }
	  delete [] blocks[i];
	}
	delete [] blocks;
  }

  void Chunk::setupBuffers() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
  }

  void Chunk::buildMesh() {
	// utils::Timer t{};

	// TODO: Optimize chunk-based built faces.
	// TODO: Add vertex count and bind to ImGUI debug panel.
	graphics::Mesh chunkMesh{};
	for (int x = 0; x < CHUNK_SIZE; ++x) {
	  for (int y = 0; y < CHUNK_SIZE; ++y) {
		for (int z = 0; z < CHUNK_SIZE; ++z) {

		  // Dont render inactive blocks.
		  if (!blocks[x][y][z].isActive()) continue;

		  chunkMesh.update(getMeshFace(graphics::BlockFace::Back), x, y, z);
		  chunkMesh.update(getMeshFace(graphics::BlockFace::Bottom), x, y, z);
		  chunkMesh.update(getMeshFace(graphics::BlockFace::Left), x, y, z);
		  chunkMesh.update(getMeshFace(graphics::BlockFace::Front), x, y, z);
		  chunkMesh.update(getMeshFace(graphics::BlockFace::Top), x, y, z);
		  chunkMesh.update(getMeshFace(graphics::BlockFace::Right), x, y, z);
		}
	  }
	}

	triangleCount = chunkMesh.triangleCount();

	// NOTE: inserting interleaved vertex data (3 vertex 2 uvs)
	// This follows the VertexAttribArrays format specified in the constructor.
	for (std::size_t i = 0, j = 0; i < chunkMesh.vertices.size(); i += 3, j += 2) {
	  vertices.push_back(chunkMesh.vertices[i]);
	  vertices.push_back(chunkMesh.vertices[i + 1]);
	  vertices.push_back(chunkMesh.vertices[i + 2]);

	  vertices.push_back(chunkMesh.texCoords[j]);
	  vertices.push_back(chunkMesh.texCoords[j + 1]);
	}

	// t.logTimer("Chunk Build: ");
  }

  void Chunk::setupLandscape() {

	math::NoiseParameters params {7, CHUNK_SIZE, 2000, 0, 0.53};
	// Randomize seed
	math::NoiseGenerator noise{21212};
	noise.setParameters(params);

	for(int x = 0; x < CHUNK_SIZE; ++x) {
	  for(int z = 0; z < CHUNK_SIZE; ++z) {
		double height = noise.getHeight(x, z, position.x, position.z);

		for (int y = 0; y < height && y < CHUNK_SIZE; ++y) {
		  blocks[x][y][z].setActive(true);
		}
	  }
	}
  }

  void Chunk::render(graphics::Shader &shader) {
	// utils::Timer t{};

	glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
	shader.setUniformMat4("model", model);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, triangleCount);

	// t.logTimer("Chunk Render: ");
  }

  graphics::Mesh Chunk::getMeshFace(graphics::BlockFace face) {
	if (face == graphics::BlockFace::Top)
	  return graphics::Mesh {
		{
		  -0.5f, 0.5f,  0.5f,
			0.5f, 0.5f,  0.5f,
			0.5f, 0.5f, -0.5f,
			0.5f, 0.5f, -0.5f,
			-0.5f, 0.5f, -0.5f,
			-0.5f, 0.5f,  0.5f
		},
		  {
			0.0f,  1.0f,  0.0f
		  },
		  {
			1.0f, 0.0f,
			0.0f, 0.0f,
			0.0f, 1.0f,
			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f
		  }
	  };
	else if (face == graphics::BlockFace::Bottom)
	  return graphics::Mesh {
		{
		  -0.5f, -0.5f, -0.5f,
			0.5f, -0.5f, -0.5f,
			0.5f, -0.5f,  0.5f,
			0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f, -0.5f
		},
		  {
			0.0f, -1.0f,  0.0f
		  },
		  {
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,
			0.0f, 0.0f
		  }
	  };
	else if (face == graphics::BlockFace::Front)
	  return graphics::Mesh {
		{
		  -0.5f, -0.5f,  0.5f,
			0.5f, -0.5f,  0.5f,
			0.5f,  0.5f,  0.5f,
			0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f
		},
		  {
			0.0f,  0.0f,  1.0f
		  },
		  {
			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,
			0.0f, 1.0f
		  }
	  };
	else if (face == graphics::BlockFace::Back)
	  return graphics::Mesh {
		{
		  0.5f,  0.5f, -0.5f,
			0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f,  0.5f, -0.5f,
			0.5f,  0.5f, -0.5f
		},
		  {
			0.0f,  0.0f, -1.0f
		  },
		  {
			0.0f, 0.0f,
			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f
		  }
	  };
	else if (face == graphics::BlockFace::Right)
	  return graphics::Mesh {
		{
		  0.5f,  0.5f,  0.5f,
			0.5f, -0.5f,  0.5f,
			0.5f, -0.5f, -0.5f,
			0.5f, -0.5f, -0.5f,
			0.5f,  0.5f, -0.5f,
			0.5f,  0.5f,  0.5f
		},
		  {
			1.0f,  0.0f,  0.0f
		  },
		  {
			0.0f, 0.0f,
			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f
		  }
	  };
	else // face == graphics::BlockFace::Left
	  return graphics::Mesh {
		{
		  -0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f
		},
		  {
			-1.0f,  0.0f,  0.0f
		  },
		  {
			1.0f, 0.0f,
			0.0f, 0.0f,
			0.0f, 1.0f,
			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f
		  }
	  };
  }

}
