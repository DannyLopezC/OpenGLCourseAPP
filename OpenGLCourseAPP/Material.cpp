#include "Material.h"

Material::Material()
{
	specularIntensity = 0;
	shininess = 0;
}

Material::Material(GLfloat specularIntensity, GLfloat shininess)
{
	this->specularIntensity = specularIntensity;
	this->shininess = shininess;
}

void Material::useMaterial(GLuint specularIntensityLocation, GLuint shininessLocation)
{
	glUniform1f(specularIntensityLocation, specularIntensity);
	glUniform1f(shininessLocation, shininess);
}

Material::~Material()
{
}
