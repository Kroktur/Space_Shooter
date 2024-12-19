#include "Game.h"
#include "playableGameObject.h"
#include "Input.h"
#include "MyMath.h"
#include "WidgetGameObject.h"



Game::Game(sf::RenderWindow* window, const float& framereta) : SceneBase(window, framereta) , m_scorebase(5), m_bossevent(false)
{
	m_input = new GameInput(*this);
	m_Background.setSize(sf::Vector2f(m_renderwindow->getSize()));
	switch (m_rand.getrandomnumber(0, 2))
	{
	case 0:
		m_Background.setTexture(&m_texture.getTexture("resource\\galaxie.bmp"));
		break;
	case 1:
		m_Background.setTexture(&m_texture.getTexture("resource\\galaxie2.bmp"));
		break;
	case 2:
		m_Background.setTexture(&m_texture.getTexture("resource\\galaxie3.png"));
	}
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
	rule();
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
	
	m_Borderlimit = 1000;
	m_player = dynamic_cast<Ship*>(new Ship(*this));
	
	auto centerpointinwindow = Vec2{ static_cast<float>(m_renderwindow->getSize().x / 2) ,static_cast<float>( m_renderwindow->getSize().y / 2) };

	new Barrier(*this, centerpointinwindow, m_Borderlimit + m_renderwindow->getSize().x, 2 * ( m_Borderlimit + m_renderwindow->getSize().y), Position_Left );
	new Barrier(*this, centerpointinwindow, m_Borderlimit + m_renderwindow->getSize().x, 2 * (m_Borderlimit + m_renderwindow->getSize().y), Position_Right);
	new Barrier(*this, centerpointinwindow, m_Borderlimit + m_renderwindow->getSize().y, 2 * (m_Borderlimit + m_renderwindow->getSize().x), Position_Top);
	new Barrier(*this, centerpointinwindow, m_Borderlimit + m_renderwindow->getSize().y, 2 * (m_Borderlimit + m_renderwindow->getSize().x), Position_Botom);

	new Barrier(*this, centerpointinwindow,  m_renderwindow->getSize().x /2 +10 , m_renderwindow->getSize().y + 20, Position_Left , Type_Barrier_Only_Misssile);
	new Barrier(*this, centerpointinwindow,  m_renderwindow->getSize().x/2 + 10, m_renderwindow->getSize().y + 20, Position_Right, Type_Barrier_Only_Misssile);
	new Barrier(*this, centerpointinwindow, m_renderwindow->getSize().y/2 + 10, m_renderwindow->getSize().x + 20, Position_Top, Type_Barrier_Only_Misssile);
	new Barrier(*this, centerpointinwindow,  m_renderwindow->getSize().y /2 + 10, m_renderwindow->getSize().x + 20, Position_Botom, Type_Barrier_Only_Misssile);

	auto scalescorerectangle = Vec2{ 300,80 };
	auto positionscorerectangle = Vec2{ static_cast<float>(m_renderwindow->getSize().x/2),0 + scalescorerectangle.y};

	tmps = new Rectanglewidgetupdatable(*this, positionscorerectangle, scalescorerectangle, "total score : ",& m_totalscore);
	tmps->settextSize(20);
	tmps->setcolor(sf::Color(sf::Color::Black));
	tmps->setTexture("resource\\etiquette.png");
	tmps->setFont("resource\\font\\static\\TMT-Paint-Regular.otf");
	tmps->setTextPosition({positionscorerectangle.x - scalescorerectangle.x /4 - 40,positionscorerectangle.y - scalescorerectangle.y/4 +5 });
	/*new BossFoxTentacle(*this, m_player->getcircle());*/
	/*new BossLuminux(*this, m_player->getcircle());*/
}







void Game::rule()
{
	if (m_bossevent )
	{
		for (auto Object : m_allGameObject)
		{
			auto type = Object->gettype();
			if (type == Type_Ship || type == Type_Missile|| type == Type_BossFox || type == Type_FoxMissille || type == Type_Carrotboss || type == Type_CarroteMissile || type == Type_LuminuxBoss || type == Type_LuminuxMissile)
				continue;
			else 
				Object->TakeDomage(1000, 0);

		}
	}
		if (m_bossevent && !bossalive)
		{
			auto bossrand = m_rand.getrandomnumber(0, 2);
			switch (bossrand)
			{
			case 0:
				new BossFoxTentacle(*this, m_player->getcircle());
				m_bossevent = false;
				bossalive = true;
				break;
			case 1:
				new BossLuminux(*this, m_player->getcircle());
				m_bossevent = false;
				bossalive = true;
				break;
			case 2:
				new BossCarrot(*this, m_player->getcircle());
				bossalive = true;
				m_bossevent = false;
				break;
			default:
				break;
			}


		}
		if (m_bossevent && bossalive)
		{
			auto coutboss = 0;

			for (auto Object : m_allGameObject)
			{
				auto type = Object->gettype();
				if (type == Type_BossFox || type == Type_Carrotboss  || type == Type_LuminuxBoss )
				{
					++coutboss;
				}

			}
			if (coutboss == 0)
			{
				bossalive = false;
			}
		}
	

}

void Game::spawnObject()
{
	if (!m_bossevent)
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
		if (m_spawnrime.asSeconds() >= 0.5)
		{
			if (m_rand.getrandomnumber(0, 5) == 1)
				new Asteroid(*this);
			if (m_rand.getrandomnumber(6, 7) == 6)
				new Commette(*this);
			if (m_rand.getrandomnumber(1, 30) == 1)
			{
				m_bossevent = true;
			}
			m_spawn.restart();
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






 
