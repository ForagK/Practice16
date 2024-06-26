#include "Entity.h"

void Entity::initVar()
{
	movSpeed = 0.f;
}

Entity::Entity()
{
	initVar();
}

Entity::~Entity()
{
}

void Entity::SetPos(const float x, const float y)
{
		sprite.setPosition(x, y);
}

void Entity::SetPos(const sf::Vector2f pos)
{
	sprite.setPosition(pos);
}

void Entity::SetTexture(sf::Texture& texture)
{
	sprite.setTexture(texture);
}

const sf::Vector2f& Entity::GetPos() const
{
	return sprite.getPosition();
}

const sf::FloatRect Entity::getBounds() const
{
	return sprite.getGlobalBounds();
}

void Entity::Move(const float& deltatime, const float dirX, const float dirY)
{
	sprite.move(dirX * movSpeed * deltatime, dirY * movSpeed * deltatime);
}

void Entity::Update(const float& deltaTime)
{
}

void Entity::Render(sf::RenderTarget& target)
{
		target.draw(sprite);
}
