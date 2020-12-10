#include "SpotLight.h"

SpotLight::SpotLight() :PointLight()
{
	direction = glm::vec3(0.0f, -1.0f, 0.0f);
	edge = 0.0f;
	procEdge = cosf(glm::radians(edge));
}

void SpotLight::UseLight(GLuint ambientIntensityLoc, GLuint ambientColorLoc, GLuint diffuseIntesnityLoc, GLuint positionLocation, GLuint directionLocation, GLuint conLocation, GLuint linLocation, GLuint expLocation, GLuint edgeLocation)
{
	glUniform3f(ambientColorLoc, color.x, color.y, color.z);
	glUniform1f(ambientIntensityLoc, ambientIntensity);

	glUniform3f(positionLocation, position.x, position.y, position.z);
	glUniform1f(conLocation, constant);
	glUniform1f(expLocation, exponent);
	glUniform1f(linLocation, linear);
	glUniform1f(diffuseIntesnityLoc, diffuseIntensity);

	glUniform3f(directionLocation, direction.x, direction.y, direction.z);
	glUniform1f(edgeLocation, procEdge);

}

void SpotLight::SetFlash(glm::vec3 pos, glm::vec3 dir)
{
	position = pos;
	direction = dir;
}


SpotLight::SpotLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntesnity, GLfloat dIntensity, GLfloat xPos, GLfloat yPos, GLfloat zPos, GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat con, GLfloat lin, GLfloat exp, GLfloat edge) : PointLight(red, green, blue, aIntesnity, dIntensity, xPos, yPos, zPos, con, lin, exp)
{
	direction = glm::normalize(glm::vec3(xDir, yDir, zDir));

	edge = edge;
	procEdge = cosf(glm::radians(edge));
}

SpotLight::~SpotLight()
{

}


