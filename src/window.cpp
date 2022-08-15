#include "window.h"

Window::Window()
{
	width = 800;
	height = 600;

	resizable = false;

	bufferWidth = 0, bufferHeight = 0;

	mainWindow = 0;

	for(size_t i = 0; i < 1024; i++){
		keys[i] = 0;
	}
}

Window::Window(GLint windowWidth, GLint windowHeight, bool windowResizable)
{
	width = windowWidth;
	height = windowHeight;

	resizable = windowResizable;

	bufferWidth = 0, bufferHeight = 0;

	mainWindow = 0;

	for(size_t i = 0; i < 1024; i++){
		keys[i] = 0;
	}
}

int Window::initialize()
{
	if (!glfwInit())
	{
		std::cerr << "GLFW library load failed...\n";
		glfwTerminate();
		return 1;
	}

	// Setup GLFW Window properties
	// OpenGL Version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// OpenGL profile without backwards compatibility
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// OpenGL profile allow forward compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// OpenGL profile window resizability
	if (resizable){
		glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	}
	else{
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	}

	// create the window
	mainWindow = glfwCreateWindow(width, height, "GPaint", NULL, NULL);
	if (!mainWindow)
	{
		std::cerr << "GLFW window creation failed...\n";
		glfwTerminate();
		return 1;
	}

	// OpenGL viewport dimensions
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// set context for GLEW to use
	glfwMakeContextCurrent(mainWindow);

	// allow the use of modern OpenGL extension
	glewExperimental = GL_TRUE;

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		std::cerr << "GLEW initialization failed...\n";
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	// Setup viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);

	glfwSetWindowUserPointer(mainWindow, this);

	return 0;
}

Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}