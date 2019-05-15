#ifndef PLAYER_H
#define PLAYER_H

#include "../entity.h"
#include "../../graphics/window.h"

class Player : public Entity {
  public:
	Player(graphics::Window *w);
	void handleInput();
	void update(float deltaTime);

  private:
	void keyboardInput();
	void mouseInput();

	glm::vec3 velocity;
	graphics::Window *window;

};

#endif
