#include "DirectionalLight.h"


DirectionalLight::DirectionalLight() : Light()
{
	direction = glm::vec3(0.0f, -1.0f, 0.0f);
}

DirectionalLight::DirectionalLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntesnity, GLfloat dIntensity, GLfloat xDir, GLfloat yDir, GLfloat zDir) : Light(red, green, blue, aIntesnity, dIntensity) // super contructor
{
	direction = glm::vec3(xDir, yDir, zDir);
}
DirectionalLight::~DirectionalLight()
{

}

void DirectionalLight::UseLight(GLfloat ambientIntensityLoc, GLfloat ambientColorLoc, GLfloat diffuseIntesnityLoc, GLfloat directionLocation)
{
	// bind both uniforms to both IDs
	glUniform3f(ambientColorLoc, color.x, color.y, color.z);
	glUniform1f(ambientIntensityLoc, ambientIntensity);

	glUniform3f(directionLocation, direction.x, direction.y, direction.z);
	glUniform1f(diffuseIntesnityLoc, diffuseIntensity);
}

