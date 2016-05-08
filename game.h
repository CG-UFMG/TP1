#ifndef GAME_H
#define GAME_H

#include "resource_manager.h"
#include "sprite_renderer.h"
#include "breakout_level.h"
#include "player.h"
#include "text_renderer.h"
#include "ball.h"
#include "vector_direction.hpp"

#include <GLFW/glfw3.h>
#include <vector>
#include <sstream>

using namespace std;

const glm::vec2 INITIAL_BALL_VELOCITY(50.0f, -220.0f);

enum GameState {
    GAME_ACTIVE,
    GAME_PAUSE,
    GAME_WIN,
    GAME_START,
    GAME_NEXT_LEVEL,
    GAME_PLAYER_DEAD
};

struct CollisionData {
    GLboolean isCollision;
    Direction direction;
    glm::vec2 difference;
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
        void checkBlocksCollision();
        void checkPlayerCollision();
        void render();
        void pauseOrContinue();
        void reset();
        void nextLevel();
        void printGameStatus();

    private:
        CollisionData checkCollision(Ball ball, RenderObject *object);

        void printPlayerStatus();
};

#endif
