#include "Enemy.h"

Enemy::Enemy(float x, float y, sf::Texture* texture, float movSpeed, int health, int damage, int points)
	:damage(damage), points(points),health(health)
{
	SetTexture(*texture);
	SetPos(x, y);
	sprite.setScale(2.f, 2.f);
	this->movSpeed = movSpeed;
	sprite.setOrigin(sprite.getGlobalBounds().width / 4, sprite.getGlobalBounds().height / 4);
	sprite.setRotation(180);
}

Enemy::~Enemy()
{
}

int Enemy::GetHealth()
{
	return health;
}

int Enemy::GetDamage()
{
	return damage;
}

int Enemy::GetPoints()
{
	return points;
}

void Enemy::SetHealth()
{
	health -= 1;
}

void Enemy::Update(const float& deltaTime)
{
	sprite.move(0, movSpeed * deltaTime);
}
