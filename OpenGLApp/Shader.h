#pragma once

#include<iostream>
#include<string>
#include<fstream>
#include<GL\glew.h>
#include "DirectionalLight.h"
#include "PointLight.h"
#include "CommomValues.h"
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
	GLuint GetAmbientIntensityLocation();
	GLuint GetAmbientColorLocation();
	GLuint GetDiffuseIntensityLocation();
	GLuint GetDirectionLocation();
	GLuint GetSpecularIntensityLocation();
	GLuint GetShininessLocation();
	GLuint GetEyePosLocation();

	void SetDirectionalLight(DirectionalLight * dLight);
	void SetPointLights(PointLight *pLight, unsigned int lightCount);


	// unassigns current shader
	static void ResetShader()
	{
		
		glUseProgram(0);
	}

	void UseShader();
	void ClearShader();
	~Shader();

private:
	int pointLightCount;
	GLuint shaderID, uniformProjection, uniformModel, uniformView;
	GLuint uniformSpecularIntensity, uniformShininess, uniformEyePos;
	GLuint uniformPointLightCount;

	struct {
		GLuint uniformColor;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;
		GLuint uniformDirection;
	}uniformDirectionalLight;

	// can have multiple point lights
	struct {
		GLuint uniformColor;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;
		GLuint uniformPosition;
		GLuint uniformConstant;
		GLuint uniformLinear;
		GLuint uniformExponent;
	}uniformPointLight[MAX_POINT_LIGHTS];


	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void AddShader(GLuint program, const char* shaderCode, GLenum shaderType);
};

