#pragma once
#include <glm/glm.hpp>

class Square
{
private:
	glm::vec3 _color = { 0.0f, 1.0f, 0.0f };
	glm::vec2 _position = { 0.0f, 0.0f };
	float _scale = 0.05f;
public:
	Square(float initialX = 0.0f, float initialY = 0.0f, const glm::vec3& color = glm::vec3(0.0f, 1.0f, 0.0f));
	
	void SetColor(const glm::vec3& color);
	void SetPosition(const glm::vec2& position);
	void SetScale(float scale);

	float GetScale() const;
	glm::vec3 GetColor() const;
	glm::vec2 GetPosition() const;
	glm::mat4 GetTransform() const;
};