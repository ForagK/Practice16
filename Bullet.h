#pragma once
#include "Entity.h"

class Bullet :
    public Entity
{
    sf::Sprite sprite;
    sf::Vector2f direction;
public:
    Bullet(sf::Texture* texture, float posX, float posY, float dirX,float dirY,float movementSpeed);
    virtual ~Bullet();
    
    const sf::FloatRect getBounds() const;
    void update(const float& deltaTime);
    void render(sf::RenderTarget* target);
};
