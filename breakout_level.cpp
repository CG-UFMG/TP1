#include "breakout_level.h"

#include <fstream>
#include <sstream>

BreakoutLevel::BreakoutLevel(const GLchar *file, GLuint levelWidth, GLuint levelHeight) {
    loadLevel(file, levelWidth, levelHeight);
}

void BreakoutLevel::loadLevel(const GLchar *file, GLuint levelWidth, GLuint levelHeight) {
    this->blocks.clear();
    this->levelWidth = levelWidth;

    GLuint tileCode;
    BreakoutLevel level;
    string line;
    ifstream fstream(file);
    vector<vector<GLint> > tileData;

    if (fstream) {
        while (getline(fstream, line)) {
            istringstream sstream(line);
            vector<GLint> row;
            while (sstream >> tileCode)
                row.push_back(tileCode);
            tileData.push_back(row);
        }

        if (tileData.size() > 0)
            this->init(tileData, levelWidth, levelHeight);
    }
}

void BreakoutLevel::drawLevel(SpriteRenderer &renderer) {
    for(vector<RenderObject>::iterator it = this->blocks.begin(); it != this->blocks.end(); ++it)
        if (!it->destroyed)
            it->draw(renderer);
}

void BreakoutLevel::moveBlocks(GLfloat delta) {
    for(vector<RenderObject>::iterator it = this->blocks.begin(); it != this->blocks.end(); ++it)
        if (!it->destroyed && it->velocity != glm::vec2(0.0f)) {
            it->position += it->velocity * delta;

            if (it->position.x <= 0.0f) {
                it->velocity.x = -it->velocity.x;
                it->position.x = 0.0f;
            } else if (it->position.x + it->sizeOf.x >= this->levelWidth) {
                it->velocity.x = -it->velocity.x;
                it->position.x = this->levelWidth - it->sizeOf.x;
            }
        }
}

GLboolean BreakoutLevel::isCompleted() {
    for(vector<RenderObject>::iterator it = this->blocks.begin(); it != this->blocks.end(); ++it)
        if (!it->isSolid && !it->destroyed)
            return GL_FALSE;
    return GL_TRUE;
}

void BreakoutLevel::init(vector<vector<GLint> > tileData, GLuint levelWidth, GLuint levelHeight) {
    GLuint height = tileData.size();
    GLuint width = tileData[0].size();
    GLfloat unit_width = levelWidth / static_cast<GLfloat>(width), unit_height = levelHeight / height;

    for (GLuint y = 0; y < height; ++y) {
        for (GLuint x = 0; x < width; ++x) {
            if (tileData[y][x] != 0) {
                BlockColor color = static_cast<BlockColor>(abs(tileData[y][x]));
                RenderObject obj(glm::vec2(unit_width * x, unit_height * y), glm::vec2(unit_width, unit_height), ResourceManager::getTexture("block"));

                // Block movement
                if (tileData[y][x] < 0)
                    obj.velocity = glm::vec2(rand() % BLOCK_HORIZONTAL_VELOCITY, 0);

                switch(color) {
                    case SOLID:
                        obj.color = glm::vec3(0.8f, 0.8f, 0.7f);
                        obj.sprite = ResourceManager::getTexture("block_solid");
                        obj.isSolid = GL_TRUE;
                        break;
                    case GREEN:
                        obj.color = glm::vec3(0.0f, 1.0f, 0.0f);
                        break;
                    case RED:
                        obj.color = glm::vec3(1.0f, 0.0f, 0.0f);
                        break;
                    case BLUE:
                        obj.color = glm::vec3(0.0f, 0.0f, 1.0f);
                        break;
                    case WHITE:
                        obj.color = glm::vec3(1.0f);
                        break;
                    case GRAY:
                        obj.color = glm::vec3(0.50f, 0.50f, 0.50f);
                        break;
                    case YELLOW:
                        obj.color = glm::vec3(1.0f, 1.0f, 0.0f);
                        break;
                    case SCARLET:
                        obj.color = glm::vec3(0.55f, 0.9f, 0.9f);
                        break;
                    case OLD_GOLD:
                        obj.color = glm::vec3(0.81f, 0.71f, 0.23f);
                        break;
                    case SALMON:
                        obj.color = glm::vec3(0.435294f, 0.258824f, 0.258824f);
                        break;
                    case PINK:
                        obj.color = glm::vec3(0.737255f, 0.560784f, 0.560784f);
                        break;
                    case MEDIUM_AQUAMARINE:
                        obj.color = glm::vec3(0.196078f, 0.8f, 0.6f);
                        break;
                    default:
                        obj.color = glm::vec3(0.372549f, 0.623529f, 0.623529f);
                        break;
                }

                this->blocks.push_back(obj);
            }
        }
    }
}

void BreakoutLevel::printDebugData() {
    cout << endl;
    cout << "======== Blocos ========" << endl;
    for(vector<RenderObject>::iterator it = this->blocks.begin(); it != this->blocks.end(); ++it) {
        cout << "Posicao - X: " << it->position.x << " Y: " << it->position.y << endl;
        cout << "Tipo: " << (it->isSolid ? "Solido" : "Normal") << endl;
        cout << "Destruido: " << (it->destroyed ? "Sim" : "Nao") << endl;
    }
}

void BreakoutLevel::reset() {
    for(vector<RenderObject>::iterator it = this->blocks.begin(); it != this->blocks.end(); ++it)
        it->destroyed = GL_FALSE;
}
