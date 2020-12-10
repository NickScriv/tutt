#pragma once
#include "PointLight.h"
class SpotLight :
	public PointLight
{
public:

	SpotLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntesnity, GLfloat dIntensity, GLfloat xPos, GLfloat yPos, GLfloat zPos, GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat con, GLfloat lin, GLfloat exp, GLfloat edge);
	~SpotLight();
	SpotLight();
	void UseLight(GLuint ambientIntensityLoc, GLuint ambientColorLoc, GLuint diffuseIntesnityLoc, GLuint positionLocation, GLuint directionLocation, GLuint conLocation, GLuint linLocation, GLuint expLocation, GLuint edgeLocation);

	void SetFlash(glm::vec3 pos, glm::vec3 dir);
private:
	glm::vec3 direction;

	// edge of the light, angle from normal
	GLfloat edge, procEdge;
};

