#include "ShadowMap.h"

ShadowMap::ShadowMap()
{
	FBO = 0;
	shadowMap = 0;
}

ShadowMap::~ShadowMap()
{
	if (FBO)
	{
		glDeleteFramebuffers(1, &FBO);
	}

	if (shadowMap)
	{
		glDeleteTextures(1, &shadowMap);
	}
}

bool ShadowMap::init(unsigned int width, unsigned int height)
{
	//std::cout << "Inintialize shadow map" << std::endl;
	shadowWidth = width;
	shadowHeight = height;

	glGenFramebuffers(1, &FBO);
	//std::cout << FBO << std::endl;
	glGenTextures(1, &shadowMap);

	glBindTexture(GL_TEXTURE_2D, shadowMap);
	// each pixel has one value

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
	
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER); // x axis
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER); // y axis
	float bColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE, GL_TEXTURE_BORDER_COLOR, bColor);

	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // far away 
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // near

	glGenerateMipmap(GL_TEXTURE_2D);
	// apply blend to texture when zooming in and out
	
	// Send image data to the gpu. 2nd arg is level of mip maps
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	// write frame buffer to texture
	//std::cout << shadowMap << std::endl;
	//std::cout << shadowMap << std::endl;
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowMap, 0);

	// do not use color attachments
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "Frame buffer error: " << status << std::endl;
		return false;
	}

	//glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return true;


}

void ShadowMap::write()
{
	//std::cout << FBO << std::endl;
	//std::cout << "Bind framebuffer to write the texture" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
}

void ShadowMap::read(GLenum textureUnit)
{
	//std::cout << "Bind shadow map to texture unit" << std::endl;
	glActiveTexture(textureUnit);
	glBindTexture(GL_TEXTURE_2D, shadowMap);
}
