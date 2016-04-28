#ifndef TEXTURE_H
#define TEXTURE_H

#define GLEW_STATIC
#include <GL/glew.h>

#include <SOIL.h>

class Texture {
    public:
        GLuint texId;
        GLuint internalFormat;
        GLuint imageFormat;
        GLuint wrapS;
        GLuint wrapT;
        GLuint filterMin;
        GLuint filterMax;

        Texture();

        void generateTexture(const GLchar* path, GLboolean alpha);
        void bindTex() const;
};

#endif // TEXTURE_H
