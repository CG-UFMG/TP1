#ifndef BREAKOUT_LEVEL_H_INCLUDED
#define BREAKOUT_LEVEL_H_INCLUDED

#define GLEW_STATIC
#include <GL/glew.h>
#include <glm.hpp>
#include <vector>
#include <stdlib.h>

#include "render_object.h"
#include "sprite_renderer.h"
#include "resource_manager.h"

using namespace std;

enum BlockColor {
    SOLID = 1,
    GREEN,
    RED,
    BLUE,
    GRAY,
    WHITE,
    YELLOW,
    MEDIUM_AQUAMARINE,
    PINK,
    SALMON,
    OLD_GOLD,
    SCARLET
};

const GLuint BLOCK_HORIZONTAL_VELOCITY = 500;

class BreakoutLevel {
    public:
        GLuint levelWidth;

        vector<RenderObject> blocks;

        BreakoutLevel() { }
        BreakoutLevel(const GLchar *file, GLuint levelWidth, GLuint levelHeight);

        void loadLevel(const GLchar *file, GLuint levelWidth, GLuint levelHeight);
        void drawLevel(SpriteRenderer &renderer);
        void reset();
        void printDebugData();
        void moveBlocks(GLfloat delta);

        GLboolean isCompleted();
    private:
        void init(vector<vector<GLint> > tileData, GLuint levelWidth, GLuint levelHeight);
};

#endif // BREAKOUT_LEVEL_H_INCLUDED
