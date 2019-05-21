#include "player.h"
#include "../../math/ray.h"

Player::Player(graphics::Window *window, World *world, graphics::Camera *camera) 
  : m_window(window), m_world(world), m_camera(camera) {

  position = m_camera->getPosition();
  rotation = m_camera->getFront();
}

void Player::handleInput() {

  // Update local values
  position = m_camera->getPosition();
  rotation = m_camera->getFront();


  // Can't spam click
  if (timer.getTime() > 2.0f) {
	m_canDig = true;
  }

  if (m_window->isMouseButtonPressed(0) && m_canDig) {

	for (Ray ray(position, m_camera->getYaw(), m_camera->getPitch()); ray.getLength() < 6; ray.step(0.05)) {
	  int x = ray.getEnd().x;
	  int y = ray.getEnd().y;
	  int z = ray.getEnd().z;

	  std::cout << x << ' ' << y << ' ' << z << '\n';

	  auto block = m_world->getBlock(x, y, z);

	  if(block != BlockId::Air) {
		m_world->editBlock(x, y, z, 0);
		timer.reset();
		m_canDig = false;
		break;
	  }
	}
  } else if (m_window->isMouseButtonPressed(1)) {

	glm::vec3 lastPosition {0.0f, 0.0f, 0.0f};

	for (Ray ray(position, m_camera->getYaw(), m_camera->getPitch()); ray.getLength() < 6; ray.step(0.05)) {
	  int x = ray.getEnd().x;
	  int y = ray.getEnd().y;
	  int z = ray.getEnd().z;

	  std::cout << x << ' ' << y << ' ' << z << '\n';
	  auto block = m_world->getBlock(x, y, z);

	  if (block != BlockId::Air) {
		m_world->editBlock(lastPosition.x, lastPosition.y, lastPosition.z, 1);
		break;
	  }

	  lastPosition = ray.getEnd();
	}
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
