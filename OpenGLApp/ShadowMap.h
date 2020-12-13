#pragma once
#include <iostream>
#include <GL/glew.h>
class ShadowMap
{
public:
	ShadowMap();
	~ShadowMap();

	virtual bool init(unsigned int width, unsigned int height);


	// write to shadow map
	virtual void write();

	virtual void read(GLenum  textureUnit);

	GLuint GetShadowWidth() {
		
		return shadowWidth;
	}

	GLuint GetShadowHeight() {
		
		return shadowHeight;
	}

private:
	GLuint FBO, shadowMap;
	GLuint shadowWidth, shadowHeight;
};

