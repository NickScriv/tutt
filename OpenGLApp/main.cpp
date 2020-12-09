
#define STB_IMAGE_IMPLEMENTATION


#include "pch.h"
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include "Mesh.h"
#include "Shader.h"
#include "Window.h"
#include "Camera.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>  
#include "Texture.h"
#include "Material.h"
#include "DirectionalLight.h"
#include "CommomValues.h"
#include "PointLight.h"

// usually defined in mesh
Texture brick;
Texture dirt;
Texture plain;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
Material shinyMaterial;
Material dullMaterial;
PointLight pointLights[MAX_POINT_LIGHTS];

const float toRadians = 3.141592651 / 180.0f;

// Vertex shader
static const char* vShader = "Shaders/shader.vert";

// fragment shader
static const char* fShader = "Shaders/shader.frag";

Window mainWindow;
Camera camera;

void calcAvgNormals(unsigned int *indicies, unsigned int indexCount, GLfloat * verticies, unsigned int vertexCount, unsigned int vLength, unsigned int normalOffset)
{
	// for every triangle
	for (size_t i = 0; i < indexCount; i += 3)
	{
		unsigned int in0 = indicies[i] * vLength;
		unsigned int in1 = indicies[i + 1] * vLength;
		unsigned int in2 = indicies[i + 2] * vLength;
		glm::vec3 v1(verticies[in1] - verticies[in0], verticies[in1 + 1] - verticies[in0 + 1], verticies[in1 + 2] - verticies[in0 + 2]);
		glm::vec3 v2(verticies[in2] - verticies[in0], verticies[in2 + 1] - verticies[in0 + 1], verticies[in2 + 2] - verticies[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;

		verticies[in0] += normal.x; verticies[in0 + 1] += normal.y; verticies[in0 + 2] += normal.z;
		verticies[in1] += normal.x; verticies[in1 + 1] += normal.y; verticies[in1 + 2] += normal.z;
		verticies[in2] += normal.x; verticies[in2 + 1] += normal.y; verticies[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < vertexCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(verticies[nOffset], verticies[nOffset + 1], verticies[nOffset + 2]);
		vec = glm::normalize(vec);
		verticies[nOffset] = vec.x;
		verticies[nOffset + 1] = vec.y;
		verticies[nOffset + 2] = vec.z;
	}


}

void CreateObjects()
{
	unsigned int indicies[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2,
	};
	GLfloat vertices[] = {
		// x     y     z       u       v         nx    ny    nz
		-1.0f, -1.0f, -0.6f,   0.0f,   0.0f,     0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 1.0f,    0.5f,   0.0f,     0.0f, 0.0f, 0.0f,
		1.0f, -1.0f,- 0.6f,   1.0f,   0.0f,      0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,    0.5f,   1.0f,      0.0f, 0.0f, 0.0f
	};

	GLfloat floorVerticies[] = {
		-10.0, 0.0f, -10.0f,   0.0f, 0.0f,      0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,   10.0f, 0.0f,     0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,   0.0f, 10.0f,     0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,     10.0f, 10.0f,   0.0f, -1.0f, 0.0f,
	};

	unsigned int floorIndicies[] = {
		0, 2, 1,
		1, 2, 3,
	};

	calcAvgNormals(indicies, 12, vertices, 32, 8, 5);

	
	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(vertices, indicies, 32, 12);
	meshList.push_back(obj2);

	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indicies, 32, 12);
	meshList.push_back(obj1);

	Mesh *obj3 = new Mesh();
	obj3->CreateMesh(floorVerticies, floorIndicies, 32, 6);
	meshList.push_back(obj3);

	
}


void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}



int main()
{
	mainWindow = Window(1366, 768);
	mainWindow.initialize();

	CreateObjects();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.5f);

	brick = Texture("Textures/brick.png");
	brick.LoadTexture();
	dirt = Texture("Textures/dirt.png");
	dirt.LoadTexture();
	plain = Texture("Textures/plain.png");
	plain.LoadTexture();

	shinyMaterial = Material(1.0f, 32.0f);
	dullMaterial = Material(0.3f, 4.0f);
	DirectionalLight mainLight(0.0f, 0.0f, 0.0f, 0.2f, 1.0f,
		              2.0f, -1.0f, -2.0f);

	unsigned int pointLightCount = 0;

	pointLights[0] = PointLight(0.0f, 0.0f, 1.0f, 0.1f, 0.4f, 4.0f, 0.0f, 0.0f, 0.3f, 0.2f, 0.1f);
	pointLightCount++;

	pointLights[1] = PointLight(0.0f, 1.0f, 0.0f, 0.1f, 1.0f, -4.0f, 2.0f, 0.0f, 0.3f, 0.1f, 0.1f);
	pointLightCount++;

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformShininess = 0, uniformSpecularIntensity = 0, uniformEyePos = 0;                                                                                    

	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / (GLfloat)mainWindow.getBufferHeight(), 0.1f, 100.0f);

	// Loop until window closes
	while (!mainWindow.getShouldClose()) // which window should close
	{

		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		lastTime = now;
		// Get and handle user input events...

		// check if any events occured
		glfwPollEvents();

		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseContol(mainWindow.getXChange(), mainWindow.getYChange());

		// clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		// clear all the colors only
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePos = shaderList[0].GetEyePosLocation();
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

	

		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLights(pointLights, pointLightCount);
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePos, camera.getCamPos().x, camera.getCamPos().y, camera.getCamPos().z);
		glm::mat4 model(1.0f);
		
		
		// position of rotation is relative to the position of the object
		model = glm::translate(model, glm::vec3(0.0f, 2.0f, -2.5f));
		
		//model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));

		// sets the value of the uniform, uniformModel holds the id of uniform
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		
		brick.UseTexture();
		shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[0]->RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
		//model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dirt.UseTexture();
		dullMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[1]->RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		plain.UseTexture();
		dullMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();


		Shader::ResetShader();
		// swap buffers after drawing
		mainWindow.swapBuffers();

	}

	return 0;
}