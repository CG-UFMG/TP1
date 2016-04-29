#ifndef BALL_H
#define BALL_H

#include <glm.hpp>

#include "texture.h"
#include "render_object.h"
#include "sprite_renderer.h"

const GLfloat BALL_RADIUS = 13.0f;

class Ball : public RenderObject {
    public:
        GLfloat radius;
        GLboolean isStuck;
        glm::vec2 initialPos;

        Ball();
        Ball(glm::vec2 pos, GLfloat radius, glm::vec2 velocity, Texture sprite);

        glm::vec2 move(GLfloat dt, GLuint screenWidth);

        void reset(glm::vec2 position, glm::vec2 velocity);
};

#endif
