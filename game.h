#ifndef GAME_H
#define GAME_H

#include "resource_manager.h"
#include "sprite_renderer.h"
#include "breakout_level.h"
#include "player.h"

#include <GLFW/glfw3.h>
#include <vector>

using namespace std;

enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

class Game {
    public:
        GLuint width, height;
        GameState state;
        Player player;

        vector<BreakoutLevel> levels;
        GLuint currentLevel;

        SpriteRenderer *renderer;

        Game(GLuint width, GLuint height);
        ~Game();

        void init();
        void processInput(GLfloat delta);
        void update(GLfloat delta);
        void render();
};

#endif
