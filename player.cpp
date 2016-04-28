#include "player.h"

Player::Player(GLuint screenWidth, GLuint screenHeight) : sWidth(screenWidth), sHeight(screenHeight) {
    this->initialPos = glm::vec2(screenWidth / 2 - PLAYER_SIZE.x / 2, screenHeight - PLAYER_SIZE.y);
    this->velFactor = PLAYER_VELOCITY / this->sWidth;
    this->paddle = new RenderObject(this->initialPos, PLAYER_SIZE, ResourceManager::getTexture("paddle"));
    this->points = 0;
    this->lifes = MAX_LIFES;
}

void Player::move(GLfloat delta, double xpos, double ypos) {
    GLfloat velocity = velFactor * xpos * delta;

    if (velocity < 0 && this->paddle->position.x >= 0 || velocity > 0 && this->paddle->position.x <= this->sWidth - this->paddle->sizeOf.x)
        this->paddle->position.x += velocity;
}

void Player::draw(SpriteRenderer &renderer) {
    this->paddle->draw(renderer);
}

void Player::reset() {
    this->paddle->position = initialPos;
    this->points = 0;
    this->lifes = MAX_LIFES;
}
