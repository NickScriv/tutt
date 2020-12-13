#include "Light.h"
#include <iostream>

Light::Light()
{
	color = glm::vec3(1.0f, 1.0f, 1.0f);
	ambientIntensity = 1.0f;
	diffuseIntensity = 0.0f;
}

Light::Light(GLfloat shadowWidth, GLfloat shadowHeight, GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntesnity, GLfloat dIntensity)
{
	shadowMap = new ShadowMap();
	shadowMap->init(shadowWidth, shadowHeight);
	

	color = glm::vec3(red, green, blue);
	ambientIntensity = aIntesnity;
	diffuseIntensity = dIntensity;
}
Light::~Light()
{

}


