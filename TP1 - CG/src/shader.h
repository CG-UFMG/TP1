#ifndef SHADER_H
#define SHADER_H

#define GLEW_STATIC
#include <GL/glew.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm.hpp>
#include <gtc/type_ptr.hpp>

using namespace std;

class Shader {
    public:
        static GLuint INFO_LOG_SIZE;

        GLuint program;

        Shader() { }
        Shader(const GLchar* vPath, const GLchar* fPath, const GLchar* gPath);

        Shader &use();

        Shader &setFloat    (const GLchar *name, GLfloat value, GLboolean useShader = false);
        Shader &setInteger  (const GLchar *name, GLint value, GLboolean useShader = false);
        Shader &setVector2f (const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader = false);
        Shader &setVector2f (const GLchar *name, const glm::vec2 &value, GLboolean useShader = false);
        Shader &setVector3f (const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
        Shader &setVector3f (const GLchar *name, const glm::vec3 &value, GLboolean useShader = false);
        Shader &setVector4f (const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
        Shader &setVector4f (const GLchar *name, const glm::vec4 &value, GLboolean useShader = false);
        Shader &setMatrix4  (const GLchar *name, const glm::mat4 &matrix, GLboolean useShader = false);

    private:
        const GLchar* openShaderFile(const GLchar* path);

        GLuint compileShader(const GLchar* shader, GLenum shaderType);
};

#endif
