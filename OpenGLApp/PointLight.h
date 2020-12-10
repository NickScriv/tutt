#pragma once
#include "Light.h"
class PointLight :
	public Light
{
public:
	PointLight();
	PointLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntesnity, GLfloat dIntensity, GLfloat xPos, GLfloat yPos, GLfloat zPos, GLfloat con, GLfloat lin, GLfloat exp);
	~PointLight();
	void UseLight(GLfloat ambientIntensityLoc, GLfloat ambientColorLoc, GLfloat diffuseIntesnityLoc, GLfloat positionLocation, GLfloat conLocation, GLfloat linLocation, GLfloat expLocation);

protected:
	glm::vec3 position;

	GLfloat constant, linear, exponent;
};

