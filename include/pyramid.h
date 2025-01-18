#ifndef PYRAMID_H
#define PYRAMID_H

#include <glm/glm.hpp>
#include "shader.h"

class Pyramid
{
public:
    Pyramid(void);

    ~Pyramid();

    void draw(const glm::vec3& position, float angle, Shader& shader);

private:
    static const float vertices[108];

    // vertex buffer objects, vertex array objects
    unsigned int VAO_, VBO_;
};

#endif // PYRAMID_H