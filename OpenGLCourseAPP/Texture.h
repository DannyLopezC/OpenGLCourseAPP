#pragma once
#include <GL/glew.h>
#include "stb_image.h"

class Texture
{
public:
	Texture();
	Texture(const char* fileLocation);

	void loadTexture();
	void useTexture();
	void clearTexture();

	~Texture();

private:

	GLuint textureId;
	int width, height, bitDepth;

	const char* fileLocation;
};

