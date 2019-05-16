#ifndef SHADER_H
#define SHADER_H

#include "../includes.h"

namespace graphics {

  class Shader {
	public:
	  Shader() = default;
	  Shader(const char *vertPath, const char *fragPath);
	  Shader(const char *vertPath, const char *fragPath, const char *geoPath);
	  ~Shader();

	  void enable() const;
	  void disable() const;

	  void setUniform1f(const char *name, float value);
	  void setUniform1i(const char *name, int value);
	  void setUniform2f(const char *name, const glm::vec2& vector);
	  void setUniform3f(const char *name, const glm::vec3& vector);
	  void setUniform4f(const char *name, const glm::vec4& vector);
	  void setUniformMat3(const char *name, const glm::mat3& matrix);
	  void setUniformMat4(const char *name, const glm::mat4& matrix);

	  inline unsigned int getShaderID() { return id; }

	private:
	  int getUniformLocation(const char *name);
	  unsigned int load();

	  unsigned int id;
	  const char *m_VertPath, *m_FragPath, *m_GeomPath;
  };

}

#endif
