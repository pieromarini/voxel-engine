#ifndef RUNTIMEPANE_H
#define RUNTIMEPANE_H

#include "pane.h"

namespace ui {

  class RuntimePane : public Pane {
	public:
	  RuntimePane(glm::vec2 panePosition);

	  virtual void setupPaneObjects();
  };

}

#endif
