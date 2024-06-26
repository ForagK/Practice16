#pragma once
#include <SFML/Graphics.hpp>
#include<vector>
#include<time.h>
#include<sstream>
#include<string>
#include<stack>
#include<map>
class Entity
{
	void initVar();
protected:
	sf::Sprite sprite;
	float movSpeed;
public:
	Entity();
	virtual ~Entity();
	void SetTexture(sf::Texture& texture);
	const sf::Vector2f& GetPos()const;
	const sf::FloatRect getBounds() const;
	virtual void SetPos(const float x, const float y);
	virtual void SetPos(const sf::Vector2f pos);
	virtual void Move(const float& deltatime, const float x, const float y);
	virtual void Update(const float& deltaTime);
	virtual void Render(sf::RenderTarget& target);
};
