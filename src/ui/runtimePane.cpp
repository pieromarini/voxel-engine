#include "runtimePane.h"

namespace ui {

  RuntimePane::RuntimePane(glm::vec2 panePosition) : Pane(std::string("Runtime Analytics"), panePosition) {}

  void RuntimePane::setupPaneObjects() {
	ImGui::Text("Frametime: %.3f ms (FPS %.1f)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
  }

}
