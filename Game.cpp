#include "Game.h"
void Game::InitVar()
{
	window = nullptr;
	deltaTime = 0.f;
}

void Game::InitWin()
{
	window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Practice", sf::Style::Fullscreen);
	window->setFramerateLimit(120);
}

void Game::InitStates()
{
	states.push(new MainMenuState(window, &states));
}

Game::Game()
{
	InitWin();
	InitStates();
}

Game::~Game()
{
	delete window;
	while (!states.empty()) {
		delete states.top();
		states.pop();
	}
}

void Game::UpdateDeltaTime()
{
	deltaTime = deltaTimeClock.restart().asSeconds();
}

void Game::UpdateEvents()
{
	while (window->pollEvent(event))
		if (event.type == sf::Event::Closed)
			window->close();
}

void Game::Update()
{
	UpdateEvents();
	if (!states.empty()){
		states.top()->Update(deltaTime);
		if (states.top()->GetQuit()) {
			states.top()->EndState();
			delete states.top();
			states.pop();
		} 
	}
	else {
		window->close();
	}
}

void Game::Render()
{
	window->clear();
	if (!states.empty())
		states.top()->Render(window);
	window->display();
}

void Game::Run()
{
	while (window->isOpen()) {
		UpdateDeltaTime();
		Update();
		Render();
	}
}
