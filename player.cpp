#include "player.h"

Player::Player(GLuint screenWidth, GLuint screenHeight) {
    glm::vec2 playerPos = glm::vec2(screenWidth / 2 - PLAYER_SIZE.x / 2, screenHeight - PLAYER_SIZE.y);
    paddle = new RenderObject(playerPos, PLAYER_SIZE, ResourceManager::getTexture("paddle"));
}

void Player::move(GLfloat delta) {
}

void Player::draw(SpriteRenderer &renderer) {
    this->paddle->draw(renderer);
}
