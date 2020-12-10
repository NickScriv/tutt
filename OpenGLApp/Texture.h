#pragma once
#include <GL/glew.h>
#include <iostream>
#include "stb_image.h"

class Texture
{
public:

	Texture();
	Texture(const char* file);
	~Texture();


	bool LoadTexture();
	// with alpha channel
	bool LoadTextureA();
	void UseTexture();
	void ClearTexture();

private:
	GLuint textureID;
	int width, height, bitDepth;

	const char* fileLoc;


};

