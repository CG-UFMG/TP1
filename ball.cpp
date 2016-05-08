#include "ball.h"

Ball::Ball() : RenderObject(), radius(10.0f), isStuck(true), isStick(false), isPassable(false) {
}

Ball::Ball(glm::vec2 pos, GLfloat radius, glm::vec2 velocity, Texture sprite)
    : RenderObject(pos, glm::vec2(radius * 2, radius * 2), sprite, glm::vec3(1.0f), velocity), radius(radius), isStuck(true), isStick(false), isPassable(false) {
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

void Ball::printDebugData() {
    cout << endl;
    cout << "======== Bola ========" << endl;
    cout << "Velocidade - X: " << this->velocity.x << " / Y: " << this->velocity.y << endl;
    cout << "Posicao - X: " << this->position.x << " / Y: " << this->position.y << endl;
}

void Ball::reset(glm::vec2 position, glm::vec2 velocity) {
    this->position = position;
    this->velocity = velocity;
    this->isStuck = GL_TRUE;
    this->isStick = GL_FALSE;
    this->isPassable = GL_FALSE;
}


CollisionData Ball::checkCollision(RenderObject *object) {
    CollisionData data;

    glm::vec2 center(this->position + this->radius);
    glm::vec2 aabb_half_extents(object->sizeOf.x / 2, object->sizeOf.y / 2);
    glm::vec2 aabb_center(object->position.x + aabb_half_extents.x, object->position.y + aabb_half_extents.y);
    glm::vec2 difference = center - aabb_center;
    glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
    glm::vec2 closest = aabb_center + clamped;

    difference = closest - center;

    if (glm::length(difference) <= this->radius) {
        data.difference = difference;
        data.direction = calculateDirection(difference);
        data.isCollision = GL_TRUE;
    } else {
        data.difference = glm::vec2(0, 0);
        data.direction = UP;
        data.isCollision = GL_FALSE;
    }

    return data;
}
