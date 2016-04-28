#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <string>

#include "shader.h"

class TextRenderer {
    public:
        TextRenderer(const Shader &shader);
        ~TextRenderer();

        void drawText(string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
    private:
        Shader shader;
        GLuint quadVAO;

        void initRenderData();
};

#endif
