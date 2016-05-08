#include "player.h"

Player::Player(GLuint screenWidth, GLuint screenHeight) : sWidth(screenWidth), sHeight(screenHeight) {
    this->initialPos = glm::vec2(screenWidth / 2 - PLAYER_SIZE.x / 2, screenHeight - PLAYER_SIZE.y);
    this->velFactor = PLAYER_VELOCITY / this->sWidth;
    this->paddle = new RenderObject(this->initialPos, PLAYER_SIZE, ResourceManager::getTexture("paddle"));
    this->points = 0;
    this->lifes = MAX_LIFES;
    this->velocity = 0;
}

GLfloat Player::move(GLfloat delta, double xpos, double ypos) {
    this->velocity = velFactor * xpos * delta;

    if (velocity < 0 && this->paddle->position.x >= 0 || this->velocity > 0 && this->paddle->position.x <= this->sWidth - this->paddle->sizeOf.x)
        this->paddle->position.x += this->velocity;
    else
        this->velocity = 0;

    return this->velocity;
}

void Player::draw(SpriteRenderer &renderer) {
    this->paddle->draw(renderer);
}

void Player::reset() {
    this->paddle->position = initialPos;
    this->points = 0;
    this->lifes = MAX_LIFES;
}

void Player::printDebugData() {
    cout << endl;
    cout << "======== Player ========" << endl;
    cout << "Velocidade: " << this->velocity << endl;
    cout << "Posicao - X: " << this->paddle->position.x << " / Y: " << this->paddle->position.y << endl;
}
