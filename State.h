#pragma once
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
class State
{
protected:
	std::stack<State*>* states;
	std::map<std::string, sf::Texture*> textures;
	sf::RenderWindow* window;
	bool quit;
	sf::Vector2f mousePosView;
public:
	State(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~State();
	const bool& GetQuit()const;
	void EndState();
	virtual void UpdateMousePos();
	virtual void UpdateInput(const float& deltaTime) = 0;
	virtual void Update(const float& deltaTime) = 0;
	virtual void Render(sf::RenderTarget* target = nullptr) = 0;
};
