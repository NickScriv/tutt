
#include "pch.h"
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include "Mesh.h"
#include "Shader.h"
#include "Window.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>  

std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

const float toRadians = 3.141592651 / 180.0f;

// Vertex shader
static const char* vShader = "Shaders/shader.vert";

// fragment shader
static const char* fShader = "Shaders/shader.frag";

Window mainWindow;

void CreateObjects()
{
	unsigned int indicies[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2,
	};
	GLfloat vertices[] = {
		-1.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(vertices, indicies, 12, 12);
	meshList.push_back(obj2);

	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indicies, 12, 12);
	meshList.push_back(obj1);
	
}


void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}



int main()
{
	mainWindow = Window();
	mainWindow.initialize();

	CreateObjects();
	CreateShaders();

	GLuint uniformProjection = 0, uniformModel = 0;

	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / (GLfloat)mainWindow.getBufferHeight(), 0.1f, 100.0f);

	// Loop until window closes
	while (!mainWindow.getShouldClose()) // which window should close
	{
		// Get and handle user input events...

		// check if any events occured
		glfwPollEvents();

		// clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		// clear all the colors only
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();

		glm::mat4 model(1.0f);
		
		
		// position of rotation is relative to the position of the object
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
		
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));

		// sets the value of the uniform, uniformModel holds the id of uniform
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

		meshList[0]->RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, -2.5f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->RenderMesh();


		Shader::ResetShader();
		// swap buffers after drawing
		mainWindow.swapBuffers();

	}

	return 0;
}