#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW\glfw3.h>
class Camera
{
public:
	Camera(glm::vec3 pos, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat moveSpeed, GLfloat turnSpeedStart);
	Camera();
	~Camera();

	glm::vec3 getCamPos();
	glm::mat4 calculateViewMatrix();

	void keyControl(bool *keys, GLfloat deltaTime);
	void mouseContol(GLfloat xChangeStart, GLfloat yChangeStart);

private:
	glm::vec3 position;
	glm::vec3 forward;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	GLfloat yaw;
	GLfloat pitch;

	GLfloat movementSpeed;
	GLfloat turnSpeed;

	void update();



};

