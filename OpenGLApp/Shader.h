#pragma once

#include<iostream>
#include<string>
#include<fstream>
#include<GL\glew.h>
class Shader
{
public:
	Shader();
	void CreateFromString(const char* vertexCode, const char* fragmentCode);
	void CreateFromFiles(const char* vertexCodeLocation, const char* fragmentCodeLocation);

	std::string ReadFile(const char* fileLoc);

	GLuint GetProjectionLocation();
	GLuint GetModelLocation();
	GLuint GetViewLocation();

	// unassigns current shader
	static void ResetShader()
	{
		
		glUseProgram(0);
	}

	void UseShader();
	void ClearShader();
	~Shader();

private:
	GLuint shaderID, uniformProjection, uniformModel, uniformView;

	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void AddShader(GLuint program, const char* shaderCode, GLenum shaderType);
};

