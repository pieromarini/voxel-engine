#ifndef RAYCAST_H
#define RAYCAST_H

#include "../../includes.h"

namespace graphics {

  class Raycast {
	public:
	  Raycast(double mouseX, double mouseY, double width, double height, glm::mat4 projection_matrix, glm::mat4 view_matrix) {

		float x = (2.0f * mouseX) / width - 1.0f;
		float y = 1.0f - (2.0f * mouseY) / height;

		glm::vec2 ray_nds = glm::vec2(x, y);
		glm::vec4 ray_clip = glm::vec4(ray_nds, -1.0, 1.0);
		glm::vec4 ray_eye = glm::inverse(projection_matrix) * ray_clip;
		ray_eye = glm::vec4(glm::vec2(ray_eye.x, ray_eye.y), -1.0, 0.0);
		glm::vec3 ray_wor = glm::inverse(view_matrix) * ray_eye;

		rayWorldCoords = glm::normalize(ray_wor);
	  }

	  // TODO: Implement
	  bool rayPlaneIntersection() {

	  }

	  bool didHit() {
		return hit;
	  }

	private:
	  bool hit;
	  glm::vec3 rayWorldCoords;

  };

}

#endif
