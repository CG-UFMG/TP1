#include "shader.h"

GLuint Shader::INFO_LOG_SIZE = 512;

void Shader::compile(const GLchar* vPath, const GLchar* fPath, const GLchar* gPath) {
    GLint success;
    GLchar infoLog[INFO_LOG_SIZE];

    // Compile vertex and fragment shader
    GLuint vertex = compileShader(openShaderFile(vPath), GL_VERTEX_SHADER);
    GLuint fragment = compileShader(openShaderFile(fPath), GL_FRAGMENT_SHADER);
    GLuint geometry;

    if (gPath != NULL)
        geometry = compileShader(openShaderFile(gPath), GL_GEOMETRY_SHADER);

    // Shader Program
    this->program = glCreateProgram();
    glAttachShader(this->program, vertex);
    glAttachShader(this->program, fragment);

    if (gPath != NULL)
        glAttachShader(this->program, geometry);

    glLinkProgram(this->program);
    glGetProgramiv(this->program, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(this->program, INFO_LOG_SIZE, NULL, infoLog);
        cout << "ERROR: SHADER PROGRAM LINKING FAILED. " << infoLog << endl;
    }

    // Delete shaders
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    if (gPath != NULL)
        glDeleteShader(geometry);
}

void Shader::use() {
    glUseProgram(this->program);
}

void Shader::setFloat(const GLchar *name, GLfloat value, GLboolean useShader) {
    if (useShader)
        this->use();
    glUniform1f(glGetUniformLocation(this->program, name), value);
}

void Shader::setInteger(const GLchar *name, GLint value, GLboolean useShader) {
    if (useShader)
        this->use();
    glUniform1i(glGetUniformLocation(this->program, name), value);
}

void Shader::setVector2f(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader) {
    if (useShader)
        this->use();
    glUniform2f(glGetUniformLocation(this->program, name), x, y);
}

void Shader::setVector2f(const GLchar *name, const glm::vec2 &value, GLboolean useShader) {
    if (useShader)
        this->use();
    glUniform2f(glGetUniformLocation(this->program, name), value.x, value.y);
}

void Shader::setVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader) {
    if (useShader)
        this->use();
    glUniform3f(glGetUniformLocation(this->program, name), x, y, z);
}

void Shader::setVector3f(const GLchar *name, const glm::vec3 &value, GLboolean useShader) {
    if (useShader)
        this->use();
    glUniform3f(glGetUniformLocation(this->program, name), value.x, value.y, value.z);
}

void Shader::setVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader) {
    if (useShader)
        this->use();
    glUniform4f(glGetUniformLocation(this->program, name), x, y, z, w);
}

void Shader::setVector4f(const GLchar *name, const glm::vec4 &value, GLboolean useShader) {
    if (useShader)
        this->use();
    glUniform4f(glGetUniformLocation(this->program, name), value.x, value.y, value.z, value.w);
}

void Shader::setMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader) {
    if (useShader)
        this->use();
    glUniformMatrix4fv(glGetUniformLocation(this->program, name), 1, GL_FALSE, glm::value_ptr(matrix));
}

const GLchar* Shader::openShaderFile(const GLchar* path) {
    string code = "";
    ifstream file;
    stringstream stream;

    file.exceptions(ifstream::badbit);

    try {
        file.open(path);
        stream << file.rdbuf();
        file.close();
        code = stream.str();
    } catch (ifstream::failure ex) {
        cout << "ERROR: FILE::" << path << " NOT READ." << endl;
    }

    return code.c_str();
}

GLuint Shader::compileShader(const GLchar* shader, GLenum shaderType) {
    GLint success;
    GLchar infoLog[INFO_LOG_SIZE];
    GLuint tmpShader = glCreateShader(shaderType);

    glShaderSource(tmpShader, 1, &shader, NULL);
    glCompileShader(tmpShader);
    glGetShaderiv(tmpShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(tmpShader, INFO_LOG_SIZE, NULL, infoLog);
        cout << "ERROR: SHADER:: " << shaderType << " COMPILATION FAILED. " << infoLog << endl;
    }

    return tmpShader;
}

