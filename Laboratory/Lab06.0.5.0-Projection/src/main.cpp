//============================================================================
// Name        : Knowing the view in OpenGL
// Professor   : Herminio Paucar
// Version     :
// Description : Configure Projection view
//============================================================================

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// Include GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext.hpp> // Print GLM matrix.
#include <glm/gtx/string_cast.hpp>
#include "Utils.h"

using namespace std;

GLuint renderingProgram;
GLuint m_VBO;
GLuint m_VAO;

// variable allocation for display
int width, height;

void setupVertices(void) {
	// Vertex to (1*6) = 2 triangles.
	float vertexPositions[18] = {
	   // positions
	   0.5f,  0.5f, -5.0f, // top right
	   0.5f, -0.5f, -5.0f, // bottom right
	  -0.5f, -0.5f, -5.0f, // bottom left

	  -0.5f,  0.5f, -5.0f, // top left
	  -0.5f, -0.5f, -5.0f, // bottom left
	   0.5f,  0.5f, -5.0f  // top right
	};

	glGenVertexArrays(1, &m_VAO);// creates VAO and returns the integer ID
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO); // creates VBO and returns the integer ID
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glBufferData(
			GL_ARRAY_BUFFER,
			sizeof(vertexPositions),
			vertexPositions,
			GL_STATIC_DRAW);

	glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			3 * sizeof(GLfloat),
			(GLvoid*) 0);
	glEnableVertexAttribArray(0);	// Habilita este atributo Layout 0
}

void init() {
	renderingProgram = Utils::createShaderProgram("src/vertShader.glsl", "src/fragShader.glsl");
	setupVertices();
}

void display(GLFWwindow *window, double currentTime) {
	glUseProgram(renderingProgram);

    // Clear the screen to black
    glClearColor(0.02f, 0.00f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// retrieve the matrix uniform locations
    GLuint projectionLoc  = glGetUniformLocation(renderingProgram, "projection");

	// get sizes of windows.
	glfwGetFramebufferSize(window, &width, &height);

	GLfloat aspect = (float) width / (float) height;
    float FoV = (float)((int)currentTime%360); // Field of View(FoV)
    // Generates a really hard-to-read matrix, but a normal, standard 4x4 matrix nonetheless
    glm::mat4 matrix_projection = glm::perspective(
        glm::radians(FoV), 	// The vertical Field of View: in radians: the amount of "zoom". Think "camera lens".
							//Usually between 90° (extra wide) and 30° (quite zoomed in)
		aspect, // Aspect Ratio: Depends on the size of your window. Notice that 4/3 == 800/600 == 1280/960, sounds familiar ?
        0.0f,   // Near: clipping plane. Keep as big as possible, or you'll get precision issues.
        100.0f  // Far: clipping plane. Keep as little as possible.
    );
    // printf("\n::> %f", FoV*2);
    // pass them to the shaders
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &matrix_projection[0][0]);

   /* printf("\n::> %.1f\n", FoV);
    for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			printf("%4.2f ", projection[i][j]);
		}
		printf("\n");
	}
	*/
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// Use este VAO e suas configurações
	glBindVertexArray(m_VAO);
	//glPointSize(10.0);
	//glDrawArrays(GL_POINTS, 0, 6);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

int main(void) {
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);     //
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); 	// Resizable option.

	GLFWwindow *window = glfwCreateWindow(800, 800, "Lab 06.0.5: Projection view",	NULL, NULL);
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) {
		exit(EXIT_FAILURE);
	}
	glfwSwapInterval(1);

	init();

	while (!glfwWindowShouldClose(window)) {
		display(window, glfwGetTime());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
