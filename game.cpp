#include "game.h"

Game::Game(GLuint width, GLuint height) : width(width), height(height), state(GAME_ACTIVE), playerEnabled(GL_TRUE) {

}

Game::~Game() {
}

void Game::init() {
    // Load shaders
    ResourceManager::loadShader("shaders/sprite.vs", "shaders/sprite.frag", NULL, "sprite");

    // Configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->width), static_cast<GLfloat>(this->height), 0.0f, -1.0f, 1.0f);
    ResourceManager::getShader("sprite").use().setInteger("image", 0).setMatrix4("projection", projection);

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

    // Load player
    player = Player(this->width, this->height);

    // Load basic level
    this->levels.push_back(basic);
    this->currentLevel = 0;
}

void Game::movePlayer(GLfloat delta, double xpos, double ypos) {
    if (this->state == GAME_ACTIVE && this->playerEnabled) {

        if (xpos < 400)
            xpos = -(int)(this->width / 2) + xpos;
        if (xpos > 400)
            xpos = -((int)(this->width / 2) - xpos);
        if (xpos == 400)
            xpos = 0;

        this->player.move(delta, xpos, ypos);
    }
}

void Game::update(GLfloat delta) {

}

void Game::render() {
    switch(this->state) {
    case GAME_ACTIVE:
        renderer->drawSprite(ResourceManager::getTexture("background"), glm::vec2(0, 0), glm::vec2(this->width, this->height), 0.0f);
        this->levels[this->currentLevel].drawLevel(*renderer);
        this->player.draw(*renderer);
        break;
    case GAME_MENU:
        break;
    case GAME_WIN:
        break;
    case GAME_PAUSE:
        break;
    }
}

void Game::pauseOrContinue() {
    if (this->state == GAME_ACTIVE)
        this->state = GAME_PAUSE;
    else if (this->state == GAME_PAUSE)
        this->state = GAME_ACTIVE;
}

void Game::reset() {
    this->currentLevel = 0;
    this->player.reset();
}
