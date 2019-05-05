#pragma once

#include "../includes.h"
#include "window.h"

namespace graphics {

  enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UPWARDS,
	DOWNWARDS
  };

  // Default Camera Values
  const float YAW = -90.0f;
  const float PITCH = 0.0f;
  const float SPEED = 10.0f;
  const float SENSITIVITY = 0.10f;
  const float FOV = 45.0f;

  class Camera {
	public:
	  Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
	  Camera(float xPos, float yPos, float zPos, float xUp, float yUp, float zUp, float yaw, float pitch);

	  glm::mat4 getViewMatrix();
	  glm::mat4 getProjectionMatrix();

	  void processInput(float deltaTime);

	  // Getters
	  inline float getYaw() const { return m_Yaw; }
	  inline float getPitch() const { return m_Pitch; }
	  inline float getMovementSpeed() const { return m_MovementSpeed; }
	  inline float getMouseSensitivity() const { return m_MouseSensitivity; }
	  inline float getFOV() const { return m_FOV; }
	  inline const glm::vec3& getFront() const { return m_Front; }
	  inline const glm::vec3& getPosition() const { return m_Position; }
	private:
	  // Camera Attributes
	  glm::vec3 m_Position, m_Front, m_Up, m_Right, m_WorldUp;

	  // Euler Angles
	  float m_Yaw;
	  float m_Pitch;

	  // Camera Options
	  float m_MovementSpeed;
	  float m_MouseSensitivity;
	  float m_FOV;

	  void updateCameraVectors();
	  void processKeyboard(Camera_Movement direction, float deltaTime);
	  void processMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch);
	  void processMouseScroll(float yOffset);
  };

}
