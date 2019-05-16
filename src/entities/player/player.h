#ifndef PLAYER_H
#define PLAYER_H

#include "../entity.h"
#include "../../graphics/window.h"
#include "../../world/world.h"
#include "../../graphics/camera.h"

class Player : public Entity {
  public:
	Player(graphics::Window *window, World *world, graphics::Camera *camera);
	void handleInput();
	void update(float deltaTime);

  private:
	void keyboardInput();
	void mouseInput();

	glm::vec3 velocity;
	graphics::Camera *m_camera;
	graphics::Window *m_window;
	World *m_world;

};

#endif
