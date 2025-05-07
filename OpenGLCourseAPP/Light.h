#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>

class Light
{
public:
	Light();
	Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntensity);

	void useLight(GLfloat ambientIntensityLocation, GLfloat ambientColorLocation);

	~Light();

private:
	glm::vec3 color;
	GLfloat ambientIntensity;
};

