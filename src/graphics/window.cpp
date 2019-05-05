#include "window.h"

#define FULLSCREEN_MODE 0
#define V_SYNC 0

namespace graphics {

  // NOTE: OpenGL Debugging Callback.
  void APIENTRY openglCallbackFunction(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam) {
	// ignore non-significant error/warning codes
	if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return; 

	std::cout << "---------------" << '\n';
	std::cout << "Debug message (" << id << "): " <<  message << '\n';

	switch (source) {
	  case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
	  case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
	  case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
	  case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
	  case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
	  case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
	} 
	std::cout << '\n';

	switch (type) {
	  case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
	  case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
	  case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break; 
	  case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
	  case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
	  case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
	  case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
	  case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
	  case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
	} 
	std::cout << '\n';

	switch (severity) {
	  case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
	  case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
	  case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
	  case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
	} 
	std::cout << '\n';
	std::cout << '\n';
  }


  bool Window::s_Keys[MAX_KEYS];
  bool Window::s_Buttons[MAX_BUTTONS];
  int Window::m_Width, Window::m_Height;
  double Window::s_MouseX, Window::s_MouseY, Window::s_MouseXDelta, Window::s_MouseYDelta;
  double Window::s_ScrollX, Window::s_ScrollY;

  Window::Window(const char *title, int width, int height) {
	m_Title = title;
	m_Width = width;
	m_Height = height;
	s_ScrollX = s_ScrollY = 0;
	s_MouseXDelta = s_MouseYDelta = 0;
	m_HideCursor = true;

	if (!init()) {
	  utils::Logger::getInstance().error("[WindowInit]", "Could not initialize window class");
	  glfwDestroyWindow(m_Window);
	  glfwTerminate();
	}

	memset(s_Keys, 0, sizeof(bool) * MAX_KEYS);
	memset(s_Buttons, 0, sizeof(bool) * MAX_BUTTONS);
  }

  Window::~Window() {
	glfwDestroyWindow(m_Window);
	glfwTerminate();
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
  }

  bool Window::init() {
	glewExperimental = true;

	if (!glfwInit()) {
	  std::cout << "GLFW Failed To Initialize" << std::endl;
	  utils::Logger::getInstance().error("[WindowInit]", "Could not initialize the GLFW window");
	  return false;
	}

	// Context hints
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	// Window hints
	glfwWindowHint(GLFW_DOUBLEBUFFER, true);

	// Create the window and OpenGL context
	if (FULLSCREEN_MODE) {
	  setFullscreenResolution();
	  m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, glfwGetPrimaryMonitor(), NULL);
	}
	else {
	  m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
	}

	if (!m_Window) {
	  utils::Logger::getInstance().error("[WindowInit]", "Could not create the GLFW window");
	  std::cout << "GLFW Window Couldn't Be Created" << std::endl;
	  return false;
	}

	void error_callback(int error, const char* description);
	void window_resize_callback(GLFWwindow *window, int width, int height);
	void framebuffer_resize_callback(GLFWwindow *window, int width, int height);
	void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	void char_callback(GLFWwindow* window, unsigned int c);

	// Setup the mouse settings
	if (m_HideCursor) 
	  glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set up contexts and callbacks
	glfwMakeContextCurrent(m_Window);
	glfwSetWindowUserPointer(m_Window, this);
	glfwSetErrorCallback(error_callback);
	glfwSetWindowSizeCallback(m_Window, window_resize_callback);
	glfwSetFramebufferSizeCallback(m_Window, framebuffer_resize_callback);
	glfwSetKeyCallback(m_Window, key_callback);
	glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
	glfwSetCursorPosCallback(m_Window, cursor_position_callback);
	glfwSetScrollCallback(m_Window, scroll_callback);
	glfwSetCharCallback(m_Window, char_callback);
	glfwGetCursorPos(m_Window, &s_MouseX, &s_MouseY);

	// Enable Depth Testing by default
	glEnable(GL_DEPTH_TEST);

