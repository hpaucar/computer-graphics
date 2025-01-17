//============================================================================
// Name        : Lab 03 Draw Triangle
// Professor   : Herminio Paucar
// Version     :
// Description : Drawing TRIANGLE using Vertex and Fragment Shader
//============================================================================

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// Include GLEW
#define GLEW_STATIC
#include <GL\glew.h>

// Include GLFW
#include <GLFW\glfw3.h>

using namespace std;

// GLuint : unsigned int
GLuint renderingProgram;

GLuint m_VBO;
GLuint m_VAO;

using namespace std;

GLuint createShaderProgram() {
    // declares two shaders as character strings
    // Vertex Shader code
    static const char *vshaderSource =
    		"#version 330  \n"
    		"layout (location = 0) in vec3 pos; \n"
    		"void main() { \n"
    		" gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);	\n"
    		"}";

    // Fragment Shader
    static const char *fshaderSource =
    		"#version 330  \n"
    		"out vec4 colour; \n"
    		"void main(){ \n"
    		" colour = vec4(0.0, 0.0, 1.0, 1.0); \n"
    		"}";
    
    // glCreateShader : generates the two shaders of types GL_VERTEX_SHADER and GL_FRAGMENT_SHADER
    // OpenGL creates each shader object, and returns an integer ID for each
    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    // loads the GLSL code from the strings into the empty shader objects
    // glShaderSource(ShaderObject, NumberOfStrings : 1, ArrayOfPointers, -)
    glShaderSource(vShader, 1, &vshaderSource, NULL);
    glShaderSource(fShader, 1, &fshaderSource, NULL);
    
    // the shaders are each compiled
    glCompileShader(vShader);
    glCompileShader(fShader);
    
    // the integer ID of a program object
    GLuint vfProgram = glCreateProgram();
    
    // attatches each of the shaders to the program object
    glAttachShader(vfProgram, vShader);
    glAttachShader(vfProgram, fShader);
    
    // requests that the GLSL compiler ensure that the shaders are compatible
    glLinkProgram(vfProgram);
    
    return vfProgram;
}

void init () {
    renderingProgram = createShaderProgram();

    GLfloat vertices[] = {
			-1.0f, -1.0f, 0.0f, //v0
			 1.0f, -1.0f, 0.0f, //v1
			 0.0f,  1.0f, 0.0f  //v2
    };

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(
			GL_ARRAY_BUFFER,
			sizeof(vertices),
			vertices,
			GL_STATIC_DRAW);

	glVertexAttribPointer(
			0,	// Atributo 0 (layout = 0 )
			3,	// cada vertice posee 3 valores
			GL_FLOAT,	// cada valor del v�rtice es del tipo GLfloat
			GL_FALSE,	// Quer normalizar os dados e converter tudo pra NDC ? ( no nosso caso, j� esta tudo correto, ent�o deixamos como FALSE)
			0,	// De quantos em quantos bytes, este atributo � encontrado no buffer
			0	// Onde est� o primeiro valor deste atributo no buffer.
	);
	glEnableVertexAttribArray(0);	// Habilita este atributo "0"

}

void display() {
    // loads the program containing the two compiled shaders into the OpenGL pipeline stages (onto the GPU)
    glUseProgram(renderingProgram);
    //glPointSize(30.0f);
    // initiates pipeline processing
    // mode: GL_POINTS, from 0, one (point)
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

int main(void) {
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); 	// Resizable option.

    GLFWwindow* window = glfwCreateWindow(800, 800, "Lab 03: Drawing Triangle with Shaders", NULL, NULL);
    glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) {
		exit(EXIT_FAILURE);
	}
	glfwSwapInterval(1);
    
    init();
    
    while (!glfwWindowShouldClose(window)) {
        display();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
