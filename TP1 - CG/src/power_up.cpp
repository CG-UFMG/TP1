#include "power_up.h"

PowerUp::PowerUp(string type, glm::vec3 color, GLfloat duration, glm::vec2 position, Texture texture)
    : RenderObject(position, SIZE, texture, color, VELOCITY), type(type), duration(duration), active() {

}

GLboolean PowerUp::spawnChance(GLuint chance) {
    GLuint random = rand() % chance;
    return random == 0;
}
