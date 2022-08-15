#pragma once

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#pragma once
class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight, bool windowResizable);

	int initialize();

	GLFWwindow* getWindow() { return mainWindow; }

	GLint getWidth() { return width; }
	GLint getHeight() { return height; }

	GLint getBufferWidth() { return bufferWidth; }
	GLint getBufferHeight() { return bufferHeight; }

	bool getShouldClose() { return glfwWindowShouldClose(mainWindow); }

	bool* getKeys() { return keys; }

	GLfloat getXChange();
	GLfloat getYChange();

	void swapBuffers() { glfwSwapBuffers(mainWindow); }

	~Window();
private:
	GLFWwindow* mainWindow;

	GLint width, height;

	bool resizable;

	GLint bufferWidth, bufferHeight;

	// mouse variables
	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	bool mouseFirstMove = true;

	// keyboard variables
	bool keys[1024];

	// window callbacks
	void createCallbacks();

	// handling keyboard keys
	static void handleKeys(GLFWwindow* _window, int _key, int _code, int _action, int _mode);

	// handling mouse movement
	static void handleMouse(GLFWwindow* _window, double xPos, double yPos);
};