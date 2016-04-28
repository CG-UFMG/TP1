#include "resource_manager.h"

map<string, Texture> ResourceManager::textures;
map<string, Shader> ResourceManager::shaders;

Shader ResourceManager::loadShader(const GLchar *shaderPath, const GLchar *fragmentPath, const GLchar *geometryPath, string name) {
    Shader shader;
    shader.compile(shaderPath, fragmentPath, geometryPath);
    shaders[name] = shader;

    return shaders[name];
}

Shader ResourceManager::getShader(string name) {
    return shaders[name];
}

Texture ResourceManager::loadTexture(const GLchar *path, GLboolean alpha, string name) {
    Texture texture;
    texture.generateTexture(path, alpha);
    textures[name] = texture;

    return textures[name];
}

Texture ResourceManager::getTexture(string name) {
    return textures[name];
}

void ResourceManager::clear() {
    for (map<string, Shader>::iterator it = shaders.begin(); it != shaders.end(); ++it)
        delete &it->second;
    for (map<string, Texture>::iterator it = textures.begin(); it != textures.end(); ++it)
        delete &it->second;
}
