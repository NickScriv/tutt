#include "Shader.h"



Shader::Shader()
{
	shaderID = 0;
	uniformModel = 0;
	uniformModel = 0;
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
	uniformAmbientColor = glGetUniformLocation(shaderID, "directionalLight.color");
	uniformAmbientIntensity = glGetUniformLocation(shaderID, "directionalLight.ambientIntensity");
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
	return uniformAmbientIntensity;
}

GLuint Shader::GetAmbientColorLocation()
{
	return uniformAmbientColor;
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
