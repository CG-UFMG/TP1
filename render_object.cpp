#include "render_object.h"

RenderObject::RenderObject()
    : position(0, 0), sizeOf(1, 1), velocity(0.0f), color(1.0f), rotation(0.0f), sprite(), isSolid(false), destroyed(false) { }

RenderObject::RenderObject(glm::vec2 pos, glm::vec2 size, Texture sprite, glm::vec3 color, glm::vec2 velocity)
    : position(pos), sizeOf(size), velocity(velocity), color(color), rotation(0.0f), sprite(sprite), isSolid(false), destroyed(false) { }

void RenderObject::draw(SpriteRenderer &renderer) {
    renderer.drawSprite(this->sprite, this->position, this->sizeOf, this->rotation, this->color);
}
