#pragma once
#include <memory>
#include "Square.h"

class Food
{
private:
	std::unique_ptr<Square> _square;
public:
	Food();

	void Draw();
	void RandomizePosition();
	glm::vec2 GetPosition();
	Square* GetSquare() const;
};