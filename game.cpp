#include "game.h"

SpriteRenderer *renderer;

Game::Game(GLuint width, GLuint height) : width(width), height(height) {

}

Game::~Game() {

}

void Game::init() {

    ResourceManager::loadShader("shaders/sprite.vs", "shaders/sprite.frag", NULL, "sprite");

    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->width),
        static_cast<GLfloat>(this->height), 0.0f, -1.0f, 1.0f);

    ResourceManager::getShader("sprite").use().setInteger("image", 0);
    ResourceManager::getShader("sprite").setMatrix4("projection", projection);

    renderer = new SpriteRenderer(ResourceManager::getShader("sprite"));

    ResourceManager::loadTexture("textures/awesomeface.png", GL_TRUE, "face");
}

void Game::processInput(GLfloat delta) {

}

void Game::update(GLfloat delta) {

}

void Game::render() {

}
