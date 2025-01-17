//============================================================================
// Name        : Display Cube using Class
// Professor   : Herminio Paucar
// Version     :
// Description : Configure Projection view
//============================================================================

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>

// Include GLEW
#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "headers/Window.h"
#include "headers/Mesh.h"
#include "headers/Shader.h"

const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

// viewing 3D
float cameraX, cameraY, cameraZ;
float cubeLocX, cubeLocY, cubeLocZ;

void CreateObjects(){

	float vertices[] = {
	 -1.0f, -1.0f,  1.0f,//P0
	  1.0f, -1.0f,  1.0f,//P1
	  1.0f,  1.0f,  1.0f,//P2

	  1.0f,  1.0f,  1.0f,//P2
	 -1.0f,  1.0f,  1.0f,//P3
	 -1.0f, -1.0f,  1.0f //P0
	};

	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, 18);
	meshList.push_back(obj1);

	cameraX = 0.0f;
	cameraY = 0.0f;
	cameraZ = -8.0f;
	cubeLocX = 0.0f;
	cubeLocY = -2.0f;
	cubeLocZ = 0.0f;
}

void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles("src/shaders/vertShader.glsl",
								"src/shaders/fragShader.glsl");
	shaderList.push_back(*shader1);
}

int main() {
	mainWindow = Window(800, 800);
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();

	glm::mat4 mProjection, mView, mModel;

	// Loop until window closed
	while (!mainWindow.getShouldClose()) {
		// Get + Handle User Input
		glfwPollEvents();

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderList[0].UseShader();

		// get locations of uniforms in the shader program
		GLuint mLoc = shaderList[0].GetUniformVarLocation("m_matrix");
		GLuint vLoc = shaderList[0].GetUniformVarLocation("v_matrix");
		GLuint projLoc = shaderList[0].GetUniformVarLocation("proj_matrix");

		// send matrix data to the uniform variables
		GLfloat aspect = (GLfloat) mainWindow.getBufferWidth() / mainWindow.getBufferHeight();

		/* Matrix configuration to view in 3D */
		mProjection = glm::perspective(
				glm::radians(60.0f), // FOV 1.0472 radians == 60 degrees
				aspect, // width/height
				0.1f, // Near
				100.0f); // Far

		/* Camera matrix configuration position, verificar con la rotaci�n del propio objeto y camara*/
		const float radius = 10.0f;
		//cameraX = sin(glfwGetTime()) * radius;
		//cameraZ = cos(glfwGetTime()) * radius;
		// Camera matrix
		mView = glm::lookAt(
				glm::vec3(cameraX, cameraY, cameraZ), // Camera position in World Space
				glm::vec3(0, 0, 0), // and looks at the origin
				glm::vec3(0, 1, 0)); // Head is up (set to 0,-1,0 to look upside-down)

		// Model transformation Rotation
		glm::mat4 tRotat = glm::rotate(
	    		glm::mat4(1.0f),
				glm::radians((float)glfwGetTime()*50.0f),
				glm::vec3(0.0f, 1.0f, 0.0f)); //Rotate in direction to axis X, Y or Z

		// Model transformation Translate
	    glm::mat4 tTransl = glm::translate(
	    			glm::mat4(1.0f),
	    			glm::vec3(cubeLocX, cubeLocY, cubeLocZ));

	    mModel = tTransl*tRotat;

		glUniformMatrix4fv(mLoc, 1, GL_FALSE, glm::value_ptr(mModel));
		glUniformMatrix4fv(vLoc, 1, GL_FALSE, glm::value_ptr(mView));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(mProjection));
		meshList[0]->RenderMeshMultiplyInstance(5);

		glUseProgram(0);
		mainWindow.swapBuffers();
	}

	return 0;
}
