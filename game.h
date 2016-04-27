#ifndef GAME_H
#define GAME_H

#include <GLFW/glfw3.h>

class Game {
    public:
        GLuint width, height;

        Game(GLuint width, GLuint height);
        ~Game();

        void init();
        void processInput(GLfloat delta);
        void update(GLfloat delta);
        void render();
};

#endif
