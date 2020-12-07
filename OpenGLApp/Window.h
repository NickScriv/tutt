#pragma once

#include<iostream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);

	int initialize();

	// passing array of keys, DANGEROUS
	bool* getsKeys()
	{
		return keys;
	}

	GLfloat getXChange();
	GLfloat getYChange();

	GLint getBufferWidth()
	{
		return bufferWidth;
	}

	GLint getBufferHeight()
	{
		return bufferHeight;
	}

	bool getShouldClose()
	{
		return glfwWindowShouldClose(mainWindow);
	}

	void swapBuffers()
	{
		glfwSwapBuffers(mainWindow);
	}
	~Window();

private:
	GLFWwindow *mainWindow;
	GLint width, height, bufferWidth, bufferHeight;
	bool keys[1024];

	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	bool mouseFirstMoved;


	// must be static because it will be passed into a call back
	static void handleKeys(GLFWwindow * window, int key, int code, int action, int mode);
	static void handleMouse(GLFWwindow * window, double xPos, double yPos);
	void createCallbacks();
};

