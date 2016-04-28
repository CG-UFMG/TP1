#ifndef PLAYER_H
#define PLAYER_H

#include <glm.hpp>

#include "render_object.h"
#include "sprite_renderer.h"
#include "resource_manager.h"

const glm::vec2 PLAYER_SIZE(100, 20);

class Player {

    public:
        Player() { }
        Player(GLuint screenWidth, GLuint screenHeight);

        void move(GLfloat dt);
        void draw(SpriteRenderer &renderer);

    private:
        RenderObject *paddle;

};

#endif //PLAYER_H
