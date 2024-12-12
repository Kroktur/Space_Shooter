#include "Game.h"

inline Game::Game(sf::RenderWindow* window, const float& framereta) : SceneBase(window, framereta)
{

}

void Game::processInput(const sf::Event& event)
{
}

void Game::update(const float& deltaTime)
{
}

void Game::render()
{

}

sf::Vector2u Game::getWindowSize()
{
	return m_renderwindow->getSize();
}

sf::RenderWindow* Game::getWindow()
{
	return m_renderwindow;
}


