#pragma once

#include <GL/glew.h>
#include <stdio.h>
#include <string.h>

class Mesh
{
public:
	Mesh();

	void createMesh(GLfloat* vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices);
	void renderMesh();
	void clearMesh();

	~Mesh();

private:
	GLuint VAO, VBO, IBO;
	GLsizei indexCount;
};

