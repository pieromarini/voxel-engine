#include "ray.h"

Ray::Ray(const glm::vec3 &position, const float &yaw, const float &pitch) : m_rayStart(position), m_rayEnd(position), m_yaw(yaw), m_pitch(pitch) { }

void Ray::step(float scale) {
  m_rayEnd.x += cos(glm::radians(m_yaw)) * scale;
  m_rayEnd.z += sin(glm::radians(m_yaw)) * scale;
  m_rayEnd.y += tan(glm::radians(m_pitch)) * scale;
}

const glm::vec3& Ray::getEnd() const {
  return m_rayEnd;
}

float Ray::getLength() const {
  return glm::distance(m_rayStart, m_rayEnd);
}
