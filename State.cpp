#include "State.h"
State::State(sf::RenderWindow* window, std::stack<State*>* states)
	:window(window),states(states),quit(false)
{
}
State::~State()
{
}
const bool& State::GetQuit() const
{
	return quit;
}
void State::EndState()
{
	quit = true;
}
void State::UpdateMousePos()
{
	mousePosView = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
}
