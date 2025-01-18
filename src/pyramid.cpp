// standard library first
#include <iostream>
// thrird party libraries
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// my own libraries
#include "pyramid.h"

// Vertex data and attributes
const float Pyramid::vertices[] = {
    // Bottom face
    // Positions          // Colors
    -0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  // 0: Left-front (Red)
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  // 1: Right-front (Red)
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  // 2: Right-back (Red)
    -0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  // 0: Left-front (Red)
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  // 2: Right-back (Red)
    -0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  // 3: Left-back (Red)
    // Front face
     0.0f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  // 4: Top-peak (Green)
    -0.5f, -0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  // 0: Left-front (Green)
     0.5f, -0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  // 1: Right-front (Green)
    // Back face
     0.0f,  0.5f,  0.0f,  0.0f,  0.0f,  1.0f,  // 4: Top-peak (Blue)
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  // 2: Right-back (Blue)
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  // 3: Left-back (Blue)
    // Left face
     0.0f,  0.5f,  0.0f,  1.0f,  1.0f,  0.0f,  // 4: Top-peak (Yellow)
    -0.5f, -0.5f, -0.5f,  1.0f,  1.0f,  0.0f,  // 3: Left-back (Yellow)
    -0.5f, -0.5f,  0.5f,  1.0f,  1.0f,  0.0f,  // 0: Left-front (Yellow)
    // Right face
     0.0f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  // 4: Top-peak (Magenta)
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  1.0f,  // 1: Right-front (Magenta)
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  1.0f   // 2: Right-back (Magenta)
};


Pyramid::Pyramid(void)
{
    // create vertex buffer objects, vertex array objects, element buffer objects
    glGenVertexArrays(1, &VAO_);
    glGenBuffers(1, &VBO_);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO_);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}


void Pyramid::draw(const glm::vec3& position, float angle, Shader& shader)
{
    // Use the shader program
    shader.use();

    // Set the model matrix and other uniforms
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 0.4f, 0.0f));
    shader.setMat4("model", model);

    // Render the crate
    glBindVertexArray(VAO_);
    glDrawArrays(GL_TRIANGLES, 0, 18);
    glBindVertexArray(0);
}


Pyramid::~Pyramid()
{
    glDeleteVertexArrays(1, &VAO_);
    glDeleteBuffers(1, &VBO_);
}

