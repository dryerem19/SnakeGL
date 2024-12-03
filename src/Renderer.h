#pragma once
#include <glm/glm.hpp>
#include "Square.h"

class Renderer
{
private:
	unsigned int _shaderProgram;
	unsigned int _VBO, _VAO, _EBO;
	unsigned int _uColorLocation = -1, _uTransformLocation = -1, _uProjectionLocation = -1;
	glm::mat4 _projection;
public:
	static Renderer& GetInstance();
	void DrawSquare(Square* square) const;
	void Resize(int width, int height);

private:
	void PrepareShaders();
	void PrepareBuffers();

	Renderer();
	~Renderer();

	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;
};