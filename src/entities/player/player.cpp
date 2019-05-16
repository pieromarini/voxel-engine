#include "player.h"
#include "../../math/ray.h"

Player::Player(graphics::Window *window, World *world, graphics::Camera *camera) 
  : m_window(window), m_world(world), m_camera(camera) {

  position = glm::vec3(0.0f, 70.0f, 0.0f);
  rotation = m_camera->getFront();
}

void Player::handleInput() {

  // Update local values
  position = m_camera->getPosition();
  rotation = m_camera->getFront();

  glm::vec3 lastPosition;

  if (graphics::Window::isMouseButtonPressed(0)) {

	// TODO: Fix raycasting direction. Right now its being shot directly down?
	for (Ray ray(position, rotation); ray.getLength() < 6; ray.step(0.1)) {
	  int x = ray.getEnd().x;
	  int y = ray.getEnd().y;
	  int z = ray.getEnd().z;

	  auto block = m_world->getBlock(x, y, z);

	  if(block != BlockId::Air) { // Not BlockId::Air
		m_world->editBlock(x, y, z, 0);
		break;
	  }
	  lastPosition = ray.getEnd();
	}
  /*
  } else if (graphics::Window::isMouseButtonPressed(1)) {
	m_world->editBlock(lastPosition.x, lastPosition.y, lastPosition.z, 1);
	break;
  */
  }

  keyboardInput();
  mouseInput();
}

void Player::update(float deltaTime) {

}


void Player::keyboardInput() {

}

void Player::mouseInput() {

}
