#pragma once
#include <GL/glew.h>
class Material
{
public:

	Material();
	Material(GLfloat sIntensity, GLfloat shine);
	~Material();

	void UseMaterial(GLuint specularIntensityLoc, GLuint shininessLoc );
private:
	// brightness
	GLfloat specularIntensity;
	// spead of shininess
	GLfloat shininess;
};

