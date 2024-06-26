#include "Player.h"
void Player::InitVar()
{
	attackCooldownMax = 10.f;
	attackCooldown = 5.f;
}

Player::Player(float x, float y, sf::Texture* texture, float movSpeed)
{
	InitVar();
	SetTexture(*texture);
	SetPos(x, y);
	sprite.setScale(3.f, 3.f);
	this->movSpeed = movSpeed;
	sprite.setOrigin(sprite.getGlobalBounds().width / 6, sprite.getGlobalBounds().height / 6);
}

Player::~Player()
{

}

const bool Player::CanAttack()
{
	if (attackCooldown >= attackCooldownMax) {
		attackCooldown = 0.f;
		return true;
	}
	return false;
}

void Player::UpdateAttack()
{
	if (attackCooldown < attackCooldownMax)
		attackCooldown += 0.5f;
}

void Player::Update(const float& deltaTime)
{
	UpdateAttack();
}
