#include <iostream>

#include "includes.h"

#include "graphics/shader.h"
#include "graphics/camera.h"

#include "utils/loaders/textureLoader.h"
#include "utils/time.h"

#include "ui/runtimePane.h"
#include "ui/debugPane.h"

#include "world/chunkManager.h"
#include "world/chunk.h"

#include "utils/timer.h"
#include "utils/loaders/textureLoader.h"
#include "graphics/texture/texture.h"

int main() {

  graphics::Window window("Engine", 1366, 768);
  graphics::Camera camera(glm::vec3(8.0f, 18.0f, 8.0f));

  graphics::Shader shaderCube("cube_vertex.glsl", "cube_fragment.glsl");
  graphics::Texture *tex = utils::TextureLoader::load2DTexture("resources/textures/stone.png", false);

  world::ChunkManager chunkManager{shaderCube};

  ui::RuntimePane runtimePane(glm::vec2(256.0f, 80.0f));
  ui::DebugPane debugPane(glm::vec2(256.0f, 145.0f));

  utils::Time deltaTime;

  chunkManager.addChunk(new world::Chunk(glm::vec3(0.0f, 0.0f, 0.0f)));

  chunkManager.addChunk(new world::Chunk(glm::vec3(16.0f, 0.0f, 0.0f)));
  chunkManager.addChunk(new world::Chunk(glm::vec3(0.0f, 0.0f, 16.0f)));
  chunkManager.addChunk(new world::Chunk(glm::vec3(-16.0f, 0.0f, 0.0f)));
  chunkManager.addChunk(new world::Chunk(glm::vec3(0.0f, 0.0f, -16.0f)));

  chunkManager.addChunk(new world::Chunk(glm::vec3(16.0f, 0.0f, 16.0f)));
  chunkManager.addChunk(new world::Chunk(glm::vec3(16.0f, 0.0f, -16.0f)));
  chunkManager.addChunk(new world::Chunk(glm::vec3(-16.0f, 0.0f, 16.0f)));
  chunkManager.addChunk(new world::Chunk(glm::vec3(-16.0f, 0.0f, -16.0f)));

  chunkManager.addChunk(new world::Chunk(glm::vec3(32.0f, 0.0f, 0.0f)));
  chunkManager.addChunk(new world::Chunk(glm::vec3(0.0f, 0.0f, 32.0f)));
  chunkManager.addChunk(new world::Chunk(glm::vec3(-32.0f, 0.0f, 0.0f)));
  chunkManager.addChunk(new world::Chunk(glm::vec3(0.0f, 0.0f, -32.0f)));

  chunkManager.addChunk(new world::Chunk(glm::vec3(32.0f, 0.0f, 32.0f)));
  chunkManager.addChunk(new world::Chunk(glm::vec3(32.0f, 0.0f, -32.0f)));
  chunkManager.addChunk(new world::Chunk(glm::vec3(-32.0f, 0.0f, 32.0f)));
  chunkManager.addChunk(new world::Chunk(glm::vec3(-32.0f, 0.0f, -32.0f)));

  chunkManager.addChunk(new world::Chunk(glm::vec3(16.0f, 0.0f, 32.0f)));
  chunkManager.addChunk(new world::Chunk(glm::vec3(16.0f, 0.0f, -32.0f)));
  chunkManager.addChunk(new world::Chunk(glm::vec3(-16.0f, 0.0f, 32.0f)));
  chunkManager.addChunk(new world::Chunk(glm::vec3(-16.0f, 0.0f, -32.0f)));

  chunkManager.addChunk(new world::Chunk(glm::vec3(32.0f, 0.0f, 16.0f)));
  chunkManager.addChunk(new world::Chunk(glm::vec3(32.0f, 0.0f, -16.0f)));
  chunkManager.addChunk(new world::Chunk(glm::vec3(-32.0f, 0.0f, 16.0f)));
  chunkManager.addChunk(new world::Chunk(glm::vec3(-32.0f, 0.0f, -16.0f)));

  chunkManager.buildChunkMeshes();

  // Lightning
  shaderCube.enable();
  shaderCube.setUniform3f("lightPos", glm::vec3(10.0f, 28.0f, 7.5f));
  shaderCube.setUniform3f("lightColor", glm::vec3(1.0, 1.0, 1.0));

  while(!window.closed()) {

	deltaTime.update();

	if (debugPane.getWireframeMode())
	  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
	  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	window.clear();

	ImGui_ImplGlfwGL3_NewFrame();

	camera.processInput(deltaTime.getDeltaTime());

	// VP Matrices. Model Matrix should be set by each renderer.
	shaderCube.setUniformMat4("view", camera.getViewMatrix());
	shaderCube.setUniformMat4("projection", camera.getProjectionMatrix());

	shaderCube.setUniform3f("viewPos", camera.getPosition());

	tex->bind();
	chunkManager.update(deltaTime.getDeltaTime());

	debugPane.render();
	runtimePane.render();

	ImGui::Render();
	ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

	ImGui::EndFrame();

	window.resetScroll();
	window.update();
  }

  return 0;
}
