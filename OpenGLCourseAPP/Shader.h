#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include <GL/glew.h>

class Shader
{
public:
	Shader();

	void createFromString(const char* vertexCode, const char* fragmentCode);
	void createFromFiles(const char* vertexLocation, const char* fragmentLocation);

	std::string ReadFile(const char* location);

	GLuint getProjectionLocation();
	GLuint getModelLocation();
	GLuint getViewLocation();
	GLuint getEyePositionLocation();
	GLuint getAmbientIntensityLocation();
	GLuint getAmbientColorLocation();
	GLuint getDiffuseIntensityLocation();
	GLuint getDiffuseDirectionLocation();
	GLuint getSpecularIntensityLocation();
	GLuint getShininessLocation();


	void useShader();

	~Shader();

private:

	GLuint shaderId, uniformProjection, uniformModel, uniformView, uniformEyePosition,
		uniformAmbientIntensity, uniformAmbientColor, uniformDiffuseIntensity, uniformDiffuseDirection,
		uniformSpecularIntensity, uniformShininess;

	void compileShader(const char* vertexCode, const char* fragmentCode);
	void addShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);

	void clearShader();
};

