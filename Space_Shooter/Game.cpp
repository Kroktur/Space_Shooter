#include "Game.h"
#include "playableGameObject.h"
Game::Game(sf::RenderWindow* window, const float& framereta) : SceneBase(window, framereta)
{
	init();
}

Game::~Game()
{
	for (auto Object : m_allGameObject)
		delete Object;
	m_allGameObject.clear();
	
}

void Game::processInput(const sf::Event& event)
{
	for (auto Object : m_allGameObject)
	{
		Object->input(event);
	}
}

void Game::update(const float& deltaTime)
{
	m_allGameObject = m_goingtoaddGameObject;
	for (auto Object : m_allGameObject)
	{
		Object->update(deltaTime);
	}
}

void Game::render()
{
	for (auto Object : m_allGameObject)
	{
		Object->render();
	}
}

void Game::init()
{
	auto test = new Ship(*this);
	auto test_ = dynamic_cast<Ship*>(test);
	new EnemieShip(*this, test_->getcircle());
}



sf::Vector2u Game::getWindowSize()
{
	return m_renderwindow->getSize();
}

sf::RenderWindow* Game::getWindow()
{
	return m_renderwindow;
}


