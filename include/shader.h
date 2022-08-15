#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

class Shader
{
public:
	Shader();
	// creating a shader using vertex and fragment shader names (they should be stored in src/shaders directory!)
	void CreateProgram(std::string vShader, std::string fShader);

	// using shader program
	void UseShader() { glUseProgram(this->shader); }

	GLuint GetProgram() { return this->shader; }

	GLuint GetModelLocation() { return this->uniformModel; }
	GLuint GetProjectionLocation() { return this->uniformProjection; }
	GLuint GetViewLocation() { return this->uniformView; }
	~Shader();
private:
	GLuint shader, uniformModel, uniformProjection, uniformView;
	void addShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
	void compileShaders(const char* vShaderCode, const char* fShaderCode);
};