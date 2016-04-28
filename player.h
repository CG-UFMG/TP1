#ifndef PLAYER_H
#define PLAYER_H

#include <glm.hpp>

#include "render_object.h"
#include "sprite_renderer.h"
#include "resource_manager.h"

const glm::vec2 PLAYER_SIZE(100, 20);
const GLuint MAX_LIFES = 3;
const GLfloat PLAYER_VELOCITY = 3000.0f;

class Player {

    public:
        glm::vec2 initialPos;

        GLfloat velFactor;
        GLuint sWidth, sHeight;
        GLuint points;
        GLuint lifes;

        Player() { }
        Player(GLuint screenWidth, GLuint screenHeight);

        void move(GLfloat dt, double xpos, double ypos);
        void draw(SpriteRenderer &renderer);
        void reset();

    private:
        RenderObject *paddle;

};

#endif //PLAYER_H