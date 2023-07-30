#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"../headers/VBO.h"
#include"../headers/VAO.h"
#include"../headers/IBO.h"
#include"../headers/shaderClass.h"
using namespace std;

// Vertices for a triforce (= positions of corners)
GLfloat vertices[] =
{
	-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
	0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
	0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
	-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
	0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
	0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
};

// Indices storing the order of the corners in a specific order (rendering is counter clock wise by default)
GLuint indices[] =
{
	5, 0, 3,
	3, 2, 4,
	5, 4, 1
};

int main() {

	// Initialize glfw (tool for quickly building windows and use OpenGL)
	glfwInit();

	// Set OpenGL version (here we use Version 3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell glfw that we want to use core profile
	// This means we only want to use modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create actual window sized 900 x 900 and with the title "Window"
	GLFWwindow* window = glfwCreateWindow(900, 900, "Window", NULL, NULL);
	
	// Check if the window was created successfully, if not then terminate
	if (window == NULL) {
		cout << "Window could not be built..." << endl;
		glfwTerminate();
		return -1;
	}

	// Use the created glfw window by introduncing it to the current context
	glfwMakeContextCurrent(window);

	// Load Glad so it configures OpenGL
	gladLoadGL();

	// Set viewport of the window which uses OpenGL
	// Here it starts at x = 0, y = 0, and goes all the way to x = 900, y = 900
	glViewport(0, 0, 900, 900);

	// Specify shaders
	Shader shaderProgram("src/default.vert", "src/default.frag");

	// Create Vertex Array Object and bind it
	VAO VAO1;
	VAO1.Bind();

	// CreateVBO and IBO
	VBO VBO1(vertices, sizeof(vertices));
	IBO IBO1(indices, sizeof(indices));

	// Link VBO
	VAO1.LinkVBO(VBO1, 0);

	// Unbind all to 0
	VAO1.Unbind();
	IBO1.Unbind();
	VBO1.Unbind();

	// Actually fill the buffers with the data (VBO with vertices, IBO with indices)
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Loop for displaying the window, should only be exited if window gets closed
	while (!glfwWindowShouldClose(window)) {

		glClearColor(0.1f, 0.3f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Sepcify shader program we want to use
		shaderProgram.Activate();

		// Bind VAO
		VAO1.Bind();
		
		// Draw the object (mode: triangles, nr of indices: 9, datatype of indices: uint)
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		// Update each frame
		glfwSwapBuffers(window);

		// Handle glfw events
		glfwPollEvents();
	}

	// Delete all objects
	VAO1.Delete();
	VBO1.Delete();
	IBO1.Delete();
	shaderProgram.Delete();

	// Destroy glfw window
	glfwDestroyWindow(window);

	// Terminate glfw
	glfwTerminate();

	return 0;
}