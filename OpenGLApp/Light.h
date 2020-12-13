#pragma once

#include<glm/glm.hpp>
#include<GL/glew.h>
#include "ShadowMap.h"
#include <glm/gtc/matrix_transform.hpp>


class Light
{
public:
	Light();
	Light( GLfloat shadowWidth, GLfloat shadowHeight,
		GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntesnity, GLfloat dIntensity);
	virtual ~Light();

	ShadowMap * GetShadowMap()
	{
		return shadowMap;
	}

protected:
	glm::vec3 color;
	GLfloat ambientIntensity;
	GLfloat diffuseIntensity;
	ShadowMap * shadowMap;
	glm::mat4 lightProj;
};

