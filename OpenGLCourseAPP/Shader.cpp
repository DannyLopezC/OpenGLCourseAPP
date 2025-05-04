#include "Shader.h"

Shader::Shader()
{
	shaderId = 0;
	uniformModel = 0;
	uniformProjection = 0;
}

void Shader::createFromString(const char* vertexCode, const char* fragmentCode)
{
	compileShader(vertexCode, fragmentCode);
}

void Shader::createFromFiles(const char* vertexLocation, const char* fragmentLocation)
{
	std::string vertexString = ReadFile(vertexLocation);
	std::string fragmentString = ReadFile(fragmentLocation);

	const char* vertexCode = vertexString.c_str();
	const char* fragmentCode = fragmentString.c_str();

	compileShader(vertexCode, fragmentCode);
}

std::string Shader::ReadFile(const char* location)
{
	std::string content;
	std::ifstream fileStream(location, std::ios::in);

	if (!fileStream.is_open()) {
		printf("Failed to read %s! File does not exist\n", location);
		return "";
	}

	std::string line = "";
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

GLuint Shader::getProjectionLocation()
{
	return uniformProjection;
}

GLuint Shader::getModelLocation()
{
	return uniformModel;
}

GLuint Shader::getViewLocation()
{
	return uniformView;
}

void Shader::useShader()
{
	if (shaderId == 0) {
		printf("Shader id equals 0");
	}

	glUseProgram(shaderId);
}

void Shader::clearShader()
{
	if (shaderId != 0) {
		glDeleteProgram(shaderId);
		shaderId = 0;
	}

	uniformModel = 0;
	uniformProjection = 0;
}

void Shader::compileShader(const char* vertexCode, const char* fragmentCode)
{
	shaderId = glCreateProgram();

	if (!shaderId)
	{
		printf("Error creating shader program!");
		return;
	}

	addShader(shaderId, vertexCode, GL_VERTEX_SHADER);
	addShader(shaderId, fragmentCode, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shaderId);
	glGetProgramiv(shaderId, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderId, sizeof(eLog), NULL, eLog);
		printf("Error linking program: '%s'\n", eLog);
		return;
	}

	glValidateProgram(shaderId);
	glGetProgramiv(shaderId, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderId, sizeof(eLog), NULL, eLog);
		printf("Error validating program: '%s'\n", eLog);
		return;
	}

	uniformProjection = glGetUniformLocation(shaderId, "projection");
	uniformModel = glGetUniformLocation(shaderId, "model");
	uniformView = glGetUniformLocation(shaderId, "view");
}

void Shader::addShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
	GLuint theShader = glCreateShader(shaderType);

	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
		printf("Error compiling the %d shader: '%s'\n", shaderType, eLog);
		return;
	}

	glAttachShader(theProgram, theShader);
}

Shader::~Shader()
{
	clearShader();
}