#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#define GLEW_STATIC
#include <GL/glew.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "texture.h"
#include "shader.h"

class SpriteRenderer {
    public:
        SpriteRenderer(const Shader &shader);
        ~SpriteRenderer();

        void drawSprite(const Texture &texture, glm::vec2 position, glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));
    private:
        Shader shader;
        GLuint quadVAO;

        void initRenderData();
};

#endif
