#ifndef WINDOW_H
#define WINDOW_H

#include "../config.h"
#include "../includes.h"
#include "../vendor/imgui/imgui.h"
#include "../vendor/imgui/imgui_impl_glfw_gl3.h"

namespace graphics {

#define MAX_KEYS 1024
#define MAX_BUTTONS 32
#define WINDOW_X_RESOLUTION 1366
#define WINDOW_Y_RESOLUTION 768

  class Window {
	public:
	  Window(const char *title, int width, int height);
	  ~Window();

	  void update();
	  bool closed() const;
	  static void clear();

	  static bool isKeyPressed(unsigned int keycode);
	  static bool isMouseButtonPressed(unsigned int code);


	  // Getters and Setters
	  static inline double getMouseX() { return s_MouseX; }
	  static inline double getMouseY() { return s_MouseY; }
	  static inline double getMouseXDelta() { return s_MouseXDelta; }
	  static inline double getMouseYDelta() { return s_MouseYDelta; }
	  static inline double getScrollX() { return s_ScrollX; }
	  static inline double getScrollY() { return s_ScrollY; }
	  static inline void resetScroll() { s_ScrollX = 0; s_ScrollY = 0; }
	  static inline void getMousePosition(double &x, double &y) { x = s_MouseX; y = s_MouseY; }
	  static inline int getWidth() { return m_Width; }
	  static inline int getHeight() { return m_Height; }

	private:
	  const char *m_Title;
	  GLFWwindow *m_Window;
	  bool m_HideCursor;

	  static int m_Width, m_Height;
	  static bool s_Keys[MAX_KEYS];
	  static bool s_Buttons[MAX_BUTTONS];
	  static double s_MouseX, s_MouseY, s_MouseXDelta, s_MouseYDelta;
	  static double s_ScrollX, s_ScrollY;

	  bool init();

	  void setFullscreenResolution();

	  // Callback Functions
	  friend void error_callback(int error, const char* description);
	  friend void window_resize_callback(GLFWwindow *window, int width, int height);
	  friend void framebuffer_resize_callback(GLFWwindow *window, int width, int height);
	  friend void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
	  friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	  friend void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	  friend void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	  friend void char_callback(GLFWwindow* window, unsigned int c);
  };


}

#endif
