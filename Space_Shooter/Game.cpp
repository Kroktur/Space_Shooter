#include "Game.h"
#include "playableGameObject.h"
Game::Game(sf::RenderWindow* window, const float& framereta) : SceneBase(window, framereta), m_Background(sf::Vector2f(m_renderwindow->getSize()))
{
	m_Background.setTexture(&m_texture.getTexture("resource\\galaxie.bmp"));
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
	for (int idx_x = 0; idx_x < m_allGameObject.size(); ++idx_x)
	{
		for (int idx_y = idx_x + 1; idx_y < m_allGameObject.size(); ++idx_y)
		{
			testColision(m_allGameObject[idx_x], m_allGameObject[idx_y]);
		}
	}
}

void Game::render()
{
	m_renderwindow->draw(m_Background);
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


