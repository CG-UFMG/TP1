#include "game.h"

Game::Game(GLuint width, GLuint height) : width(width), height(height), state(GAME_ACTIVE), playerEnabled(GL_TRUE) {

}

Game::~Game() {
}

void Game::init() {
    // Load shaders
    ResourceManager::loadShader("shaders/sprite.vs", "shaders/sprite.frag", NULL, "sprite");
    ResourceManager::loadShader("shaders/text.vs", "shaders/text.frag", NULL, "text");

    // Configure shaders
    glm::mat4 spriteProjection = glm::ortho(0.0f, static_cast<GLfloat>(this->width), static_cast<GLfloat>(this->height), 0.0f, -1.0f, 1.0f);
    glm::mat4 textProjection = glm::ortho(0.0f, static_cast<GLfloat>(this->width), 0.0f, static_cast<GLfloat>(this->height));

    ResourceManager::getShader("sprite").use().setInteger("image", 0).setMatrix4("projection", spriteProjection);
    ResourceManager::getShader("text").use().setMatrix4("projection", textProjection);

    // Load textures
    ResourceManager::loadTexture("textures/background.jpg", GL_FALSE, "background");
    ResourceManager::loadTexture("textures/ball.png", GL_TRUE, "ball");
    ResourceManager::loadTexture("textures/block.png", GL_FALSE, "block");
    ResourceManager::loadTexture("textures/block_solid.png", GL_FALSE, "block_solid");

    // Set render-specific controls
    renderer = new SpriteRenderer(ResourceManager::getShader("sprite"));
    textRenderer = new TextRenderer(ResourceManager::getShader("text"), "fonts/Arcade.ttf");

    // Load levels
    BreakoutLevel basic;
    basic.loadLevel("levels/basic.blv", this->width, this->height * 0.5);

    // Load player
    player = Player(this->width, this->height);

    // Load Ball
    glm::vec2 ballPos = player.paddle->position + glm::vec2(PLAYER_SIZE.x / 2 - BALL_RADIUS, -BALL_RADIUS * 2);
    ball = Ball(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY, ResourceManager::getTexture("ball"));

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

        GLfloat velocity = this->player.move(delta, xpos, ypos);

        if (this->ball.isStuck)
            this->ball.position.x += velocity;
    }
}

void Game::update(GLfloat delta) {
    if (this->state == GAME_ACTIVE)
        this->ball.move(delta, this->width);
}

void Game::processInput(GLfloat delta) {
    if (this->state == GAME_ACTIVE)
        if (this->keys[GLFW_KEY_SPACE])
            this->ball.isStuck = false;
}

void Game::render() {
    switch(this->state) {
    case GAME_ACTIVE:
        break;
    case GAME_MENU:
        break;
    case GAME_WIN:
        break;
    case GAME_PAUSE:
        break;
    }

    renderer->drawSprite(ResourceManager::getTexture("background"), glm::vec2(0, 0), glm::vec2(this->width, this->height), 0.0f);

    this->levels[this->currentLevel].drawLevel(*renderer);
    this->player.draw(*renderer);
    this->ball.draw(*renderer);
    this->printPlayerStatus();
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
    this->ball.reset(this->ball.initialPos, INITIAL_BALL_VELOCITY);
}

void Game::printPlayerStatus() {
    ostringstream lifes, points;

    lifes << "Vidas: " << this->player.lifes;
    points << "Pontos: " << this->player.points;

    textRenderer->drawText(lifes.str(), 25.0f, 25.0f, 0.5f, glm::vec3(1.0f));
    textRenderer->drawText(points.str(), 25.0f, 50.0f, 0.5f, glm::vec3(1.0f));
}
