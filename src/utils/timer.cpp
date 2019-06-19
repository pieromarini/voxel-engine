#include "timer.h"
#include "logger.h"

namespace utils {

  Timer::Timer() {
	startTime = glfwGetTime();
  }

  void Timer::reset() {
	startTime = glfwGetTime();
  }

  double Timer::getTime() {
	return glfwGetTime() - startTime;
  }

  void Timer::logTimer(std::string prefix) {
	logger::log<logger::Debug>("[Timer]", prefix, glfwGetTime() - startTime, "s");
  }

};

