#pragma once
#include "Entity.h"
class Player :
    public Entity
{
    void InitVar();
    float attackCooldown;
    float attackCooldownMax;
public:
    Player(float x, float y, sf::Texture* texture, float movSpeed);
    virtual ~Player();
    const bool CanAttack();
    void UpdateAttack();
    void Update(const float& deltaTime);
};
