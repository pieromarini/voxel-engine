#pragma once

#include "pane.h"

namespace ui {

  class DebugPane : public Pane {
	public:
	  DebugPane(glm::vec2 panePosition);

	  virtual void setupPaneObjects();

	  inline static void bindCameraPositionValue(glm::vec3 *ptr) { s_CameraPosition = ptr; }

	  inline static bool getWireframeMode() { return s_WireframeMode; }
	  inline static void setWireframeMode(bool choice) { s_WireframeMode = choice; }

	private:
	  static glm::vec3 *s_CameraPosition;
	  static bool s_WireframeMode;
  };

}
