#include "texture.h"

Texture::Texture(const GLchar* path, GLboolean alpha)
    : internalFormat(GL_RGB), imageFormat(GL_RGB), wrapS(GL_REPEAT), wrapT(GL_REPEAT), filterMin(GL_LINEAR), filterMax(GL_LINEAR) {
    int width, height;
    unsigned char* image;

    if (alpha) {
        this->internalFormat = GL_RGBA;
        this->imageFormat = GL_RGBA;
    }

    image = SOIL_load_image(path, &width, &height, 0, this->imageFormat == GL_RGBA ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);

    glGenTextures(1, &this->texId);
    glBindTexture(GL_TEXTURE_2D, this->texId);
    glTexImage2D(GL_TEXTURE_2D, 0, this->internalFormat, width, height, 0, this->imageFormat, GL_UNSIGNED_BYTE, image);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filterMax);

    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::bindTexture() const {
    glBindTexture(GL_TEXTURE_2D, this->texId);
}
