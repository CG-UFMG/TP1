#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <glm.hpp>

#include "texture.h"
#include "sprite_renderer.h"

class RenderObject {
    public:
        glm::vec2   position, sizeOf, velocity;
        glm::vec3   color;
        GLfloat     rotation;
        GLboolean   isSolid;
        GLboolean   destroyed;

        Texture   sprite;

        RenderObject();
        RenderObject(glm::vec2 pos, glm::vec2 size, Texture sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));

        virtual void draw(SpriteRenderer &renderer);
};

#endif // RENDEROBJECT_H
