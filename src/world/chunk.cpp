#include "chunk.h"
#include <GL/glew.h>
#include "../utils/timer.h"

namespace world {

  Chunk::Chunk(glm::vec3 position) : position(position) {

	buildMesh();

	// buffers
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

  Chunk::~Chunk() { }

  void Chunk::buildMesh() {

	for (int x = 0; x < CHUNK_SIZE; ++x) {
	  for (int y = 0; y < CHUNK_SIZE; ++y) {
		for (int z = 0; z < CHUNK_SIZE; ++z) {
		  blocks[x][y][z] = true;
		}
	  }
	}


	// TODO: Optimize chunk-based rendered faces.
	graphics::Mesh chunkMesh{};
	for (int x = 0; x < CHUNK_SIZE; ++x) {
	  for (int y = 0; y < CHUNK_SIZE; ++y) {
		for (int z = 0; z < CHUNK_SIZE; ++z) {

		  if (x > 0 && blocks[x-1][y][z] == true) {
			// add face back
			chunkMesh.update(getMeshFace(graphics::BlockFace::Back), x-1, y, z);
		  }

		  if (y > 0 && blocks[x][y-1][z] == true) {
			// add face bottom
			chunkMesh.update(getMeshFace(graphics::BlockFace::Bottom), x, y-1, z);
		  }

		  if (z > 0 && blocks[x][y][z-1] == true) {
			// add face left
			chunkMesh.update(getMeshFace(graphics::BlockFace::Left), x, y, z-1);
		  }

		  if (x + 1 < CHUNK_SIZE && blocks[x+1][y][z] == true) {
			// add face front
			chunkMesh.update(getMeshFace(graphics::BlockFace::Front), x+1, y, z);
		  }

		  if (y + 1 < CHUNK_SIZE && blocks[x][y+1][z] == true) {
			// add face top
			chunkMesh.update(getMeshFace(graphics::BlockFace::Top), x, y+1, z);
		  }

		  if (z + 1 < CHUNK_SIZE && blocks[x][y][z+1] == true) {
			// add face right
			chunkMesh.update(getMeshFace(graphics::BlockFace::Right), x, y, z+1);
		  }
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

  }

  void Chunk::render(graphics::Shader &shader) {
	// utils::Timer t{};

	glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
	shader.setUniformMat4("model", model);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, triangleCount);

	// t.logTimer("Chunk Render: ");
  }

  // TODO: Fix Vertex Winding
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
