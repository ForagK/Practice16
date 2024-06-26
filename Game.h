#pragma once
#include "MainMenuState.h"
class Game
{
	sf::RenderWindow *window;
	sf::Event event;
	sf::Clock deltaTimeClock;
	float deltaTime;
	std::stack<State*> states;

	void InitVar();
	void InitWin();
	void InitStates();
public:
	Game();
	virtual ~Game();

	void UpdateDeltaTime();
	void UpdateEvents();
	void Update();

	void Render();
	
	void Run();
};
