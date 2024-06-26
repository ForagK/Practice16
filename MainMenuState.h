#pragma once
#include "GameState.h"
#include "Button.h"
class MainMenuState :
    public State
{
    sf::Texture bgTexture;
    sf::RectangleShape background;
    sf::Font font;
    std::map<std::string, Button*> buttons;
    void InitBackground();
    void InitFonts();
    void InitButtons();
public:
    MainMenuState(sf::RenderWindow* window, std::stack<State*>* states);
    virtual ~MainMenuState();
    void UpdateInput(const float& deltaTime);
    void UpdateButtons();
    void Update(const float& deltaTime);
    void RenderButtons(sf::RenderTarget& target);
    void Render(sf::RenderTarget* target = nullptr);
};
