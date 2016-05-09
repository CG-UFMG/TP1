#include "game.h"

Game::Game(GLuint width, GLuint height) : width(width), height(height), state(GAME_START), playerEnabled(GL_TRUE) {
    this->soundEngine = irrklang::createIrrKlangDevice();
}

Game::~Game() {
}

void Game::init() {
    // Load Sounds
    this->soundEngine->play2D("audio/background.mp3", GL_TRUE);

    // Load shaders
    ResourceManager::loadShader("shaders/sprite.vs", "shaders/sprite.frag", NULL, "sprite");
    ResourceManager::loadShader("shaders/text.vs", "shaders/text.frag", NULL, "text");

    // Configure shaders
    glm::mat4 spriteProjection = glm::ortho(0.0f, static_cast<GLfloat>(this->width), static_cast<GLfloat>(this->height), 0.0f, -1.0f, 1.0f);
    glm::mat4 textProjection = glm::ortho(0.0f, static_cast<GLfloat>(this->width), 0.0f, static_cast<GLfloat>(this->height));

    ResourceManager::getShader("sprite").use().setInteger("image", 0).setMatrix4("projection", spriteProjection);
    ResourceManager::getShader("text").use().setMatrix4("projection", textProjection);

    // Load textures
    ResourceManager::loadTexture("textures/paddle.png", GL_FALSE, "paddle");
    ResourceManager::loadTexture("textures/background.jpg", GL_FALSE, "background");
    ResourceManager::loadTexture("textures/ball.png", GL_TRUE, "ball");
    ResourceManager::loadTexture("textures/block.png", GL_FALSE, "block");
    ResourceManager::loadTexture("textures/block_solid.png", GL_FALSE, "block_solid");
    ResourceManager::loadTexture("textures/speedup.png", GL_TRUE, "speed");
    ResourceManager::loadTexture("textures/stickpaddle.png", GL_TRUE, "stick");
    ResourceManager::loadTexture("textures/increasepaddle.png", GL_TRUE, "increase");
    ResourceManager::loadTexture("textures/passball.png", GL_TRUE, "pass");

    // Set render-specific controls
    renderer = new SpriteRenderer(ResourceManager::getShader("sprite"));
    textRenderer = new TextRenderer(ResourceManager::getShader("text"), "fonts/Arcade.ttf");

    // Load player
    player = Player(this->width, this->height);

    // Load Ball
    glm::vec2 ballPos = player.paddle->position + glm::vec2(PLAYER_SIZE.x / 2 - BALL_RADIUS, -BALL_RADIUS * 2);
    ball = Ball(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY, ResourceManager::getTexture("ball"));

    // Load levels
    this->levels.push_back(BreakoutLevel("levels/1.blv", this->width, this->height * 0.5));
    this->levels.push_back(BreakoutLevel("levels/2.blv", this->width, this->height * 0.5));
    this->levels.push_back(BreakoutLevel("levels/3.blv", this->width, this->height * 0.5));
    this->levels.push_back(BreakoutLevel("levels/4.blv", this->width, this->height * 0.5));

    this->currentLevel = 0;
}

