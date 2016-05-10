#ifndef POWER_UP_H
#define POWER_UP_H

#include "render_object.h"

#include <glm.hpp>
#include <stdlib.h>

const glm::vec2 SIZE(60, 20);
const glm::vec2 VELOCITY(0.0f, 150.0f);

class PowerUp : public RenderObject {
    public:
        GLfloat duration;
        GLboolean active;
        string type;

        PowerUp(string type, glm::vec3 color, GLfloat duration, glm::vec2 position, Texture texture);

        static GLboolean spawnChance(GLuint change);

};

#endif // POWER_UP_H