	// Check to see if v-sync was enabled and act accordingly
	if (V_SYNC) {
	  glfwSwapInterval(1);
	}
	else {
	  glfwSwapInterval(0);
	}


	// Initialize GLEW (allows us to use newer versions of OpenGL)
	if (glewInit() != GLEW_OK) {
	  std::cout << "Could not Initialize GLEW" << std::endl;
	  utils::Logger::getInstance().error("[WindowInit]", "Could not initialize the GLEW");
	  return 0;
	}
	std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;

	// Setup default OpenGL viewport
	glViewport(0, 0, m_Width, m_Height);

	// Enable the debug callback
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(openglCallbackFunction, nullptr);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, true);

	// Setup ImGui bindings
	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(m_Window, false);
	ImGui::StyleColorsDark();

	return 1;
  }

  void Window::update() {
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
	  std::cout << "OpenGL Error: " << error << std::endl;
	}

	glfwSwapBuffers(m_Window);
	s_MouseXDelta = s_MouseYDelta = 0;
	glfwPollEvents();
  }

  void Window::clear() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }

  bool Window::closed() const {
	return glfwWindowShouldClose(m_Window);
  }

  // Sets the Window's Size to the Primary Monitor's Resolution
  void Window::setFullscreenResolution() {
	const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	m_Width = mode->width;
	m_Height = mode->height;
  }

  /*                   Static Functions                    */
  bool Window::isKeyPressed(unsigned int keycode) {
	if (keycode >= MAX_KEYS) {
	  utils::Logger::getInstance().error("[InputCheck]", "Key checked is out of bounds (ie not supported)");
	  return false;
	}
	else {
	  return s_Keys[keycode];
	}
  }

  bool Window::isMouseButtonPressed(unsigned int code) {
	if (code >= MAX_BUTTONS) {
	  utils::Logger::getInstance().error("[InputCheck]", "Key checked is out of bounds (ie not supported)");
	  return false;
	}
	else {
	  return s_Buttons[code];
	}
  }

  void error_callback(int error, const char* description) {
	std::cout << "Error:" << description << std::endl;
  }

  void window_resize_callback(GLFWwindow *window, int width, int height) {
	Window* win = (Window*)glfwGetWindowUserPointer(window);
	if (width == 0 || height == 0) {
	  win->m_Width = WINDOW_X_RESOLUTION;
	  win->m_Height = WINDOW_Y_RESOLUTION;
	} else {
	  win->m_Width = width;
	  win->m_Height = height;
	}
	glViewport(0, 0, win->m_Width, win->m_Height);
  }

  // TODO: Finish
  void framebuffer_resize_callback(GLFWwindow *window, int width, int height) {
	// Window* win = (Window*)glfwGetWindowUserPointer(window);
  }

  void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
	Window* win = (Window*)glfwGetWindowUserPointer(window);
	win->s_Keys[key] = action != GLFW_RELEASE;
	ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);

	if (key == GLFW_KEY_P && action == GLFW_RELEASE) {
	  win->m_HideCursor = !win->m_HideCursor;
	  GLenum cursorOption = win->m_HideCursor ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL;
	  glfwSetInputMode(win->m_Window, GLFW_CURSOR, cursorOption);
	}
  }

  void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
	Window* win = (Window*)glfwGetWindowUserPointer(window);
	win->s_Buttons[button] = action != GLFW_RELEASE;
	ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
	  Window::s_Buttons[0] = true;
	}
  }

  void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
	Window* win = (Window*)glfwGetWindowUserPointer(window);
	win->s_MouseXDelta = xpos - win->s_MouseX;
	win->s_MouseYDelta = ypos - win->s_MouseY;
	win->s_MouseX = xpos;
	win->s_MouseY = ypos;
  }

  void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	Window* win = (Window*)glfwGetWindowUserPointer(window);
	win->s_ScrollX = xoffset;
	win->s_ScrollY = yoffset;
	ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset);
  }

  void char_callback(GLFWwindow* window, unsigned int c) {
	ImGui_ImplGlfw_CharCallback(window, c);
  }


}
