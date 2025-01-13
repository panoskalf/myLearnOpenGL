#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>

class Camera
{
public:
    enum Camera_Movement
    {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

    Camera(glm::vec3 position);
    glm::mat4 getViewMatrix();
    float getZoom();
    void processKeyboard(Camera_Movement direction, float deltaTime);
    void processMouseMovement(float xoffset, float yoffset);
    void processMouseScroll(float yoffset);

private:
    glm::vec3 position_;
    glm::vec3 front_;
    glm::vec3 up_;
    float fov_;
    float yaw_;
    float pitch_;
};

#endif // CAMERA_H