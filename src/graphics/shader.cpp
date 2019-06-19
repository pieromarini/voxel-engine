#include <vector>
#include <GL/glew.h>

#include "../utils/fileUtils.h"
#include "shader.h"

#define SHADER_PATH "resources/shaders/"

namespace graphics {

  Shader::Shader(const char *vertPath, const char *fragPath)
	: m_VertPath(vertPath), m_FragPath(fragPath), m_GeomPath("") {
	id = load();
  }

  Shader::Shader(const char *vertPath, const char *fragPath, const char *geoPath)
	: m_VertPath(vertPath), m_FragPath(fragPath), m_GeomPath(geoPath) {
	id = load();
  }

  Shader::~Shader() {
	glDeleteProgram(id);
  }

  unsigned int Shader::load() {
	// Create the program and shaders
	unsigned int program = glCreateProgram();
	unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);

	// NOTE: C-string concat. Move to utils.
	char *pathVert, *pathFrag;
	pathVert = static_cast<char *>(malloc(strlen(m_VertPath) + strlen(SHADER_PATH) + 1));
	pathFrag = static_cast<char *>(malloc(strlen(m_FragPath) + strlen(SHADER_PATH) + 1));
	strcpy(pathVert, SHADER_PATH);
	strcat(pathVert, m_VertPath);
	strcpy(pathFrag, SHADER_PATH);
	strcat(pathFrag, m_FragPath);
	std::string vertSourceString = utils::FileUtils::readFile(pathVert);
	std::string fragSourceString = utils::FileUtils::readFile(pathFrag);
	free(pathVert);
	free(pathFrag);

	const char *vertSource = vertSourceString.c_str();
	const char *fragSource = fragSourceString.c_str();

	glShaderSource(vertex, 1, &vertSource, NULL);
	glCompileShader(vertex);
	int result;

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
	  int length;
	  glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
	  std::vector<char> error(length);
	  glGetShaderInfoLog(vertex, length, &length, &error[0]);

	  std::string errorStr {error.begin(), error.end()};
	  logger::log<logger::Error>("[ShaderInit]", "Failed to compile vertex shader ", m_VertPath, errorStr);

	  glDeleteShader(vertex);
	  return 0;
	}

	glShaderSource(fragment, 1, &fragSource, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
	  int length;
	  glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
	  std::vector<char> error(length);
	  glGetShaderInfoLog(fragment, length, &length, &error[0]);

	  std::string errorStr {error.begin(), error.end()};
	  logger::log<logger::Error>("[ShaderInit]", "Failed to compile fragment shader", m_FragPath, errorStr);

	  glDeleteShader(fragment);
	  return 0;
	}

	unsigned int geometry;
	if (std::strcmp(m_GeomPath, "") != 0) {
	  geometry = glCreateShader(GL_GEOMETRY_SHADER);
	  std::string geomSourceString = utils::FileUtils::readFile(m_GeomPath);
	  const char *geomSource = geomSourceString.c_str();

	  // Geometry Shader
	  glShaderSource(geometry, 1, &geomSource, NULL);
	  glCompileShader(geometry);
	  int resultGeo;

	  // Check to see if it was successful
	  glGetShaderiv(geometry, GL_COMPILE_STATUS, &resultGeo);
	  if (resultGeo == GL_FALSE) {
		int length;
		glGetShaderiv(geometry, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> error(length);
		glGetShaderInfoLog(geometry, length, &length, &error[0]);

		std::string errorStr {error.begin(), error.end()};
		logger::log<logger::Error>("[ShaderInit]", "Failed to compile geometry shader", m_GeomPath, errorStr);

		glDeleteShader(geometry);
		return 0;
	  }
	}

	glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	if (std::strcmp(m_GeomPath, "") != 0)
	  glAttachShader(program, geometry);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
	if (std::strcmp(m_GeomPath, "") != 0)
	  glDeleteShader(geometry);

	return program;
  }

  int Shader::getUniformLocation(const char* name) {
	return glGetUniformLocation(id, name);
  }

  void Shader::setUniform1f(const char* name, float value) {
	glUniform1f(getUniformLocation(name), value);
  }

  void Shader::setUniform1i(const char* name, int value) {
	glUniform1i(getUniformLocation(name), value);
  }

  void Shader::setUniform2f(const char* name, const glm::vec2& vector) {
	glUniform2f(getUniformLocation(name), vector.x, vector.y);
  }

  void Shader::setUniform3f(const char* name, const glm::vec3& vector) {
	glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
  }

  void Shader::setUniform4f(const char* name, const glm::vec4& vector) {
	glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
  }

  void Shader::setUniformMat3(const char* name, const glm::mat3& matrix) {
	glUniformMatrix3fv(glGetUniformLocation(id, name), 1, GL_FALSE, glm::value_ptr(matrix));
  }

  void Shader::setUniformMat4(const char* name, const glm::mat4& matrix) {
	glUniformMatrix4fv(glGetUniformLocation(id, name), 1, GL_FALSE, glm::value_ptr(matrix));
  }

  void Shader::enable() const {
	glUseProgram(id);
  }

  void Shader::disable() const {
	glUseProgram(0);
  }

}
