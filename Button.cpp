#include "Button.h"

Button::Button(float x, float y, float width, float height, sf::Font* font, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color pressedColor,
	unsigned charSize,sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textPressedColor)
	:textIdleColor(textIdleColor), textHoverColor(textHoverColor), textPressedColor(textPressedColor),
	idleColor(idleColor), hoverColor(hoverColor), pressedColor(pressedColor),font(font),hover(0),pressed(0)
{
	shape.setPosition(sf::Vector2f(x, y));
	shape.setSize(sf::Vector2f(width, height));

	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(textIdleColor);
	this->text.setCharacterSize(charSize);
	this->text.setPosition(
		shape.getPosition().x + (shape.getGlobalBounds().width / 2.f) - (this->text.getGlobalBounds().width / 2.f),
		shape.getPosition().y - (shape.getGlobalBounds().height / 2.f) + (this->text.getGlobalBounds().height / 2.f)
	);
	this->shape.setFillColor(idleColor);
}

Button::~Button()
{
}

const bool Button::GetPressed() const
{
	return pressed;
}

void Button::Update(const sf::Vector2f mousePos)
{
	pressed = 0; 
	hover = 0;
	if (shape.getGlobalBounds().contains(mousePos)) {
		hover = 1;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			hover = 0;
			pressed = 1;
		}
	}
	if (hover) {
		shape.setFillColor(hoverColor);
		text.setFillColor(textHoverColor);
	}
	if (pressed) {
		shape.setFillColor(pressedColor);
		text.setFillColor(textPressedColor);
	}
	if (!pressed && !hover) {
		shape.setFillColor(idleColor);
		text.setFillColor(textIdleColor);
	}
}

void Button::Render(sf::RenderTarget& target)
{
	target.draw(shape);
	target.draw(text);
}
