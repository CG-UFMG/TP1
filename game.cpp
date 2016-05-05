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
    ResourceManager::loadTexture("textures/paddle.png", GL_FALSE, "paddle");
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
    if (this->state == GAME_ACTIVE) {
        this->ball.move(delta, this->width);
        this->checkBlocksCollision();
        this->checkPlayerCollision();

        if (this->ball.position.y >= this->height) {
            this->player.lifes--;
            this->player.paddle->position = this->player.initialPos;
            this->ball.reset(this->ball.initialPos, INITIAL_BALL_VELOCITY);

            if (this->player.lifes == 0)
                this->reset();
        }
    }
}

void Game::processInput(GLfloat delta) {
    if (this->state == GAME_ACTIVE)
        if (this->keys[GLFW_KEY_SPACE])
            this->ball.isStuck = false;
}

void Game::checkBlocksCollision() {
    BreakoutLevel *lvl = &this->levels[this->currentLevel];

    for(vector<RenderObject>::iterator it = lvl->blocks.begin(); it != lvl->blocks.end(); ++it)
        if (!it->destroyed) {
            CollisionData collData = checkCollision(this->ball, &*it);

            if (collData.isCollision) {

                if (!it->isSolid) {
                    it->destroyed = GL_TRUE;
                    this->player.points++;
                }

                Direction direction = collData.direction;
                glm::vec2 difference = collData.difference;

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

void Game::checkPlayerCollision() {
    CollisionData data = checkCollision(this->ball, player.paddle);

    if (!this->ball.isStuck && data.isCollision) {
        GLfloat centerBoard = this->player.paddle->position.x + this->player.paddle->sizeOf.x / 2;
        GLfloat distance = (this->ball.position.x + this->ball.radius) - centerBoard;
        GLfloat percentage = distance / (this->player.paddle->sizeOf.x / 2);
        GLfloat strength = 2.0f;

        glm::vec2 oldVelocity = this->ball.velocity;

        this->ball.velocity.x = INITIAL_BALL_VELOCITY.x * percentage * strength;
        this->ball.velocity.y = -this->ball.velocity.y;
        this->ball.velocity = glm::normalize(this->ball.velocity) * glm::length(oldVelocity);
    }
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
    this->levels[this->currentLevel].reset();
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

CollisionData Game::checkCollision(Ball ball, RenderObject *object) {
    CollisionData data;

    glm::vec2 center(ball.position + ball.radius);
    glm::vec2 aabb_half_extents(object->sizeOf.x / 2, object->sizeOf.y / 2);
    glm::vec2 aabb_center(object->position.x + aabb_half_extents.x, object->position.y + aabb_half_extents.y);
    glm::vec2 difference = center - aabb_center;
    glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
    glm::vec2 closest = aabb_center + clamped;

    difference = closest - center;

    if (glm::length(difference) <= ball.radius) {
        data.difference = difference;
        data.direction = calculateDirection(difference);
        data.isCollision = GL_TRUE;
    } else {
        data.difference = glm::vec2(0, 0);
        data.direction = UP;
        data.isCollision = GL_FALSE;
    }

    return data;
}
