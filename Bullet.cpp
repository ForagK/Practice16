#include "Bullet.h"

Bullet::Bullet(sf::Texture* texture, float posX, float posY, float dirX, float dirY, float movementSpeed)
{
	sprite.setTexture(*texture);
	sprite.setPosition(posX, posY);
	sprite.setScale(1.f, 0.5f);
	sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
	direction.x = dirX;
	direction.y = dirY;
	this->movSpeed = movementSpeed;
}

Bullet::~Bullet()
{
}

const sf::FloatRect Bullet::getBounds() const
{
	return sprite.getGlobalBounds();
}

void Bullet::render(sf::RenderTarget* target)
{
	target->draw(sprite);
}

void Bullet::update(const float& deltaTime)
{
	sprite.move(movSpeed * direction * deltaTime);
}
