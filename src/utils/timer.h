#pragma once

#include <GLFW/glfw3.h>
#include <string>

namespace utils {

  class Timer {
	private:
	  double startTime;
	public:
	  Timer();
	  void reset();
	  void logTimer(std::string prefix = "");
  };

} 
