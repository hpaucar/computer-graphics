//============================================================================
// Name        : Translate X, Y, Diagonal Triangle Object
// Professor   : Herminio Paucar
// Version     :
// Description :
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
#include "Utils.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

GLuint renderingProgram;

GLfloat* m_Vertices;
GLuint n_Coords;
GLuint m_VBO;
GLuint m_VAO;

bool direction = true;
float triOffset = 0.0f;
float triMaxOffset = 0.7f;
float triIncrement = 0.005f;

void init () {

	// Utils
	renderingProgram = Utils::createShaderProgram("src/vertShader.glsl", "src/fragShader.glsl");

	// Cria um ID na GPU para um array de  buffers
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

    // The first 3 points are to Vertex position of Triangle
	m_Vertices = new GLfloat[9] {
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f
	};
	n_Coords = 9;
	// Cria um ID na GPU para nosso buffer
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	// Reserva memoria na GPU para um TARGET receber dados
	// Copia esses dados pra essa �rea de memoria
	glBufferData(
			GL_ARRAY_BUFFER,	// TARGET associado ao nosso buffer
			n_Coords * sizeof(GLfloat),	// tamanho do buffer
			m_Vertices,			// Dados a serem copiados pra GPU
			GL_STATIC_DRAW		// Pol�tica de acesso aos dados, para otimiza��o
		);

	glVertexAttribPointer(
			0,			// Lembra do (layout = 0 ) no vertex shader ? Esse valor indica qual atributo estamos indicando
			3,			// cada vertice � composto de 3 valores
			GL_FLOAT,	// cada valor do v�rtice � do tipo GLfloat
			GL_FALSE,	// Quer normalizar os dados e converter tudo pra NDC ? ( no nosso caso, j� esta tudo correto, ent�o deixamos como FALSE)
			0 * sizeof(GLfloat),// De quantos em quantos bytes, este atributo � encontrado no buffer ? No nosso caso 3 floats pros vertices + 3 floats pra cor = 6 floats
			(GLvoid*) 0	// Onde est� o primeiro valor deste atributo no buffer. Nesse caso, est� no in�cio do buffer
		);

	glEnableVertexAttribArray(0);	// Habilita este atributo
}

void display(double currentTime) {
	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(renderingProgram);

	if (direction)
		triOffset += triIncrement;
	else
		triOffset -= triIncrement;

	if (std::abs(triOffset) >= triMaxOffset)
		direction = !direction;

	GLuint modelLoc = glGetUniformLocation(renderingProgram, "model");

	//Movimiento Horizontal
	//@Param_first: Identy Matrix, @Param_second: Translate position
	//glm::mat4 t_model = glm::translate(glm::mat4(1.0), glm::vec3(triOffset, 0.0f, 0.0f));
	//Movimiento Vertical
	//glm::mat4 t_model = glm::translate(glm::mat4(1.0), glm::vec3(0.0f, triOffset, 0.0f));
	//Movimiento Diagonal
	glm::mat4 t_model = glm::translate(glm::mat4(1.0), glm::vec3(triOffset, triOffset, 0.0f));

	//Usando UniformMatrix
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(t_model));
	//glProgramUniformMatrix4fv(renderingProgram, uniformModel, 1, GL_FALSE, glm::value_ptr(model));

	// Use este VAO e suas configura��es
	glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
	glUseProgram(0);
}

int main(void) {
    if (!glfwInit()) {
    	exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  //
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            //
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); 	// Resizable option.

    GLFWwindow* window = glfwCreateWindow(800, 800, "Lab06.0: Translate of Triangle", NULL, NULL);
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) {
    	exit(EXIT_FAILURE);
    }
    glfwSwapInterval(1);

    init();

    while (!glfwWindowShouldClose(window)) {
        display(glfwGetTime());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
