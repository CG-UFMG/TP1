#ifndef VECTOR_DIRECTION_H
#define VECTOR_DIRECTION_H

#include <glm.hpp>

enum Direction {
    UP, DOWN, LEFT, RIGHT
};

inline Direction calculateDirection(glm::vec2 vec) {
    glm::vec2 compass[] = {
        glm::vec2(0.0f, 1.0f),
        glm::vec2(0.0f, -1.0f),
        glm::vec2(-1.0f, 0.0f),
        glm::vec2(1.0f, 0.0f)
    };

    GLfloat max = 0.0f;
    GLuint best_match = -1;

    for (GLuint i = 0; i < 4; i++) {
        GLfloat dot_product = glm::dot(glm::normalize(vec), compass[i]);
        if (dot_product > max) {
            max = dot_product;
            best_match = i;
        }
    }

    return (Direction) best_match;
}


#endif // VECTOR_DIRECTION_H

