#include "debugPane.h"

namespace ui {

  // Initialize Static Variables
  glm::vec3 *DebugPane::s_CameraPosition = nullptr;
  bool DebugPane::s_WireframeMode = false;
  int DebugPane::s_Cubes = 0;
  int DebugPane::s_Faces = 0;

  DebugPane::DebugPane(glm::vec2 panePosition) : Pane(std::string("Debug Controls"), panePosition) { }

  void DebugPane::setupPaneObjects() {
	if (s_CameraPosition != nullptr)
	  ImGui::Text("Camera Pos x:%.1f y:%.1f z:%.1f", s_CameraPosition->x, s_CameraPosition->y, s_CameraPosition->z);

	ImGui::Text("Total Cubes: %i", s_Cubes);
	ImGui::Text("Rendered Faces: %i", s_Faces);

	ImGui::Text("Hit \"P\" to show/hide the cursor");
	ImGui::Checkbox("Wireframe Mode", &s_WireframeMode);
  }

}
