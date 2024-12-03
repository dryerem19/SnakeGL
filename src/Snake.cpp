#include "Snake.h"

#include "Square.h"
#include "types/direction.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

Snake::Snake(const float initialX, const float initialY, const glm::vec3& headColor)
	: _initialX(initialX), _initialY(initialY), _headColor(headColor)
{
	_segments.push_back(std::make_unique<Square>(_initialX, _initialY, _headColor));
}

Square* Snake::GetHead()
{
	return _segments[0].get();
}

Square* Snake::GetSegment(int i)
{
	return _segments[i].get();
}

int Snake::Length()
{
	return _segments.size();
}

void Snake::Draw()
{
	const auto& renderer = Renderer::GetInstance();

	for (auto& segment : _segments)
	{
		renderer.DrawSquare(segment.get());
	}
}

void Snake::Move(Direction direction)
{
	glm::vec2 headPosition = _segments[0]->GetPosition();
	float unitSize = _segments[0]->GetScale();

	for (int iSegment = _segments.size() - 1; iSegment >= 0; iSegment--)
	{
		if (iSegment == 0)
		{
			if (direction == Direction::Up)
			{
				headPosition.y += unitSize;
				if (headPosition.y > 1.0f) {
					headPosition.y = -1.0f;
				}
			}
			else if (direction == Direction::Down)
			{
				headPosition.y -= unitSize;
				if (headPosition.y < -1.0f) {
					headPosition.y = 1.0f;
				}
			}
			else if (direction == Direction::Left)
			{
				headPosition.x -= unitSize;
				if (headPosition.x < -1.0f) {
					headPosition.x = 1.0f;
				}
			}
			else if (direction == Direction::Right)
			{
				headPosition.x += unitSize;
				if (headPosition.x > 1.0f) {
					headPosition.x = -1.0f;
				}
			}

			_segments[0]->SetPosition(headPosition);
		}
		else
		{
			glm::vec2 tmp = _segments[iSegment - 1]->GetPosition();
			_segments[iSegment]->SetPosition(tmp);
		}
	}
}

void Snake::Grow()
{
	glm::vec2 prevPosition = _segments.back()->GetPosition();
	_segments.push_back(std::make_unique<Square>(prevPosition.x, prevPosition.y));
}
