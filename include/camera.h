#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>

enum Camera_Movement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};


class Camera
{
public:

    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f));
    glm::mat4 getViewMatrix();
    float getZoom();
    glm::vec3 getPosition() { return position_; }
    glm::vec3 getFront() { return front_;}
    void processKeyboard(Camera_Movement direction, float deltaTime);
    void processMouseMovement(float xoffset, float yoffset);
    void processMouseScroll(float yoffset);

private:
    void updateCameraVectors(void);
    glm::mat4 myLookAt(const glm::vec3& position, const glm::vec3& target, const glm::vec3& worldUp);

    glm::vec3 position_;
    glm::vec3 front_;
    glm::vec3 up_;
    glm::vec3 right_;
    glm::vec3 worldUp_;
    float fov_;
    float yaw_;
    float pitch_;
};

#endif // CAMERA_H