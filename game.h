#ifndef GAME_H
#define GAME_H

#include "resource_manager.h"
#include "sprite_renderer.h"
#include "breakout_level.h"
#include "player.h"
#include "text_renderer.h"
#include "ball.h"

#include <GLFW/glfw3.h>
#include <vector>
#include <sstream>

using namespace std;

const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);

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
        GLboolean keys[1024];
        GameState state;
        Player player;
        Ball ball;

        vector<BreakoutLevel> levels;
        GLuint currentLevel;

        SpriteRenderer *renderer;
        TextRenderer *textRenderer;

        Game(GLuint width, GLuint height);
        ~Game();

        void init();
        void movePlayer(GLfloat delta, double xpos, double ypos);
        void update(GLfloat delta);
        void processInput(GLfloat delta);
        void render();
        void pauseOrContinue();
        void reset();
    private:
        void printPlayerStatus();
};

#endif
