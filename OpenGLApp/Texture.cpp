#include "Texture.h"

Texture::Texture()
{
	textureID = 0;
	width = 0;
	height = 0;
	bitDepth = 0;
	fileLoc = nullptr;

}

Texture::Texture(const char* file)
{
	textureID = 0;
	width = 0;
	height = 0;
	bitDepth = 0;
	fileLoc = file;
}

Texture::~Texture()
{
	ClearTexture();
}


bool Texture::LoadTextureA()
{
	// array of bytes to store image data
	unsigned char *texData = stbi_load(fileLoc, &width, &height, &bitDepth, 0);
	if (!texData)
	{
		std::cout << "Failed to find " << fileLoc << std::endl;
		return false;
	}

	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);
	// when texels go beyond the range of 0 and 1
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // x axis
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // y axis
	// apply blend to texture when zooming in and out
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // far away 
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // near
	// Send image data to the gpu. 2nd arg is level of mip maps
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(texData);
	return true;
}



bool Texture::LoadTexture()
{
	// array of bytes to store image data
	unsigned char *texData = stbi_load(fileLoc, &width, &height, &bitDepth, 0);
	if (!texData)
	{
		std::cout << "Failed to find " << fileLoc << std::endl;
		return false;
	}

	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);
	// when texels go beyond the range of 0 and 1
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // x axis
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // y axis
	// apply blend to texture when zooming in and out
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // far away 
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // near
	// Send image data to the gpu. 2nd arg is level of mip maps
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(texData);
	return true;
}


void Texture::UseTexture()
{
	// GL_TEXTURE0 is a texture unit, allows use of multiple textures in shaders
	glActiveTexture(GL_TEXTURE0);
	// bind texture to texture unit
	glBindTexture(GL_TEXTURE_2D, textureID);


}
void Texture::ClearTexture()
{
	// delete texture off of GPU memory
	glDeleteTextures(1, &textureID);
	textureID = 0;
	width = 0;
	height = 0;
	bitDepth = 0;
	fileLoc = nullptr;
}
