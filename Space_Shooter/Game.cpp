#include "Game.h"
#include "playableGameObject.h"
#include "Input.h"
#include "MyMath.h"

// a enlever
#include <iostream>

Game::Game(sf::RenderWindow* window, const float& framereta) : SceneBase(window, framereta), m_Background(sf::Vector2f(m_renderwindow->getSize())) , m_scorebase(5)
{
	m_input = new GameInput(*this);
	m_Background.setTexture(&m_texture.getTexture("resource\\galaxie.bmp"));
	init();
}

Game::~Game()
{

	for (auto Object : m_allGameObject)
		delete Object;
	delete m_input;
}

void Game::processInput(sf::Event& event)
{
	m_input->processinput(event);
    objectinput(event);
			

	
}

void Game::objectinput(sf::Event& event)
{
	
	for (auto Object : m_allGameObject)
	{
		Object->input(event);
	}
}

void Game::update(const float& deltaTime)
{
	
	spawnObject();
	addObject();
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
	deleteObject();
}

void Game::render()
{
	m_renderwindow->draw(m_Background);
	for (auto Object : m_allGameObject)
	{
		Object->render();
	}
	if (m_showAABB)
		renderAABB();

	std::cout << m_totalscore << std::endl;
}

void Game::init()
{
	m_Borderlimit = 500;
	m_player = dynamic_cast<Ship*>(new Ship(*this));
	
	auto centerpointinwindow = Vec2{ static_cast<float>(m_renderwindow->getSize().x / 2) ,static_cast<float>( m_renderwindow->getSize().y / 2) };

	
	new Barrier(*this, centerpointinwindow, m_Borderlimit + m_renderwindow->getSize().x,2*( m_Borderlimit + m_renderwindow->getSize().y), Position_Left );
	new Barrier(*this, centerpointinwindow, m_Borderlimit + m_renderwindow->getSize().x, 2 * (m_Borderlimit + m_renderwindow->getSize().y), Position_Right);
	new Barrier(*this, centerpointinwindow, m_Borderlimit + m_renderwindow->getSize().y, 2 * (m_Borderlimit + m_renderwindow->getSize().x), Position_Top);
	new Barrier(*this, centerpointinwindow, m_Borderlimit + m_renderwindow->getSize().y, 2 * (m_Borderlimit + m_renderwindow->getSize().x), Position_Botom);

	new Barrier(*this, centerpointinwindow,  m_renderwindow->getSize().x /2 +10 , m_renderwindow->getSize().y + 20, Position_Left , Type_Barrier_Only_Misssile);
	new Barrier(*this, centerpointinwindow,  m_renderwindow->getSize().x/2 + 10, m_renderwindow->getSize().y + 20, Position_Right, Type_Barrier_Only_Misssile);
	new Barrier(*this, centerpointinwindow, m_renderwindow->getSize().y/2 + 10, m_renderwindow->getSize().x + 20, Position_Top, Type_Barrier_Only_Misssile);
	new Barrier(*this, centerpointinwindow,  m_renderwindow->getSize().y /2 + 10, m_renderwindow->getSize().x + 20, Position_Botom, Type_Barrier_Only_Misssile);
	
}





sf::Vector2u Game::getWindowSize()
{
	return m_renderwindow->getSize();
}

sf::RenderWindow* Game::getWindow()
{
	return m_renderwindow;
}

void Game::spawnObject()
{
	m_spawnrime = m_spawn.getElapsedTime();
	auto Enemiecount = 0;
	for (auto Object : m_allGameObject)
	{
		if (Object->gettype() == Type_Ennemie_Ship)
			++Enemiecount;
	}
	while (Enemiecount < 8)
	{
		new EnemieShip(*this, m_player->getcircle());
		++Enemiecount;
	}
	if (m_spawnrime.asSeconds() >= 1.5)
	{
		if(m_rand.getrandomnumber(0,2) == 1)
		new Asteroid(*this);
		if (m_rand.getrandomnumber(0, 1) == 1)
			new Commette(*this);
		m_spawn.restart();
	}
}

void Game::addObject()
{
	for (auto toaddgameobject : m_tobeaddGameObject)
		m_allGameObject.push_back(toaddgameobject);
	m_tobeaddGameObject.clear();
}

void Game::toberemoved(IGameObject* it)
{
m_toberemovedGameObject.push_back(it);
}

void Game::deleteObject()
{
	
	for (auto it = m_toberemovedGameObject.begin(); it != m_toberemovedGameObject.end(); )
	{
		auto gameObjIt = std::find(m_allGameObject.begin(), m_allGameObject.end(), *it);
		if (gameObjIt != m_allGameObject.end())
		{
			delete* gameObjIt;
			m_allGameObject.erase(gameObjIt);
			it = m_toberemovedGameObject.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void Game::renderAABB()
{
	for (auto Object : m_allGameObject)
	{
		auto AABB = Object->GetBoundingBox();
		sf::VertexArray line(sf::Lines, 8);


		line[0].position = sf::Vector2f(AABB.Amin.x, AABB.Amin.y);
		line[1].position = sf::Vector2f(AABB.Amin.x, AABB.Amax.y);

		line[2].position = sf::Vector2f(AABB.Amin.x, AABB.Amax.y);
		line[3].position = sf::Vector2f(AABB.Amax.x, AABB.Amax.y);

		line[4].position = sf::Vector2f(AABB.Amax.x, AABB.Amax.y);
		line[5].position = sf::Vector2f(AABB.Amax.x, AABB.Amin.y);

		line[6].position = sf::Vector2f(AABB.Amax.x, AABB.Amin.y);
		line[7].position = sf::Vector2f(AABB.Amin.x, AABB.Amin.y);
		
		for (int i = 0; i < 8; ++i) {
			line[i].color = sf::Color::Green;  
		}
		m_renderwindow->draw(line);
	}

}

void Game::addScore(int score)
{
	m_totalscore += score;
}




 
