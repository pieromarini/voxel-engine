#ifndef PANE_H
#define PANE_H

#include <string>
#include <glm/glm.hpp>
#include <glm/common.hpp>
#include "../vendor/imgui/imgui.h"

namespace ui {

  class Pane {
	public:
	  Pane(std::string paneName, glm::vec2 paneSize);
	  virtual ~Pane() = default;

	  void render();
	protected:
	  virtual void setupPaneObjects() = 0;

	  std::string m_PaneName;
	  glm::vec2 m_PaneSize;
  };

}

#endif
