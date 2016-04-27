#ifndef SHADER_H
#define SHADER_H

#define GLEW_STATIC
#include <GL/glew.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


using namespace std;

class Shader {
    public:
        static GLuint INFO_LOG_SIZE;

        GLuint program;

        Shader(const GLchar* vPath, const GLchar* fPath, const GLchar* gPath);
        Shader();
        ~Shader();

        Shader &use();

    private:
        const GLchar* openShaderFile(const GLchar* path);

        GLuint compileShader(const GLchar* shader, GLenum shaderType);
};

#endif
