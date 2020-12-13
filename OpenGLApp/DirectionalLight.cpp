#include "DirectionalLight.h"


DirectionalLight::DirectionalLight() : Light()
{
	
	direction = glm::vec3(0.0f, -1.0f, 0.0f);
	lightProj = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.1f, 20.0f);
}

DirectionalLight::DirectionalLight(GLfloat shadowWidth, GLfloat shadowHeight, GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntesnity, GLfloat dIntensity, GLfloat xDir, GLfloat yDir, GLfloat zDir) : Light(shadowWidth, shadowHeight, red, green, blue, aIntesnity, dIntensity) // super contructor
{
	direction = glm::vec3(xDir, yDir, zDir);
	lightProj = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, 0.1f, 100.0f);
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

glm::mat4 DirectionalLight::calculateLightTransform()
{
	// negative direction for the postion
	glm::mat4 res =  lightProj * glm::lookAt(-direction, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	std::cout << res[0].x << " " <<  res[0].y << " " << res[0].z << " " << res[0].w << " " << std::endl;
	std::cout << res[1].x << " " << res[1].y << " " << res[1].z << " " << res[1].w << " " << std::endl;
	std::cout << res[2].x << " " << res[2].y << " " << res[2].z << " " << res[2].w << " " << std::endl;
	std::cout << res[3].x << " " << res[3].y << " " << res[3].z << " " << res[3].w << " " << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	return res;
}

