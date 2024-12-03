#include "Game.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <iostream>
#include <stdexcept>

Game::Game(int width, int height) 
	: _width(width), _height(height), _keys(), _direction(Direction::Right)
{
	if (glfwInit() == GLFW_FALSE) {
		throw std::runtime_error("Failed to initialize GLFW library");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_window = glfwCreateWindow(_width, _height, "Snake game by dryerem19", nullptr, nullptr);
	if (_window == nullptr) {
		throw std::runtime_error("Failed to create GLFW window");
	}
	
	glfwMakeContextCurrent(_window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw std::runtime_error("Failed to initialize GLAD");
	}

	glfwSwapInterval(1);

	glfwSetWindowUserPointer(_window, reinterpret_cast<void*>(this));
	glfwSetKeyCallback(_window, Game::OnKeyCallback);
	glfwSetFramebufferSizeCallback(_window, Game::OnFramebufferSizeCallback);

	glViewport(0, 0, _width, _height);

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(_window, true);
	ImGui_ImplOpenGL3_Init();

	// Инициализация подсистемы рендеринга
	Renderer::GetInstance();
}

Game::~Game()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
}

void Game::Beep()
{
	// Выводит звук
	std::cout << "\a";
}

// Игровой цикл
int Game::Exec()
{
	const double MS_PER_UPDATE = 1.0 / 10.0;
	double previous = glfwGetTime();
	double lag = 0.0f;

	while (!glfwWindowShouldClose(_window))
	{
		double current = glfwGetTime();
		double elapsed = current - previous;
		previous = current;
		lag += elapsed;

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		glfwPollEvents();
		ProcessInput();

		while (lag >= MS_PER_UPDATE)
		{
			Update();
			lag -= MS_PER_UPDATE;
		}

		// Render the Dear ImGui frame
		RenderMenu();
		ImGui::Render();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		// Render the game
		Render();

		// Render the ImGui frame
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(_window);
	}

	return EXIT_SUCCESS;
}

void Game::NewGame()
{
	_food = std::make_unique<Food>();
	_food->RandomizePosition();

	_direction = Direction::Right;
	_snake = std::make_unique<Snake>();

	_state = GameState::GameActive;
	_score = 0;
}

// Точная проверка столкновения
bool Game::CheckCollisionExact(Square* one, Square* two)
{
	glm::vec2 onePosition = one->GetPosition();
	glm::vec2 twoPosition = two->GetPosition();

	bool collisionX = (onePosition.x == twoPosition.x);
	bool collisionY = (onePosition.y == twoPosition.y);
	
	return collisionX && collisionY;
}

// Проверка столкновения двух объектов по AABB
bool Game::CheckCollisionAABB(Square* one, Square* two)
{
	glm::vec2 onePosition = one->GetPosition();
	glm::vec2 twoPosition = two->GetPosition();

	bool collisionX = onePosition.x + one->GetScale() >= twoPosition.x &&
		twoPosition.x + two->GetScale() >= onePosition.x;

	bool collisionY = onePosition.y + one->GetScale() >= twoPosition.y &&
		twoPosition.y + two->GetScale() >= onePosition.y;

	return collisionX && collisionY;
}

// Обработка пользовательского ввода
void Game::ProcessInput()
{
	if (_state == GameState::GameActive) 
	{
		if (_keys[GLFW_KEY_ESCAPE])
		{
			_state = GameState::GamePause;
			return;
		}

		if (_keys[GLFW_KEY_W])
		{
			if (_direction == Direction::Down || _direction == Direction::Up) {
				return;
			}

			_direction = Direction::Up;
		}

		if (_keys[GLFW_KEY_S])
		{
			if (_direction == Direction::Down || _direction == Direction::Up) {
				return;
			}

			_direction = Direction::Down;
		}

		if (_keys[GLFW_KEY_A])
		{
			if (_direction == Direction::Right || _direction == Direction::Left) {
				return;
			}

			_direction = Direction::Left;
		}

		if (_keys[GLFW_KEY_D])
		{
			if (_direction == Direction::Right || _direction == Direction::Left) {
				return;
			}

			_direction = Direction::Right;
		}
	}
}

