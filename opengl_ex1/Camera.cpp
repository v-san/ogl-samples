#include "Camera.h"
#include <glm/glm.hpp>

Camera::Camera(glm::vec3 a_pos, glm::vec3 a_up, glm::vec3 a_front, GLfloat a_yaw, GLfloat a_pitch,
  GLfloat a_moveSpeed, GLfloat a_mouseSensitivity, GLfloat a_zoom) : pos(a_pos), front(a_front), up(a_up),
  yaw(a_yaw), pitch(a_pitch), moveSpeed(a_moveSpeed), mouseSensitivity(a_mouseSensitivity), zoom(a_zoom)
{
  right = glm::normalize(glm::cross(a_up, a_front));
  worldUp = up;
}



glm::mat4 Camera::GetViewMatrix() const
{
  return glm::lookAt(pos, pos + front, up);
}

void Camera::ProcessKeyboard(Movement_Direction dir, GLfloat deltaTime)
{
  GLfloat velocity = moveSpeed * deltaTime;
  if (dir == FORWARD)
    pos += front * velocity;
  if (dir == BACKWARD)
    pos -= front * velocity;
  if (dir == LEFT)
    pos -= right * velocity;
  if (dir == RIGHT)
    pos += right * velocity;
}

void Camera::ProcessMouseMove(GLfloat deltaX, GLfloat deltaY, GLboolean limitPitch)
{
  deltaX *= mouseSensitivity;
  deltaY *= mouseSensitivity;

  yaw += deltaX;
  pitch += deltaY;

  if (limitPitch)
  {
    if (pitch > 89.0f)
      pitch = 89.0f;
    if (pitch < -89.0f)
      pitch = -89.0f;
  }

  updateCameraVectors();
}

void Camera::ProcessMouseScroll(GLfloat deltaY)
{
  if (zoom >= 1.0f && zoom <= 45.0f)
    zoom -= deltaY;
  if (zoom <= 1.0f)
    zoom = 1.0f;
  if (zoom >= 45.0f)
    zoom = 45.0f;
}



void Camera::updateCameraVectors()
{
  glm::vec3 tmpFront;

  tmpFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  tmpFront.y = sin(glm::radians(pitch));
  tmpFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

  front = glm::normalize(tmpFront);

  right = glm::normalize(glm::cross(front, worldUp));
  up = glm::normalize(glm::cross(right, front));
}