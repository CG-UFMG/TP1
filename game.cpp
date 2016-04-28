#include "game.h"

Game::Game(GLuint width, GLuint height) : width(width), height(height) {

}

Game::~Game() {
}

void Game::init() {
    // Load shaders
    ResourceManager::loadShader("shaders/sprite.vs", "shaders/sprite.frag", NULL, "sprite");

    // Configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->width), static_cast<GLfloat>(this->height), 0.0f, -1.0f, 1.0f);
    ResourceManager::getShader("sprite").use();
    ResourceManager::getShader("sprite").setInteger("image", 0);
    ResourceManager::getShader("sprite").setMatrix4("projection", projection);

    // Load textures
    ResourceManager::loadTexture("textures/background.jpg", GL_FALSE, "background");
    ResourceManager::loadTexture("textures/awesomeface.png", GL_TRUE, "face");
    ResourceManager::loadTexture("textures/block.png", GL_FALSE, "block");
    ResourceManager::loadTexture("textures/block_solid.png", GL_FALSE, "block_solid");

    // Set render-specific controls
    renderer = new SpriteRenderer(ResourceManager::getShader("sprite"));

    // Load levels
    BreakoutLevel basic;
    basic.loadLevel("levels/basic.blv", this->width, this->height * 0.5);

    // Load basic level
    this->levels.push_back(basic);
    this->currentLevel = 0;
}

void Game::processInput(GLfloat delta) {

}

void Game::update(GLfloat delta) {

}

void Game::render() {
    renderer->drawSprite(ResourceManager::getTexture("background"), glm::vec2(0, 0), glm::vec2(this->width, this->height), 0.0f);

    this->levels[this->currentLevel].drawLevel(*renderer);
}
