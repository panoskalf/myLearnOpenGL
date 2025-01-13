#include <glm/gtc/matrix_transform.hpp>
#include "camera.h"

Camera::Camera(glm::vec3 position) :
position_(position),
front_(glm::vec3(0.0f, 0.0f, -1.0f)),
up_(glm::vec3(0.0f, 1.0f, 0.0f)),
fov_(45.0f),
// yaw 0.0 results in poining to x-axis (right)
// but we want to point it to -z axis (front)
// so rotate clockwise by 90 degrees
yaw_(-90.0f),
pitch_(0.0f)
{

}

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(position_, position_ + front_, up_);
}

float Camera::getZoom()
{
    return fov_;
}

void Camera::processKeyboard(Camera_Movement direction, float deltaTime)
{
    float velocity = 2.5f * deltaTime;
    if (direction == FORWARD)
        position_ += front_ * velocity;
    if (direction == BACKWARD)
        position_ -= front_ * velocity;
    if (direction == LEFT)
        position_ -= glm::normalize(glm::cross(front_, up_)) * velocity;
    if (direction == RIGHT)
        position_ += glm::normalize(glm::cross(front_, up_)) * velocity;
}


void Camera::processMouseMovement(float xoffset, float yoffset)
{
    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw_   += xoffset;
    pitch_ += yoffset;

    if(pitch_ > 89.0f)
        pitch_ = 89.0f;
    if(pitch_ < -89.0f)
        pitch_ = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    direction.y = sin(glm::radians(pitch_));
    direction.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    front_ = glm::normalize(direction);
}


void Camera::processMouseScroll(float yoffset)
{
    fov_ -= yoffset;
    if (fov_ < 1.0f)
        fov_ = 1.0f;
    if (fov_ > 45.0f)
        fov_ = 45.0f;
}