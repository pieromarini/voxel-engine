#ifndef TIME_H
#define TIME_H

#include <GLFW/glfw3.h>
#include <GL/gl.h>

namespace utils {

  struct Time {
	private:
	  double lastFrame;
	  double delta;
	public:
	  Time();
	  void update();

	  inline double getDeltaTime() const { return delta; }
  };

}

#endif
