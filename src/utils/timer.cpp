#include "timer.h"
#include "logger.h"

namespace utils {

  Timer::Timer() {
	startTime = glfwGetTime();
  }

  void Timer::reset() {
	startTime = glfwGetTime();
  }

  void Timer::logTimer(std::string prefix) {
	Logger::getInstance().info("[Timer]", prefix + std::to_string(glfwGetTime() - startTime) + "s");
  }

};

