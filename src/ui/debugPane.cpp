#include "debugPane.h"

namespace ui {

  glm::vec3 *DebugPane::s_CameraPosition = nullptr;
  bool DebugPane::s_WireframeMode = false;

  DebugPane::DebugPane(glm::vec2 panePosition) : Pane(std::string("Debug Controls"), panePosition) {}

  void DebugPane::setupPaneObjects() {
	if (s_CameraPosition != nullptr)
	  ImGui::Text("Camera Pos x:%.1f y:%.1f z:%.1f", s_CameraPosition->x, s_CameraPosition->y, s_CameraPosition->z);

	ImGui::Text("Hit \"P\" to show/hide the cursor");
	ImGui::Checkbox("Wireframe Mode", &s_WireframeMode);
  }

}