void Game::movePlayer(GLfloat delta, double xpos, double ypos) {
    if ((this->state == GAME_ACTIVE || this->state == GAME_PLAYER_DEAD) && this->playerEnabled) {

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
    if (this->state == GAME_ACTIVE || this->state == GAME_PLAYER_DEAD) {
        this->ball.move(delta, this->width);
        this->levels[this->currentLevel].moveBlocks(delta);
        this->updatePowerUps(delta);
        this->checkBlocksCollision();
        this->checkPlayerCollision();
        this->checkPowerUpsCollision();
        this->checkPlayerDeath();
        this->checkNextLevel();
    }
}

void Game::processInput(GLfloat delta) {
    if (this->keys[GLFW_KEY_SPACE]) {
        this->ball.isStuck = false;
        this->state = GAME_ACTIVE;
    }
}

void Game::checkBlocksCollision() {
    BreakoutLevel *lvl = &this->levels[this->currentLevel];

    for(vector<RenderObject>::iterator it = lvl->blocks.begin(); it != lvl->blocks.end(); ++it)
        if (!it->destroyed) {
            CollisionData collData = this->ball.checkCollision(&*it);

            if (collData.isCollision) {

                if (!it->isSolid) {
                    it->destroyed = GL_TRUE;
                    this->soundEngine->play2D("audio/non-solid.wav");
                    this->player.points++;
                    this->spawnPowerUps(&*it);
                } else {
                    this->soundEngine->play2D("audio/solid.wav");
                }

                Direction direction = collData.direction;
                glm::vec2 difference = collData.difference;

                if (!this->ball.isPassable || it->isSolid) {
                    if (direction == LEFT || direction == RIGHT) {
                        GLfloat penetration = this->ball.radius - abs(difference.x);
                        this->ball.velocity.x = this->ball.velocity.x;
                        this->ball.position.x += (direction == LEFT ? penetration : -penetration);
                    } else {
                        GLfloat penetration = this->ball.radius - abs(difference.y);
                        this->ball.velocity.y = -this->ball.velocity.y;
                        this->ball.position.y += (direction == UP ? -penetration : penetration);
                    }
                }
            }
        }
}

void Game::checkPlayerCollision() {
    CollisionData data = this->ball.checkCollision(player.paddle);

    if (!this->ball.isStuck && data.isCollision) {
        GLfloat centerBoard = this->player.paddle->position.x + this->player.paddle->sizeOf.x / 2;
        GLfloat distance = (this->ball.position.x + this->ball.radius) - centerBoard;
        GLfloat percentage = distance / (this->player.paddle->sizeOf.x / 2);
        GLfloat strength = 2.0f;

        glm::vec2 oldVelocity = this->ball.velocity;

        this->ball.velocity.x = INITIAL_BALL_VELOCITY.x * percentage * strength;
        this->ball.velocity.y = -this->ball.velocity.y;
        this->ball.velocity = glm::normalize(this->ball.velocity) * glm::length(oldVelocity);
        this->ball.velocity.y = -1 * abs(this->ball.velocity.y);
        this->ball.isStuck = this->ball.isStick;

        this->soundEngine->play2D("audio/paddle.wav");
    }
}

void Game::checkPowerUpsCollision() {
    for(vector<PowerUp>::iterator it = this->powerUps.begin(); it != this->powerUps.end(); ++it) {
        if (!it->destroyed) {
            if (it->position.y >= this->height)
                it->destroyed = GL_TRUE;
            else if (it->checkCollision(this->player.paddle).isCollision) {
                this->activePowerUp(&*it);
                this->soundEngine->play2D("audio/powerup.wav");
                it->destroyed = GL_TRUE;
                it->active = GL_TRUE;
            }
        }
    }
}

void Game::checkPlayerDeath() {
    if (this->ball.position.y >= this->height) {
        this->player.lifes--;
        this->player.paddle->position = this->player.initialPos;
        this->ball.reset(this->ball.initialPos, INITIAL_BALL_VELOCITY);
        this->soundEngine->play2D("audio/dead.wav");

        if (this->player.lifes == 0)
            this->reset();
    }
}

void Game::render() {
    renderer->drawSprite(ResourceManager::getTexture("background"), glm::vec2(0, 0), glm::vec2(this->width, this->height), 0.0f);

    if (this->state != GAME_WIN)
        this->levels[this->currentLevel].drawLevel(*renderer);

    this->player.draw(*renderer);
    this->ball.draw(*renderer);

    switch(this->state) {
        case GAME_PLAYER_DEAD:
        case GAME_ACTIVE:
            this->printPlayerStatus();
            this->renderPowerUps();
            break;
        case GAME_WIN:
            textRenderer->drawText("VOCE GANHOU!!!", 270.0f, 350.0f, 0.7f, glm::vec3(0.81f, 0.71f, 0.23f));
            textRenderer->drawText("PRESSIONE Q PARA SAIR...", 210.0f, 320.0f, 0.7f, glm::vec3(1.0f));
            break;
        case GAME_PAUSE:
            textRenderer->drawText("JOGO PAUSADO...", 300.0f, 250.0f, 0.7f, glm::vec3(1.0f, 0.0f, 0.0f));
            this->printPlayerStatus();
            break;
        case GAME_START:
            textRenderer->drawText("BEM VINDO AO BREAKOUT - TP1 - CG", 160.0f, 250.0f, 0.6f, glm::vec3(1.0f, 1.0f, 0.0f));
            textRenderer->drawText("PRESSIONE A TECLA DE ESPACO PARA JOGAR...", 100.0f, 220.0f, 0.6f, glm::vec3(1.0f));
            break;
        case GAME_NEXT_LEVEL:
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
    this->levels[this->currentLevel].reset();
    this->player.reset();
    this->ball.reset(this->ball.initialPos, INITIAL_BALL_VELOCITY);
    this->state = GAME_START;
}

void Game::checkNextLevel() {
    if (this->levels[this->currentLevel].isCompleted()) {
        if (this->currentLevel == this->levels.size() - 1)
            this->state = GAME_WIN;
        else {
            this->currentLevel++;
            this->player.reset();
            this->ball.reset(this->ball.initialPos, INITIAL_BALL_VELOCITY);
            this->state = GAME_NEXT_LEVEL;
            this->soundEngine->play2D("audio/win.wav");
        }
    }
}

void Game::printPlayerStatus() {
    ostringstream lifes, points, level;

    level << "Nivel: " << this->currentLevel + 1;
    lifes << "Vidas: " << this->player.lifes;
    points << "Pontos: " << this->player.points;

    textRenderer->drawText(level.str(), 15.0f, 560.0f, 0.6f, glm::vec3(1.0f));
    textRenderer->drawText(lifes.str(), 25.0f, 25.0f, 0.5f, glm::vec3(1.0f));
    textRenderer->drawText(points.str(), 25.0f, 50.0f, 0.5f, glm::vec3(1.0f));
}

void Game::printGameStatus() {
    this->player.printDebugData();
    this->ball.printDebugData();
    this->levels[this->currentLevel].printDebugData();
    this->state = GAME_PAUSE;
}

void Game::spawnPowerUps(RenderObject *object) {
    if (PowerUp::spawnChance(60))
        this->powerUps.push_back(PowerUp("speed", glm::vec3(0.5f, 0.5f, 1.0f), 0.0f, object->position, ResourceManager::getTexture("speed")));
    if (PowerUp::spawnChance(60))
        this->powerUps.push_back(PowerUp("sticky", glm::vec3(1.0f, 0.5f, 1.0f), 20.0f, object->position, ResourceManager::getTexture("stick")));
    if (PowerUp::spawnChance(60))
        this->powerUps.push_back(PowerUp("pass", glm::vec3(0.5f, 1.0f, 0.5f), 10.0f, object->position, ResourceManager::getTexture("pass")));
    if (PowerUp::spawnChance(60))
        this->powerUps.push_back(PowerUp("pad-size-increase",glm::vec3(1.0f, 0.6f, 0.4), 20.0f, object->position, ResourceManager::getTexture("increase")));
}

void Game::renderPowerUps() {
    for(vector<PowerUp>::iterator it = this->powerUps.begin(); it != this->powerUps.end(); ++it)
        if (!it->destroyed)
            it->draw(*renderer);
}

void Game::updatePowerUps(GLfloat delta) {
    for(vector<PowerUp>::iterator it = this->powerUps.begin(); it != this->powerUps.end(); ++it) {
        it->position += it->velocity * delta;

        if (it->active) {
            it->duration -= delta;
            if (it->duration <= 0.0f) {
                it->active = GL_FALSE;
                if (!this->hasAnotherPowerUp(it->type)) {
                    if (it->type == "sticky") {
                        this->ball.isStick = GL_FALSE;
                        this->player.paddle->color = glm::vec3(1.0f);
                    } else if (it->type == "pass") {
                        this->ball.isPassable = GL_FALSE;
                        this->ball.color = glm::vec3(1.0f);
                    } else if (it->type == "pad-size-increase") {
                        this->player.paddle->sizeOf.x -= 50;
                    }
                }
            }
        }
    }
}

void Game::activePowerUp(PowerUp *powerUp) {
    if (powerUp->type == "speed") {
        this->ball.velocity *= 1.3;
    } else if (powerUp->type == "sticky") {
        this->ball.isStick = GL_TRUE;
        this->player.paddle->color = glm::vec3(1.0f, 0.5f, 1.0f);
    } else if (powerUp->type == "pass") {
        this->ball.isPassable = GL_TRUE;
        this->ball.color = glm::vec3(1.0f, 0.5f, 0.5f);
    } else if (powerUp->type == "pad-size-increase") {
        this->player.paddle->sizeOf.x += 50;
    }
}

GLboolean Game::hasAnotherPowerUp(string type) {
    for(vector<PowerUp>::iterator it = this->powerUps.begin(); it != this->powerUps.end(); ++it)
        if (it->active && it->type == type)
            return GL_TRUE;
    return GL_FALSE;
}
