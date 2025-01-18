// standard library first
#include <iostream>
// thrird party libraries
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// my own libraries
#include "crate.h"

// Vertex data and attributes
const float Crate::vertices[] = {
    // Positions          // Texture Coords
    // Front face
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // 0: Bottom-left
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // 1: Bottom-right
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // 2: Top-right
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // 3: Top-left
    // Back face
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // 4: Bottom-left
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // 5: Bottom-right
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // 6: Top-right
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // 7: Top-left
    // Left face
    -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // 8: Bottom-right
    -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // 9: Top-right
    // Right face
     0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // 10: Bottom-left
     0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // 11: Top-left
    // Top face
    -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, // 12: Bottom-left
     0.5f,  0.5f, -0.5f,  1.0f, 0.0f, // 13: Bottom-right
    // Bottom face
     0.5f, -0.5f,  0.5f,  1.0f, 1.0f, // 14: Top-right
    -0.5f, -0.5f,  0.5f,  0.0f, 1.0f  // 15: Top-left
};


// Indices for drawing the cube using element array
const unsigned int Crate::indices[] = {
    // Front face
    0, 1, 2,
    0, 2, 3,
    // Back face
    4, 5, 6,
    4, 6, 7,
    // Left face
    4, 8, 9,
    4, 9, 7,
    // Right face
    10, 1, 2,
    10, 2, 11,
    // Top face
    12, 13, 2,
    12, 2, 3,
    // Bottom face
    4, 5, 14,
    4, 14, 15
};


Crate::Crate(const char* texturePath1, const char* texturePath2, Shader& shader)
{
    // load textures
    texture1_ = loadTexture(texturePath1, false, GL_RGB);
    texture2_ = loadTexture(texturePath2, true, GL_RGBA);

    // create vertex buffer objects, vertex array objects, element buffer objects
    glGenVertexArrays(1, &VAO_);
    glGenBuffers(1, &VBO_);
    glGenBuffers(1, &EBO_);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO_);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribure
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    shader.use(); // don't forget to activate the shader before setting uniforms!
    glUniform1i(glGetUniformLocation(shader.ID, "texture1"), 0); // set it manually
    shader.setInt("texture2", 1); // or with shader class
}


void Crate::draw(const glm::vec3& position, float angle, Shader& shader)
{
    // Use the shader program
    shader.use();

    // Bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1_);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2_);

    // Set the model matrix and other uniforms
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
    shader.setMat4("model", model);

    // Render the crate
    glBindVertexArray(VAO_);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}


Crate::~Crate()
{
    glDeleteVertexArrays(1, &VAO_);
    glDeleteBuffers(1, &VBO_);
    glDeleteBuffers(1, &EBO_);
    glDeleteTextures(1, &texture1_);
    glDeleteTextures(1, &texture2_);
}


unsigned int Crate::loadTexture(const char* path, bool flipVertically, GLenum format)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    glBindTexture(GL_TEXTURE_2D, textureID);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set the texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // load and generate the texture
    int width, height, nrChannels;
    if (flipVertically)
    {
        stbi_set_flip_vertically_on_load(true);
    }
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture: " << path << std::endl;
    }
    stbi_image_free(data);

    return textureID;
}