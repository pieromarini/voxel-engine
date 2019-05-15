#include <iostream>

#include "includes.h"

#include "graphics/shader.h"
#include "graphics/camera.h"
#include "graphics/texture/texture.h"

#include "utils/loaders/textureLoader.h"
#include "utils/time.h"
#include "utils/timer.h"

#include "ui/runtimePane.h"
#include "ui/debugPane.h"

#include "entities/entity.h"
#include "world/world.h"
#include "renderers/masterRenderer.h"


int main() {

  graphics::Window window("Engine", 1366, 768);
  graphics::Camera camera(glm::vec3(0.0f, 80.0f, 0.0f));

  ui::RuntimePane runtimePane(glm::vec2(256.0f, 80.0f));
  ui::DebugPane debugPane(glm::vec2(256.0f, 145.0f));

  utils::Time deltaTime;

  Entity player{};
  camera.attachToEntity(player);

  World world{};
  MasterRenderer renderer{};

  while(!window.closed()) {

	deltaTime.update();

	if (debugPane.getWireframeMode())
	  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
	  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	window.clear();

	ImGui_ImplGlfwGL3_NewFrame();

	camera.processInput(deltaTime.getDeltaTime());

    /*
	renderer.drawCube({0, 0, 0});
    renderer.drawCube({0, 2, 0});
	*/

	world.renderWorld(renderer);
	renderer.finishRender(window, camera);

	// TODO: All the gui rendering should be done inside the "masterRenderer" through an abstraction probably.
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
