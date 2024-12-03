#include "Square.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Square::Square(float initialX, float initialY, const glm::vec3& color)
{
	_position.x = initialX;
	_position.y = initialY;
	_color = color;
}

void Square::SetColor(const glm::vec3& color)
{
	_color = color;
}

void Square::SetPosition(const glm::vec2& position)
{
	_position = position;
}

void Square::SetScale(float scale)
{
	_scale = scale;
}

float Square::GetScale() const
{
	return _scale;
}

glm::vec3 Square::GetColor() const
{
	return _color;
}

glm::vec2 Square::GetPosition() const
{
	return _position;
}

glm::mat4 Square::GetTransform() const
{
	// Make sure to initialize matrix to identity matrix first
	glm::mat4 transform = glm::mat4(1.0f);

	// Set a position of the square
	transform = glm::translate(transform, glm::vec3(_position, 0.0f));

	// Set a size of the square
	transform = glm::scale(transform, glm::vec3(_scale));

	return transform;
}
