#pragma once

#include<glm/glm.hpp>
#include<GL/glew.h>
class Light
{
public:
	Light();
	Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntesnity );
	~Light();

	void UseLight(GLfloat ambientIntensityLoc, GLfloat ambientColorLoc);

private:
	glm::vec3 color;
	GLfloat ambientIntensity;
};

