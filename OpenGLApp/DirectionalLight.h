#pragma once
#include "Light.h"
class DirectionalLight : public Light
{
public:
	DirectionalLight();
	DirectionalLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntesnity, GLfloat dIntensity, GLfloat xDir, GLfloat yDir, GLfloat zDir);
	~DirectionalLight();

	void UseLight(GLfloat ambientIntensityLoc, GLfloat ambientColorLoc, GLfloat diffuseIntesnityLoc, GLfloat directionLocation);

private:
	glm::vec3 direction;
};

