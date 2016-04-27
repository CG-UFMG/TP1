#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>

using namespace std;

class Shader {
    public:
        GLuint program;

        Shader(const GLchar* vPath, const GLchar* fPath);
        ~Shader();

        void use();

    private:
        static const GLuint INFO_LOG_SIZE = 512;

        const GLchar* openShaderFile(const GLchar* path);

        GLuint compileShader(const GLchar* shader, GLenum shaderType);
};

#endif
