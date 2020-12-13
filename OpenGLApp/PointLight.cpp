#include "PointLight.h"

PointLight::PointLight() : Light()
{
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	constant = 1.0f;
	linear = 0.0f;
	exponent = 0.0f;
}

PointLight::PointLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntesnity, GLfloat dIntensity, GLfloat xPos, GLfloat yPos, GLfloat zPos, GLfloat con, GLfloat lin, GLfloat exp) : Light(1024, 1024,  red, green, blue, aIntesnity, dIntensity)
{
	position = glm::vec3(xPos, yPos, zPos);
	constant = con;
	exponent = exp;
	linear = lin;
}

PointLight::~PointLight()
{
}

void PointLight::UseLight(GLfloat ambientIntensityLoc, GLfloat ambientColorLoc, GLfloat diffuseIntesnityLoc, GLfloat positionLocation, GLfloat conLocation, GLfloat linLocation, GLfloat expLocation)
{
	glUniform3f(ambientColorLoc, color.x, color.y, color.z);
	glUniform1f(ambientIntensityLoc, ambientIntensity);

	glUniform3f(positionLocation, position.x, position.y, position.z);
	glUniform1f(conLocation, constant);
	glUniform1f(expLocation, exponent);
	glUniform1f(linLocation, linear);
	glUniform1f(diffuseIntesnityLoc, diffuseIntensity);
}
