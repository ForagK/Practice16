#pragma once
#include "Entity.h"
class Enemy :
    public Entity
{
    int health;
    int damage;
    int points;
public:
    Enemy(float x, float y, sf::Texture* texture, float movSpeed, int health, int damage, int points);
    virtual ~Enemy();
    int GetHealth();
    int GetDamage();
    int GetPoints();
    void SetHealth();
    void Update(const float& deltaTime);
};
