#include "shader.h"

Shader::Shader(const GLchar* vPath, const GLchar* fPath, const GLchar* gPath) {
    GLint success;
    GLchar infoLog[Shader::INFO_LOG_SIZE];

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
        glGetProgramInfoLog(this->program, Shader::INFO_LOG_SIZE, NULL, infoLog);
        cout << "ERROR: SHADER PROGRAM LINKING FAILED. " << infoLog << endl;
    }

    // Delete shaders
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    if (gPath != NULL)
        glDeleteShader(geometry);
}

Shader::~Shader() {
    glDeleteProgram(this->program);
}

Shader &Shader::use() {
    glUseProgram(this->program);
    return *this;
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
    GLchar infoLog[Shader::INFO_LOG_SIZE];
    GLuint tmpShader = glCreateShader(shaderType);

    glShaderSource(tmpShader, 1, &shader, NULL);
    glCompileShader(tmpShader);
    glGetShaderiv(tmpShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(tmpShader, Shader::INFO_LOG_SIZE, NULL, infoLog);
        cout << "ERROR: SHADER:: " << shaderType << " COMPILATION FAILED. " << infoLog << endl;
    }

    return tmpShader;
}

