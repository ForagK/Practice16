#include "MainMenuState.h"

void MainMenuState::InitBackground()
{
	background.setSize(sf::Vector2f(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)));
	bgTexture.loadFromFile("Resources/background.png");
	background.setTexture(&bgTexture);
}

void MainMenuState::InitFonts()
{
	font.loadFromFile("Resources/Silver.ttf");
}

void MainMenuState::InitButtons()
{
	buttons["gameState"] = new Button(window->getSize().x/2.f - 125.f,
		window->getSize().y / 10.f * 5.f,
		250, 75, &font, "Start Game", 
		sf::Color(41,158,162,0), sf::Color(29, 112, 115, 0), sf::Color(27, 104, 107, 0),
		75,  sf::Color(29, 112, 115, 255), sf::Color(41, 158, 162, 255), sf::Color(27, 104, 107, 255));
	
	buttons["exitState"] = new Button(window->getSize().x / 2.f - 60.f,
		window->getSize().y / 10.f * 8.f,
		120, 75, &font, "Quit", 
		sf::Color(41, 158, 162, 0), sf::Color(29, 112, 115, 0), sf::Color(27, 104, 107, 0),
		75,  sf::Color(29, 112, 115, 255), sf::Color(41, 158, 162, 255), sf::Color(27, 104, 107, 255));
}

MainMenuState::MainMenuState(sf::RenderWindow* window, std::stack<State*>* states)
	:State(window, states)
{
	InitBackground();
	InitFonts();
	InitButtons();
}

MainMenuState::~MainMenuState()
{
	auto it = buttons.begin();
	for (it = buttons.begin(); it != buttons.end(); ++it) {
		delete it->second;
	}
}

void MainMenuState::UpdateInput(const float& deltaTime)
{
}

void MainMenuState::UpdateButtons()
{	
	for (auto& it : buttons) {
		it.second->Update(mousePosView);
	}
	
	if (buttons["gameState"]->GetPressed()) {
		states->push(new GameState(window, states));
	}
	
	if (buttons["exitState"]->GetPressed()) {
		EndState();
	}
}

void MainMenuState::Update(const float& deltaTime)
{
	UpdateMousePos();
	UpdateInput(deltaTime);
	UpdateButtons();
}

void MainMenuState::RenderButtons(sf::RenderTarget& target)
{
	for (auto& it : buttons) {
		it.second->Render(target);
	}
}

void MainMenuState::Render(sf::RenderTarget* target)
{
	if (!target)
		target = window;
	target->draw(background);
	RenderButtons(*target);
}
