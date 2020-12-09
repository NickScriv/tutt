#include "Shader.h"



Shader::Shader()
{
	shaderID = 0;
	uniformModel = 0;
	uniformModel = 0;
	pointLightCount = 0;
}

void Shader::CreateFromString(const char* vertexCode, const char* fragmentCode)
{
	CompileShader(vertexCode, fragmentCode);
}

void Shader::CompileShader(const char* vertexCode, const char* fragmentCode)
{
	shaderID = glCreateProgram();
	if (!shaderID)
	{
		std::cout << "Error creating shader program!" << std::endl;
		return;
	}

	AddShader(shaderID, vertexCode, GL_VERTEX_SHADER);
	AddShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

	// link and validate program
	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	// creates executables on graphics card
	glLinkProgram(shaderID);
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		std::cout << "Error linked Program: " << eLog << std::endl;
		return;
	}

	// validates the program
	glValidateProgram(shaderID);
	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		std::cout << "Error validating Program: " << eLog << std::endl;
		return;
	}

	// get uniforms in the shader
	uniformModel = glGetUniformLocation(shaderID, "model");
	uniformView= glGetUniformLocation(shaderID, "view");
	uniformProjection = glGetUniformLocation(shaderID, "projection");
	uniformDirectionalLight.uniformColor = glGetUniformLocation(shaderID, "directionalLight.base.color");
	uniformDirectionalLight.uniformAmbientIntensity = glGetUniformLocation(shaderID, "directionalLight.base.ambientIntensity");
	uniformDirectionalLight.uniformDiffuseIntensity = glGetUniformLocation(shaderID, "directionalLight.base.diffuseIntensity");
	uniformDirectionalLight.uniformDirection = glGetUniformLocation(shaderID, "directionalLight.direction");
	uniformSpecularIntensity = glGetUniformLocation(shaderID, "material.specularIntensity");
	uniformShininess = glGetUniformLocation(shaderID, "material.shininess");
	uniformEyePos = glGetUniformLocation(shaderID, "eyePosition");

	uniformPointLightCount = glGetUniformLocation(shaderID, "pointLightCount");

	for (size_t i = 0; i < MAX_POINT_LIGHTS; i++)
	{
		char locBuffer[100] = { '\0' }; // null terminator

		snprintf(locBuffer, sizeof(locBuffer), "pointLights[%d].base.color", i);
		uniformPointLight[i].uniformColor = glGetUniformLocation(shaderID, locBuffer);

		snprintf(locBuffer, sizeof(locBuffer), "pointLights[%d].base.ambientIntensity", i);
		uniformPointLight[i].uniformAmbientIntensity = glGetUniformLocation(shaderID, locBuffer);

		snprintf(locBuffer, sizeof(locBuffer), "pointLights[%d].base.diffuseIntensity", i);
		uniformPointLight[i].uniformDiffuseIntensity = glGetUniformLocation(shaderID, locBuffer);

		snprintf(locBuffer, sizeof(locBuffer), "pointLights[%d].position", i);
		uniformPointLight[i].uniformPosition = glGetUniformLocation(shaderID, locBuffer);

		snprintf(locBuffer, sizeof(locBuffer), "pointLights[%d].constant", i);
		uniformPointLight[i].uniformConstant= glGetUniformLocation(shaderID, locBuffer);

		snprintf(locBuffer, sizeof(locBuffer), "pointLights[%d].linear", i);
		uniformPointLight[i].uniformLinear = glGetUniformLocation(shaderID, locBuffer);

		snprintf(locBuffer, sizeof(locBuffer), "pointLights[%d].exponent", i);
		uniformPointLight[i].uniformExponent = glGetUniformLocation(shaderID, locBuffer);
	}
}

void Shader::AddShader(GLuint program, const char* shaderCode, GLenum shaderType)
{
	GLuint theShader = glCreateShader(shaderType);

	const GLchar* code[1];
	code[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, code, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
		std::cout << "Error compiling " << shaderType << ": " << eLog << std::endl;
		return;
	}

	glAttachShader(program, theShader);
}

void Shader::UseShader()
{
	glUseProgram(shaderID);
}

GLuint Shader::GetProjectionLocation() 
{
	return uniformProjection;
}
GLuint Shader::GetModelLocation() {
	return uniformModel;
}

GLuint Shader::GetViewLocation()
{
	return uniformView;
}

GLuint Shader::GetAmbientIntensityLocation()
{
	return uniformDirectionalLight.uniformAmbientIntensity;
}

GLuint Shader::GetAmbientColorLocation()
{
	return uniformDirectionalLight.uniformColor;
}

GLuint Shader::GetDiffuseIntensityLocation()
{
	return uniformDirectionalLight.uniformDiffuseIntensity;
}

GLuint Shader::GetDirectionLocation()
{
	return uniformDirectionalLight.uniformDirection;
}

GLuint Shader::GetSpecularIntensityLocation()
{
	return uniformSpecularIntensity;
}

GLuint Shader::GetShininessLocation()
{
	return uniformShininess;
}

GLuint Shader::GetEyePosLocation()
{
	return uniformEyePos;
}

void Shader::SetDirectionalLight(DirectionalLight * dLight)
{
	dLight->UseLight(uniformDirectionalLight.uniformAmbientIntensity, uniformDirectionalLight.uniformColor, uniformDirectionalLight.uniformDiffuseIntensity, uniformDirectionalLight.uniformDirection);
}

void Shader::SetPointLights(PointLight * pLight, unsigned int lightCount)
{
	if (lightCount > MAX_POINT_LIGHTS)
	{
		lightCount = MAX_POINT_LIGHTS;
	}

	glUniform1i(uniformPointLightCount, lightCount);

	for (size_t i = 0; i < lightCount; i++)
	{
		pLight[i].UseLight(uniformPointLight[i].uniformAmbientIntensity, uniformPointLight[i].uniformColor, uniformPointLight[i].uniformDiffuseIntensity, uniformPointLight[i].uniformPosition, uniformPointLight[i].uniformConstant, uniformPointLight[i].uniformLinear, uniformPointLight[i].uniformExponent);
	}
}

void Shader::CreateFromFiles(const char* vertexCodeLocation, const char* fragmentCodeLocation)
{
	std::string vertexString = ReadFile(vertexCodeLocation);
	std::string fragString = ReadFile(fragmentCodeLocation);

	const char* vertCode = vertexString.c_str();
	const char* fragCode = fragString.c_str();

	CompileShader(vertCode, fragCode);

}

// read shader file line by line
std::string Shader::ReadFile(const char* fileLoc) {
	std::string content;
	std::ifstream fileStream(fileLoc, std::ios::in);

	if (!fileStream.is_open())
	{
		std::cout << "Failed to read." << fileLoc << " does not exist." << std::endl;
		return "";
	}

	std::string line = "";
	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;

}

void Shader::ClearShader()
{
	if (shaderID != 0)
	{
		// delete program off the graphics card
		glDeleteProgram(shaderID);
	}
}

Shader::~Shader()
{
	ClearShader();
}
