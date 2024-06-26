#pragma once
#include <SFML/Graphics.hpp>

class Button
{
	bool pressed;
	bool hover;
	
	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;
	sf::Color textIdleColor;
	sf::Color textHoverColor;
	sf::Color textPressedColor;
	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color pressedColor;
public:
	Button(float x, float y, float width, float height, sf::Font* font, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color pressedColor,
		unsigned charSize, sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textPressedColor);
	~Button();

	const bool GetPressed() const;

	void Update(const sf::Vector2f mousePos);
	void Render(sf::RenderTarget& target);
};
