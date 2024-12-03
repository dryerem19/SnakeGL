#include "Renderer.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

Renderer::Renderer()
	: _projection(1.0)
{
	PrepareShaders();
	PrepareBuffers();
}

Renderer::~Renderer()
{
	// De-allocate all resources
	glDeleteProgram(_shaderProgram);
	glDeleteVertexArrays(1, &_VAO);
	glDeleteBuffers(1, &_VBO);
	glDeleteBuffers(1, &_EBO);
}

Renderer& Renderer::GetInstance()
{
	static Renderer instance;
	return instance;
}

void Renderer::DrawSquare(Square* square) const
{
	glUseProgram(_shaderProgram);
	glUniformMatrix4fv(_uProjectionLocation, 1, GL_FALSE, glm::value_ptr(_projection));

	glm::vec3 color = square->GetColor();
	glUniform3f(_uColorLocation, color.x, color.y, color.z);

	glm::mat4 transform = square->GetTransform();
	glUniformMatrix4fv(_uTransformLocation, 1, GL_FALSE, glm::value_ptr(transform));

	glBindVertexArray(_VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer::Resize(int width, int height)
{
	glViewport(0, 0, width, height);
	float ratio = width / (float)height;

	_projection = glm::ortho(-ratio, ratio, -1.0f, 1.0f, -1.0f, 1.0f);
}

void Renderer::PrepareShaders()
{
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"uniform mat4 uTransform;\n"
		"uniform mat4 uProjectionLocation;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = uProjectionLocation * uTransform * vec4(aPos, 1.0);\n"
		"}\0";

	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"uniform vec3 uColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(uColor, 1.0);\n"
		"}\n\0";

	// Vertex shader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);

	// Fragment shader
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);

	// Create shader program
	_shaderProgram = glCreateProgram();
	glAttachShader(_shaderProgram, vertexShader);
	glAttachShader(_shaderProgram, fragmentShader);
	glLinkProgram(_shaderProgram);

	// De-allocate shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	_uColorLocation = glGetUniformLocation(_shaderProgram, "uColor");
	_uTransformLocation = glGetUniformLocation(_shaderProgram, "uTransform");
	_uProjectionLocation = glGetUniformLocation(_shaderProgram, "uProjectionLocation");
}

void Renderer::PrepareBuffers()
{
	const float vertices[] = {
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
	};

	// note that we start from 0!
	const unsigned int indices[] = {

		0, 1, 3,    // first triangle
		1, 2, 3,    // second triangle
	};

	glGenVertexArrays(1, &_VAO);
	glGenBuffers(1, &_VBO);
	glGenBuffers(1, &_EBO);
	glBindVertexArray(_VAO);

	// Send the vertex array to a video card memory
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Send the indices array to a video card memory
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Config
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
