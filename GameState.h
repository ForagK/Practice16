#pragma once
#include "State.h"
class GameState :
    public State
{
    Player* player;
    Enemy* enemy;
    sf::RectangleShape background;
    sf::RectangleShape borderLeft;
    sf::RectangleShape borderRight;
    sf::Sprite hpBarBorder;
    sf::Sprite hpBar;
    Bullet* bullet;
    float spawnTimer;
    float spawnTimerMax;
    float spawnTimerCurrent;
    std::vector<Bullet*> bullets;
    std::vector<Enemy*> enemies;
    sf::Font font;
    sf::Text pointText;
    sf::Text gameOverText;
    unsigned points;
    int health;
    int healthMax;
    bool gameOver;
    void InitStats();
    void InitTextures();
    void InitPlayer();
    void InitEnemy();
    void InitGui();
    void InitBackground();
    void InitFonts();
public:
    GameState(sf::RenderWindow* window, std::stack<State*>* states);
    virtual ~GameState();
    void ReduceHealth(int damage);
    void UpdateInput(const float& deltaTime);
    void UpdateGui();
    void UpdateCollision();
    void UpdateTimer();
    void UpdateBullets(const float& deltaTime);
    void UpdateEnemy(const float& deltaTime);
    void Update(const float& deltaTime);
    void Render(sf::RenderTarget* target = nullptr);
};
