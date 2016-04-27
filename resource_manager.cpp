#include "resource_manager.h"

map<string, Texture> ResourceManager::textures;
map<string, Shader> ResourceManager::shaders;

Shader ResourceManager::loadShader(const GLchar *shaderPath, const GLchar *fragmentPath, const GLchar *geometryPath, string name) {
    shaders[name] = Shader(shaderPath, fragmentPath, geometryPath);
    return shaders[name];
}

Shader ResourceManager::getShader(string name) {
    return shaders[name];
}

Texture ResourceManager::loadTexture(const GLchar *path, GLboolean alpha, std::string name) {
    textures[name] = Texture().generateFromFile(path, alpha);
    return textures[name];
}

Texture ResourceManager::getTexture(std::string name) {
    return textures[name];
}

void ResourceManager::clear() {
    for (map<string, Shader>::iterator it = shaders.begin(); it != shaders.end(); ++it)
        delete &it->second;
    for (map<string, Texture>::iterator it = textures.begin(); it != textures.end(); ++it)
        delete &it->second;
}
