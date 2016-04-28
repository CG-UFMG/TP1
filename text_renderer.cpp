#include "text_renderer.h"

//map<GLchar, Character> characters;

TextRenderer::TextRenderer(const Shader &shader, const GLchar *fontPath) {
    this->shader = shader;
    this->initRenderData(fontPath);
}

void TextRenderer::drawText(string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color) {
}

void TextRenderer::initRenderData(const GLchar *fontPath) {
    FT_Library ft;
    FT_Face face;

    if (FT_Init_FreeType(&ft)) {
        std::cout << "ERROR : Freetype could not init FreeType Library" << std::endl;
        return;
    }

    if (FT_New_Face(ft, fontPath, 0, &face)) {
        std::cout << "ERROR : Freetype failed to load font" << std::endl;
        return;
    }

    FT_Set_Pixel_Sizes(face, 0, 48);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

}
