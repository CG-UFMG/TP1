#include "text_renderer.h"

TextRenderer::TextRenderer(const Shader &shader) {
    this->shader = shader;
    this->initRenderData();
}

void TextRenderer::drawText(string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color) {
}

void TextRenderer::initRenderData() {
}
