#include "DirectionalLight.h"

DirectionalLight::DirectionalLight() : Light()
{
	direction = glm::vec3(0.0f, -1.0f, 0.0f);
}

DirectionalLight::DirectionalLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntensity, GLfloat diffuseIntensity,
	GLfloat xDirection, GLfloat yDirection, GLfloat zDirection) : Light(red, green, blue, ambientIntensity, diffuseIntensity)
{
	direction = glm::vec3(xDirection, yDirection, zDirection);
}

void DirectionalLight::useLight(GLuint ambientIntensityLocation, GLuint ambientColorLocation,
	GLuint diffuseIntensityLocation, GLuint directionLocation)
{
	glUniform3f(ambientColorLocation, color.x, color.y, color.z);
	glUniform1f(ambientIntensityLocation, ambientIntensity);

	glUniform3f(directionLocation, direction.x, direction.y, direction.z);
	glUniform1f(diffuseIntensityLocation, diffuseIntensity);
}

DirectionalLight::~DirectionalLight()
{
}
