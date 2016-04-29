#ifndef GAME_H
#define GAME_H

#include "resource_manager.h"
#include "sprite_renderer.h"
#include "breakout_level.h"
#include "player.h"
#include "text_renderer.h"

#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

enum GameState {
    GAME_ACTIVE,
    GAME_PAUSE,
    GAME_MENU,
    GAME_WIN
};

class Game {
    public:
        GLuint width, height;
        GLboolean playerEnabled;
        GameState state;
        Player player;

        vector<BreakoutLevel> levels;
        GLuint currentLevel;

        SpriteRenderer *renderer;
        TextRenderer *textRenderer;

        Game(GLuint width, GLuint height);
        ~Game();

        void init();
        void movePlayer(GLfloat delta, double xpos, double ypos);
        void update(GLfloat delta);
        void render();
        void pauseOrContinue();
        void reset();
    private:
        void printPlayerStatus();
};

#endif
