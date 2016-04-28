#include "breakout_level.h"

#include <fstream>
#include <sstream>

void BreakoutLevel::loadLevel(const GLchar *file, GLuint levelWidth, GLuint levelHeight) {
    this->blocks.clear();

    GLuint tileCode;
    BreakoutLevel level;
    string line;
    ifstream fstream(file);
    vector<vector<GLuint> > tileData;

    if (fstream) {
        while (getline(fstream, line)) {
            istringstream sstream(line);
            vector<GLuint> row;
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

GLboolean BreakoutLevel::isCompleted() {
    for(vector<RenderObject>::iterator it = this->blocks.begin(); it != this->blocks.end(); ++it)
        if (!it->isSolid && !it->destroyed)
            return GL_FALSE;
    return GL_TRUE;
}

void BreakoutLevel::init(vector<vector<GLuint> > tileData, GLuint levelWidth, GLuint levelHeight) {
    GLuint height = tileData.size();
    GLuint width = tileData[0].size();
    GLfloat unit_width = levelWidth / static_cast<GLfloat>(width), unit_height = levelHeight / height;

    for (GLuint y = 0; y < height; ++y) {
        for (GLuint x = 0; x < width; ++x) {
            if (tileData[y][x] == 1) {
                glm::vec2 pos(unit_width * x, unit_height * y);
                glm::vec2 size(unit_width, unit_height);
                RenderObject obj(pos, size, ResourceManager::getTexture("block_solid"), glm::vec3(0.8f, 0.8f, 0.7f));
                obj.isSolid = GL_TRUE;
                this->blocks.push_back(obj);
            }
            else if (tileData[y][x] > 1) {
                glm::vec3 color = glm::vec3(1.0f);
                if (tileData[y][x] == 2)
                    color = glm::vec3(0.2f, 0.6f, 1.0f);
                else if (tileData[y][x] == 3)
                    color = glm::vec3(0.0f, 0.7f, 0.0f);
                else if (tileData[y][x] == 4)
                    color = glm::vec3(0.8f, 0.8f, 0.4f);
                else if (tileData[y][x] == 5)
                    color = glm::vec3(1.0f, 0.5f, 0.0f);

                glm::vec2 pos(unit_width * x, unit_height * y);
                glm::vec2 size(unit_width, unit_height);
                this->blocks.push_back(RenderObject(pos, size, ResourceManager::getTexture("block"), color));
            }
        }
    }
}
