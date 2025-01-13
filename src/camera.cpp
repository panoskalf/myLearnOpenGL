#include <glm/gtc/matrix_transform.hpp>
#include "camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up) :
position_(position),
front_(glm::vec3(0.0f, 0.0f, -1.0f)),
up_(up),
worldUp_(up),
fov_(45.0f),
// yaw 0.0 results in poining to x-axis (right)
// but we want to point it to -z axis (front)
// so rotate clockwise by 90 degrees
yaw_(-90.0f),
pitch_(0.0f)
{
    // optional: right would be calculated when orientation is changed.
    // cross product results in a vector perpendicular to the two vectors
    right_ = glm::normalize(glm::cross(front_, worldUp_));
}

glm::mat4 Camera::getViewMatrix()
{
    // equivalent to: glm::lookAt(position_, position_ + front_, up_);
    return myLookAt(position_, position_ + front_, up_);
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
        position_ -= right_ * velocity;
    if (direction == RIGHT)
        position_ += right_ * velocity;
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

    // with pitch and yaw we can calculate new front vector
    // using Euler angles.
    updateCameraVectors();
}


void Camera::updateCameraVectors(void)
{
    glm::vec3 front;
    front.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    front.y = sin(glm::radians(pitch_));
    front.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    front_ = glm::normalize(front);
    // also re-calculate the right and up vector
    // normalize the vectors, because their length gets closer to 0
    // the more you look up or down which results in slower movement.
    right_ = glm::normalize(glm::cross(front_, worldUp_));
    up_    = glm::normalize(glm::cross(right_, front_));
}


void Camera::processMouseScroll(float yoffset)
{
    fov_ -= yoffset;
    if (fov_ < 1.0f)
        fov_ = 1.0f;
    if (fov_ > 45.0f)
        fov_ = 45.0f;
}


glm::mat4 Camera::myLookAt(const glm::vec3& position, const glm::vec3& target, const glm::vec3& worldUp)
{
    glm::vec3 zaxis = glm::normalize(position - target);
    glm::vec3 xaxis = glm::normalize(glm::cross(worldUp, zaxis));
    glm::vec3 yaxis = glm::cross(zaxis, xaxis);

    glm::mat4 translation = glm::mat4(1.0f);
    translation[3][0] = -position.x;
    translation[3][1] = -position.y;
    translation[3][2] = -position.z;
    glm::mat4 rotation = glm::mat4(1.0f);
    rotation[0][0] = xaxis.x;
    rotation[1][0] = xaxis.y;
    rotation[2][0] = xaxis.z;
    rotation[0][1] = yaxis.x;
    rotation[1][1] = yaxis.y;
    rotation[2][1] = yaxis.z;
    rotation[0][2] = zaxis.x;
    rotation[1][2] = zaxis.y;
    rotation[2][2] = zaxis.z;

    return rotation * translation;
}