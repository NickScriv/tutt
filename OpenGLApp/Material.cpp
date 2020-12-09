#include "Material.h"
Material::Material()
{
	specularIntensity = 0;
	shininess = 0;
}

Material::Material(GLfloat sIntensity, GLfloat shine)
{
	specularIntensity = sIntensity;
	shininess = shine;
}

void Material::UseMaterial(GLuint specularIntensityLoc, GLuint shininessLoc)
{
	glUniform1f(specularIntensityLoc, specularIntensity);
	glUniform1f(shininessLoc, shininess);
}

Material::~Material()
{

}