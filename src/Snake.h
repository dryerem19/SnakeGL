#pragma once
#include <deque>
#include <vector>
#include <memory>
#include <glm/glm.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Food.h"
#include "types/direction.h"

#include "Renderer.h"

// Forward declaration
class Square;

class Snake
{
private:
	float _initialX;
	float _initialY;

	glm::vec3 _headColor;
	std::vector<std::unique_ptr<Square>> _segments;
public:
	Snake(const float initialX = 0.0f, const float initialY = 0.0f,
		const glm::vec3& headColor = { 0.0f, 0.0f, 1.0f });

	Square* GetHead();
	Square* GetSegment(int i);
	int Length();

	void Draw();
	void Move(Direction direction);
	void Grow();
};