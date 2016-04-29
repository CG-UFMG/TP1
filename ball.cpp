#include "ball.h"

Ball::Ball() : RenderObject(), radius(10.0f), isStuck(true) {
}

Ball::Ball(glm::vec2 pos, GLfloat radius, glm::vec2 velocity, Texture sprite)
    : RenderObject(pos, glm::vec2(radius * 2, radius * 2), sprite, glm::vec3(1.0f), velocity), radius(radius), isStuck(true) {
        this->initialPos = pos;
}

glm::vec2 Ball::move(GLfloat dt, GLuint screenWidth) {
    if (!this->isStuck) {
        this->position += this->velocity * dt;

        if (this->position.x <= 0.0f) {
            this->velocity.x = -this->velocity.x;
            this->position.x = 0.0f;
        }
        else if (this->position.x + this->sizeOf.x >= screenWidth) {
            this->velocity.x = -this->velocity.x;
            this->position.x = screenWidth - this->sizeOf.x;
        }
        if (this->position.y <= 0.0f) {
            this->velocity.y = -this->velocity.y;
            this->position.y = 0.0f;
        }
    }

    return this->position;
}

void Ball::reset(glm::vec2 position, glm::vec2 velocity) {
    this->position = position;
    this->velocity = velocity;
    this->isStuck = true;
}
