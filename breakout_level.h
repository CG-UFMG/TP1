#ifndef BREAKOUT_LEVEL_H_INCLUDED
#define BREAKOUT_LEVEL_H_INCLUDED

#define GLEW_STATIC
#include <GL/glew.h>
#include <glm.hpp>
#include <vector>

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

class BreakoutLevel {
    public:
        vector<RenderObject> blocks;

        BreakoutLevel() { }

        void loadLevel(const GLchar *file, GLuint levelWidth, GLuint levelHeight);
        void drawLevel(SpriteRenderer &renderer);

        GLboolean isCompleted();
    private:
        void init(vector<vector<GLuint> > tileData, GLuint levelWidth, GLuint levelHeight);
};

#endif // BREAKOUT_LEVEL_H_INCLUDED
