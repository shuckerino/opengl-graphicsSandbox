#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
using namespace std;


// Vertex shader
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main(){\n"
"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
// Fragment shader
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main(){\n"
"FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

int main() {

	// Initialize glfw (tool for quickly building windows and use OpenGL)
	glfwInit();

	// Set OpenGL version (here we use Version 3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell glfw that we want to use core profile
	// This means we only want to use modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLfloat vertices[] =
	{
		-0.1f, -0.3f, 0.0f,
		-0.5f, -0.3f, 0.0f,
		0.0f, 0.7f, 0.0f
	};


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

	// Create Vertex Shader Object
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// Create Fragment Shader Object
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// Create shader program 
	GLuint shaderProgram = glCreateProgram();

	// Attach both shaders to the program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	// Link the shader program
	glLinkProgram(shaderProgram);

	// Delete shaders after they have been attached
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	// Create Vertex Buffer Object (sends data from CPU to GPU)
	GLuint VAO, VBO;

	// Create and bind VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Create and bind VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);



	// Set window background color to navy blue
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	// Clear the background buffer and assign the new color to it
	glClear(GL_COLOR_BUFFER_BIT);
	// Swap the back buffer with the front buffer
	glfwSwapBuffers(window);


	// Loop for displaying the window, should only be exited if window gets closed
	while (!glfwWindowShouldClose(window)) {

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// Use shader program
		glUseProgram(shaderProgram);
		// Bind VAO
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Update each frame
		glfwSwapBuffers(window);

		// Handle glfw events
		glfwPollEvents();
	}

	// Delete all objects
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO); 
	glDeleteProgram(shaderProgram);

	// Destroy glfw window
	glfwDestroyWindow(window);

	// Terminate glfw
	glfwTerminate();

	return 0;
}