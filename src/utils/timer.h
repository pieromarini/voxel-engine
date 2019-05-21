#ifndef TIMER_H
#define TIMER_H

#include <GLFW/glfw3.h>
#include <string>

namespace utils {

  class Timer {
	public:
	  Timer();
	  void reset();
	  void logTimer(std::string prefix = "");
	  double getTime();
	private:
	  double startTime;
  };

} 

#endif
