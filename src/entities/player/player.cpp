#include "player.h"

Player::Player(graphics::Window *w) : window(w) {
  position = glm::vec3(0.0f, 70.0f, 0.0f);
}

void Player::handleInput() {
  keyboardInput();
  mouseInput();
}

void Player::update(float deltaTime) {
  handleInput();
}


void Player::keyboardInput() {

}

void Player::mouseInput() {

}
