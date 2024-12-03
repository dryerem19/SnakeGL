#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "types/direction.h"

#include <memory>

#include "Food.h"
#include "Snake.h"
#include "Renderer.h"

enum class GameState
{
	GameActive,
	GamePause,
	GameMenu,
	GameOver,
	GameWin
};

class Game
{
private:
	bool _keys[1024];
	int _width, _height;
	GLFWwindow* _window;

	int _score = 0;
	GameState _state = GameState::GameMenu;
	Direction _direction;
	std::unique_ptr<Food> _food;
	std::unique_ptr<Snake> _snake;
public:
	Game(int width = 640, int height = 480);
	~Game();

	void Beep();
	int Exec();
	void NewGame();
	bool CheckCollisionAABB(Square* one, Square* two);
	bool CheckCollisionExact(Square* one, Square* two);

private:
	void ProcessInput();
	void Update();
	void Render();
	void RenderMenu();

	static void OnKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void OnFramebufferSizeCallback(GLFWwindow* window, int width, int height);
};