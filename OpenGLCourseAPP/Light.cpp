#include "Light.h"

Light::Light()
{
	color = glm::vec3(1.0f, 1.0f, 1.0f);
	ambientIntensity = 1;

	direction = glm::vec3(0.0f, -1.0f, 0.0f);
	diffuseIntensity = 1.0f;
}

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntensity,
	GLfloat xDirection, GLfloat yDirection, GLfloat zDirection, GLfloat diffuseIntensity)
{
	color = glm::vec3(red, green, blue);
	this->ambientIntensity = ambientIntensity;

	direction = glm::vec3(xDirection, yDirection, zDirection);
	this->diffuseIntensity = diffuseIntensity;
}

void Light::useLight(GLuint ambientIntensityLocation, GLuint ambientColorLocation,
	GLuint diffuseIntensityLocation, GLuint directionLocation)
{
	glUniform3f(ambientColorLocation, color.x, color.y, color.z);
	glUniform1f(ambientIntensityLocation, ambientIntensity);
	
	glUniform3f(directionLocation, direction.x, direction.y, direction.z);
	glUniform1f(diffuseIntensityLocation, diffuseIntensity);
}

Light::~Light()
{
}
