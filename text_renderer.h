#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <string>
#include <map>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "shader.h"

using namespace std;

struct Character {
    GLuint textureID;
    glm::ivec2 size;
    glm::ivec2 bearing;
    GLuint advance;
};

class TextRenderer {
    public:
        TextRenderer(const Shader &shader, const GLchar *fontPath);
        ~TextRenderer();

        void drawText(string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
    private:
        Shader shader;
        GLuint quadVAO;

        void initRenderData(const GLchar *fontPath);
};

#endif
