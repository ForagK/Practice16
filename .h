#pragma once
#include <SFML/Graphics.hpp>
#include "Hitbox.h"
class Hitbox
{
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	float offsetX;
	float offsetY;

public:
	Hitbox(sf::Sprite& sprite, float offsetX, float offsetY, float width, float height);
	virtual ~Hitbox();
	bool CheckIntersect(const sf::FloatRect& fRect);
	void Update();
	void Render(sf::RenderTarget& target);
};