// Обновление состояния игры
void Game::Update()
{
	if (_state == GameState::GameActive) 
	{
		_snake->Move(_direction);

		// Проверка столкновения головы с едой
		if (CheckCollisionAABB(_snake->GetHead(), _food->GetSquare()))
		{
			Beep();
			_snake->Grow();
			_food->RandomizePosition();
			_score++;
		}
		else
		{
			// Проверка столкновения головы с телом змейки
			for (int i = 1; i < _snake->Length(); i++)
			{
				if (CheckCollisionExact(_snake->GetSegment(i), _snake->GetHead()))
				{
					_state = GameState::GameOver;
					break;
				}
			}
		}
	}
}

// Вывод на экран
void Game::Render()
{
	if (_state == GameState::GameActive) 
	{
		_food->Draw();
		_snake->Draw();
	}
}

void Game::RenderMenu()
{
	ImGuiIO& io = ImGui::GetIO();

	if (_state == GameState::GameOver)
	{
		ImGui::SetNextWindowPos({ io.DisplaySize.x * 0.5f, 100 }, ImGuiCond_Always, ImVec2(0.5f, 0.5f));
		if (ImGui::Begin("FakeWindow", nullptr, ImGuiWindowFlags_AlwaysAutoResize | 
			ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground))
		{
			static const std::string text = "Gameover!";

			auto windowWidth = ImGui::GetWindowSize().x;
			auto textWidth = ImGui::CalcTextSize(text.c_str()).x;
			
			// Текст по центру
			ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
			ImGui::Text(text.c_str());
			ImGui::End();
		}
	}

	if (_state == GameState::GameActive)
	{
		// Выравнивание окна в правый верхний угол
		ImGui::SetNextWindowPos({ io.DisplaySize.x, 0.0f }, ImGuiCond_Always, { 1.0f, 0.0f });
		if (ImGui::Begin("Score", nullptr,
			ImGuiWindowFlags_AlwaysAutoResize |
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoCollapse))
		{
			std::string scoreString = "Your score: " + std::to_string(_score);
			ImGui::Text(scoreString.c_str());
			ImGui::End();
		}
	}

	if (_state == GameState::GameMenu || _state == GameState::GamePause || _state == GameState::GameOver) 
	{
		// Выравнивание окна по центру
		ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));

		// Применяем стиль к окну для выравнивания заголовка по центру окна
		ImGui::PushStyleVar(ImGuiStyleVar_WindowTitleAlign, ImVec2(0.5f, 0.5f));

		if (ImGui::Begin("Main menu", nullptr,
			ImGuiWindowFlags_AlwaysAutoResize |
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoCollapse))
		{
			static const float buttonWidth = 75.0f;
			static const float buttonHeight = 20.0f;

			// Выравниваем кнопку по центру
			ImGui::SetCursorPosX((ImGui::GetWindowWidth() - buttonWidth) / 2.0f);
			if (ImGui::Button("New game", ImVec2(buttonWidth, buttonHeight))) {
				NewGame();
			}

			if (_state == GameState::GamePause)
			{
				ImGui::SetCursorPosX((ImGui::GetWindowWidth() - buttonWidth) / 2.0f);
				if (ImGui::Button("Continue", ImVec2(buttonWidth, buttonHeight))) {
					_state = GameState::GameActive;
				}
			}

			ImGui::SetCursorPosX((ImGui::GetWindowWidth() - buttonWidth) / 2.0f);
			if (ImGui::Button("Exit", ImVec2(buttonWidth, buttonHeight))) {
				glfwSetWindowShouldClose(_window, true); // Закрываем окно
			}

			ImGui::PopStyleVar(); // Отменяем стиль
			ImGui::End();
		}
	}
}

// Обработчик нажатия клавиш
void Game::OnKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	Game* handle = reinterpret_cast<Game*>(glfwGetWindowUserPointer(window));
	if (!handle) {
		return;
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS) {
			handle->_keys[key] = true;
		}
		else if (action == GLFW_RELEASE) {
			handle->_keys[key] = false;
		}
	}
}

void Game::OnFramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	Renderer::GetInstance().Resize(width, height);
}
