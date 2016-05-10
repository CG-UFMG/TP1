#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>

#include "texture.h"
#include "shader.h"

using namespace std;

class ResourceManager {
    public:
        static map<string, Shader> shaders;
        static map<string, Texture> textures;

        static Shader loadShader(const GLchar *shaderPath, const GLchar *fragmentPath, const GLchar *geometryPath, string name);
        static Shader getShader(string name);

        static Texture loadTexture(const GLchar *path, GLboolean alpha, string name);
        static Texture getTexture(string name);

        static void clear();
};

#endif // RESOURCE_MANAGER_H
