#ifndef CRATE_H
#define CRATE_H

#include <glm/glm.hpp>
#include "shader.h"

class Crate
{
public:
    Crate(const char* texturePath1, const char* texturePath2, Shader& shader);

    ~Crate();

    void draw(const glm::vec3& position, float angle, Shader& shader);

private:

    unsigned int loadTexture(const char* path, bool flipVertically, GLenum format);

    static const float vertices[80];

    static const unsigned int indices[36];

    // texture IDs
    unsigned int texture1_, texture2_;

    // vertex buffer objects, vertex array objects, element buffer objects
    unsigned int VAO_, VBO_, EBO_;
};

#endif // CRATE_H