#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.h"
#include "Shader.h"
#include "Window.h"
#include "Camera.h"
#include "Texture.h"
#include "Light.h"

const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader*> shaderList;
Camera camera;

Texture brickTexture;
Texture dirtTexture;

Light mainLight;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

float curAngle = 0.0f;
bool sizeDirection = true;
float curSize = 0.4f;
float maxSize = 0.8f;
float minSize = 0.1f;

// Vertex Shader
static const char* vShader = "Shaders/shader.vert";

// Fragment Shader
static const char* fShader = "Shaders/shader.frag";

void createObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		0, 2, 3,
		0, 1, 2
	};

	GLfloat vertices[] =
	{
		// x     y     z     u      v
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,// left down
		0.0f, -1.0f, 1.0f, 0.5f, 0.0f,// depth
		1.0f, -1.0f, 0.0f, 1.0f, 0.0f,// right down
		0.0f, 1.0f, 0.0f, 0.5f, 1.0f// up
	};

	Mesh* obj1 = new Mesh();
	obj1->createMesh(vertices, indices, 20, 12);
	meshList.push_back(obj1);
}

void createShaders()
{
	Shader* shader1 = new Shader();
	shader1->createFromFiles(vShader, fShader);
	shaderList.push_back(shader1);
}

int main()
{
	mainWindow = Window();
	mainWindow.initialise();

	createObjects();
	createShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.5f);

	brickTexture = Texture("Textures/brick.png");
	brickTexture.loadTexture();
	
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.loadTexture();

	mainLight = Light(1.0f, 1.0f, 1.0f, 0.2f);

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformAmbientIntensity = 0, uniformAmbientColor = 0;

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);

	// loop until window closed
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		lastTime = now;

		// get and handle user input
		glfwPollEvents();

		camera.keyControl(mainWindow.getKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// clear window
		glClearColor(0, 0, 0, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (curSize >= maxSize || curSize <= minSize)
		{
			sizeDirection = !sizeDirection;
		}

		curAngle += 1;
		curAngle = fmod(curAngle, 360.0f);

		shaderList[0]->useShader();
			uniformModel = shaderList[0]->getModelLocation();
			uniformProjection = shaderList[0]->getProjectionLocation();
			uniformView = shaderList[0]->getViewLocation();
			uniformAmbientColor = shaderList[0]->getAmbientColorLocation();
			uniformAmbientIntensity = shaderList[0]->getAmbientIntensityLocation();

			mainLight.useLight(uniformAmbientIntensity, uniformAmbientColor);

			glm::mat4 model(1.0f);
			model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
			model = glm::rotate(model, curAngle * toRadians, glm::vec3(1, 0, 0));
			model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));

			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
			glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));

			brickTexture.useTexture();
			meshList[0]->renderMesh();

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	glfwTerminate();
	return 0;
}