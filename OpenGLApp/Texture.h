#pragma once
#include <GL/glew.h>
#include <iostream>
#include "stb_image.h"

class Texture
{
public:

	Texture();
	Texture(char* file);
	~Texture();


	void LoadTexture();
	void UseTexture();
	void ClearTexture();

private:
	GLuint textureID;
	int width, height, bitDepth;

	char* fileLoc;


};

