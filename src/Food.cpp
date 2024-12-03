#include "Food.h"
#include "Renderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>

Food::Food()
{
	_square = std::make_unique<Square>();
	_square->SetColor({1.0f, 0.0f, 0.0f});
}

void Food::Draw()
{
	Renderer::GetInstance().DrawSquare(_square.get());
}

void Food::RandomizePosition()
{
	float x = glm::linearRand(-1.0f, 1.0f);
	float y = glm::linearRand(-1.0f, 1.0f);

	_square->SetPosition({x, y});
}

glm::vec2 Food::GetPosition()
{
	return _square->GetPosition();
}

Square* Food::GetSquare() const
{
	return _square.get();
}
