#include "Game.h"
#include "playableGameObject.h"
#include "Input.h"
#include "MyMath.h"

Game::Game(sf::RenderWindow* window, const float& framereta) : SceneBase(window, framereta), m_Background(sf::Vector2f(m_renderwindow->getSize()))
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
	
	/*spawnObject();*/
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
}

void Game::init()
{
	m_Borderlimit = 50;
	m_player = dynamic_cast<Ship*>(new Ship(*this));
	/*auto leftTopBarrierCorner  = Vec2{0,0 };
	auto leftDownBarrierCorner = Vec2{0,static_cast<float>(m_renderwindow->getSize().y)  };

	auto RightTopBarrierCorner = Vec2{  static_cast<float>(m_renderwindow->getSize().x), 0 };
	auto RightDownBarrierCorner = Vec2{ static_cast<float>(m_renderwindow->getSize().x) ,m_Borderlimit+static_cast<float>(m_renderwindow->getSize().y) };
	
	new Barrier(*this, leftTopBarrierCorner, leftDownBarrierCorner);
	new Barrier(*this, leftDownBarrierCorner, RightDownBarrierCorner);
	new Barrier(*this, RightTopBarrierCorner, RightDownBarrierCorner);
	new Barrier(*this, leftTopBarrierCorner, RightTopBarrierCorner);*/

	/*auto testlfetBarrerP1 = Vec2{ 50,50 };
	auto testleftBarrerP2 = Vec2{ 55 ,static_cast<float>(m_renderwindow->getSize().y)-45};
	new Barrier(*this, testlfetBarrerP1, testleftBarrerP2);

	auto testupBarrerP1 = Vec2{ 50,50 };
	auto testupBarrerP2 = Vec2{ static_cast<float>(m_renderwindow->getSize().x)-45 , 55 };
	new Barrier(*this, testupBarrerP1, testupBarrerP2);

	auto testRightBarrerP1 = Vec2{ static_cast<float>(m_renderwindow->getSize().x)-45 ,55 };
	auto testRightBarrerP2 = Vec2{ static_cast<float>(m_renderwindow->getSize().x)- 50 ,static_cast<float>(m_renderwindow->getSize().y) - 50 };
	new Barrier(*this, testRightBarrerP1, testRightBarrerP2);

	auto testDawnBarrerP1 = Vec2{ 55,static_cast<float>(m_renderwindow->getSize().y) -45 };
	auto testDawnBarrerP2 = Vec2{ static_cast<float>(m_renderwindow->getSize().x) - 50,static_cast<float>(m_renderwindow->getSize().y) - 50 };
	new Barrier(*this, testDawnBarrerP1, testDawnBarrerP2);*/
	auto test = Vec2{ static_cast<float>(m_renderwindow->getSize().x / 2) ,static_cast<float>( m_renderwindow->getSize().y / 2) };
	new Barrier(*this, test, 50.f, Position_Left);
	new Barrier(*this, test, 50.f, Position_Right);
	new Barrier(*this, test, 50.f, Position_Top);
	new Barrier(*this, test, 50.f, Position_Botom);
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
	auto Enemiecount = 0;
	for (auto Object : m_allGameObject)
	{
		if (Object->gettype() == Type_Ennemie_Ship)
			++Enemiecount;
	}
	while (Enemiecount < 4)
	{
		new EnemieShip(*this, m_player->getcircle());
		++Enemiecount;
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


 
