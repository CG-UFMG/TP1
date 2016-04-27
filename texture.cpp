#include "texture.h"

Texture::Texture() : internalFormat(GL_RGB), imageFormat(GL_RGB), wrapS(GL_REPEAT), wrapT(GL_REPEAT), filterMin(GL_LINEAR), filterMax(GL_LINEAR) {
    glGenTextures(1, &this->texId);
}

Texture::~Texture() {
    glDeleteTextures(1, &this->texId);
}

Texture &Texture::generateFromFile(const GLchar* path, GLboolean alpha) {
    int width, height;
    unsigned char* image;

    if (alpha) {
        this->internalFormat = GL_RGBA;
        this->imageFormat = GL_RGBA;
    }

    image = SOIL_load_image(path, &width, &height, 0, this->imageFormat == GL_RGBA ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);

    glBindTexture(GL_TEXTURE_2D, this->texId);
    glTexImage2D(GL_TEXTURE_2D, 0, this->internalFormat, width, height, 0, this->imageFormat, GL_UNSIGNED_BYTE, image);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filterMax);

    glBindTexture(GL_TEXTURE_2D, 0);
    SOIL_free_image_data(image);

    return *this;
}

void Texture::bind() const {
    glBindTexture(GL_TEXTURE_2D, this->texId);
}
