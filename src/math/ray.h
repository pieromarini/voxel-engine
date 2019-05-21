#ifndef RAY_H_INCLUDED
#define RAY_H_INCLUDED

#include "../includes.h"

class Ray {
  public:
	Ray(const glm::vec3 &position, const float &yaw, const float &pitch);

	void step(float scale);

	const glm::vec3& getEnd() const;

	float getLength() const;

  private:
	glm::vec3 m_rayStart;
	glm::vec3 m_rayEnd;
	float m_yaw, m_pitch;
};

#endif
