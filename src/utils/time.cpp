#include "time.h"

namespace utils {

  Time::Time() {
	lastFrame = glfwGetTime();
	delta = 0;
  }

  void Time::update() {
	delta = glfwGetTime() - lastFrame;
	lastFrame = glfwGetTime();
  }

}
