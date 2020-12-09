#include "Camera.h"

Camera::Camera(glm::vec3 pos, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat moveSpeed, GLfloat turnSpeedStart)
{
	position = pos;
	worldUp = startUp;
	yaw = startYaw;
	pitch = startPitch;
	forward = glm::vec3(0.0f, 1.0f, 0.0f);

	movementSpeed = moveSpeed;
	turnSpeed = turnSpeedStart;

	update();
}

Camera::Camera()
{

}

void Camera::keyControl(bool * keys, GLfloat deltaTime)
{
	GLfloat velocity = movementSpeed * deltaTime;
	if (keys[GLFW_KEY_W])
	{
		position += forward * velocity;
	}
	if (keys[GLFW_KEY_S])
	{
		position -= forward * velocity;
	}
	if (keys[GLFW_KEY_A])
	{
		position -= right * velocity;
	}
	if (keys[GLFW_KEY_D])
	{
		position += right * velocity;
	}
}

void Camera::mouseContol(GLfloat xChangeStart, GLfloat yChangeStart)
{
	xChangeStart *= turnSpeed;
	yChangeStart *= turnSpeed;

	yaw += xChangeStart;
	pitch += yChangeStart;

	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}

	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	update();
}

glm::vec3 Camera::getCamPos()
{
	return position;
}

glm::mat4 Camera::calculateViewMatrix()
{
	return glm::lookAt(position, position + forward, up);
}

void Camera::update()
{
	forward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	forward.y = sin(glm::radians(pitch));
	forward.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	forward = glm::normalize(forward);

	right = glm::normalize(glm::cross(forward, worldUp));
	up = glm::normalize(glm::cross(right, forward));
}

Camera::~Camera()
{

}