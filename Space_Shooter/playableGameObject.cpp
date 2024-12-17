#include "playableGameObject.h"
#include "Input.h"
#include <cmath>


Ship::Ship(Game& game) :IGameObject(game), m_ship(50), m_angle(0), m_fire(false), m_firerate(0.25f), m_moove(0, 0)
{
	
	m_type = Type_Ship;
	m_vie = 3;
	setShip();
}

Ship::~Ship()
{
	delete m_input;
}

void Ship::setShip()
{
	//set texture
	m_ship.setTexture(&m_game.gettexture().getTexture("resource\\space_cat_.png"));
	//set Ship position and Origin
	m_ship.setOrigin(m_ship.getRadius(), m_ship.getRadius());
	m_ship.setPosition(m_game.getWindowSize().x / 2, m_game.getWindowSize().y / 2);
	//input
	m_input = new PlayerInput(*this);
}
void Ship::anglecalcul()
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(*m_game.getWindow());
	sf::Vector2f shipPos = m_ship.getPosition();
	float deltaX = mousePos.x - shipPos.x;
	float deltaY = mousePos.y - shipPos.y;
	float angle = std::atan2(deltaY, deltaX) * 180 / 3.14159f;
	m_angle = angle;
}

void Ship::input(sf::Event event)
{		
	resetmooveposition();
	m_input->processinput( event);
}

void Ship::update(float deltatime)
{
	anglecalcul();
	m_ship.setRotation(m_angle);
	m_ship.move(m_moove.x, m_moove.y);
	if (m_fire)
	{
		m_fire = false;
		new Missile(m_game, m_ship, Type_Missile);
	}
}

void Ship::render()
{
	m_game.getWindow()->draw(m_ship);
}

int& Ship::gettype()
{
	return m_type;
}



void Ship::resetmooveposition()
{
	m_moove.x = 0;
	m_moove.y = 0;
}

AABB Ship::GetBoundingBox()
{
	
	 Amin.x = m_ship.getPosition().x - m_ship.getRadius();
	 Amin.y = m_ship.getPosition().y - m_ship.getRadius();

	 Amax.x = m_ship.getPosition().x + m_ship.getRadius();
	 Amax.y = m_ship.getPosition().y + m_ship.getRadius();
	 AABB boundingbox(Amin, Amax);
	 return boundingbox;
}

sf::CircleShape& Ship::getcircle()
{
	return m_ship;
}

void Ship::TakeDomage(int num, int score)
{
	/*m_timetotakedomage = m_takedomage.getElapsedTime();
	if (m_timetotakedomage.asSeconds() > 0.05)
	{
		m_score += score;
		m_vie -= num;
		if (m_vie == 0)
		{
			m_game.addScore(m_score);
			m_game.toberemoved(this);
		}
	}
	m_takedomage.restart();*/
}

EnemieShip::EnemieShip(Game& game, sf::CircleShape& circle) :
	IGameObject(game)
, m_ennemie(50)
, m_ship(circle)
, m_angle(0)
, m_fire(false)
, m_firerate(1.f)
, m_moove(0, 0)
, m_delta(0, 0)

{
	m_type = Type_Ennemie_Ship;
	m_vie = 1;
	setennemie();
}

EnemieShip::~EnemieShip()
{
	delete m_input;
	delete m_randPosition;
}

void EnemieShip::setennemie()
{
	//set RandomSpawn
	m_randPosition = new RandomSpawn(Vec2{ -m_ennemie.getRadius(),-m_ennemie.getRadius() }, Vec2{static_cast<float>(m_game.getWindowSize().x + m_ennemie.getRadius()),static_cast<float>(m_game.getWindowSize().y + m_ennemie.getRadius())});
	//set EnemieShip position and Origin
	m_ennemie.setOrigin(m_ennemie.getRadius(), m_ennemie.getRadius());
	m_ennemie.setPosition(m_randPosition->m_spawnCordonate());
	//set texture
	m_ennemie.setTexture(&m_game.gettexture().getTexture("resource\\space_cat_enemie.png"));
	//input
	m_input = new IaInput(*this);

}
void EnemieShip::deltapositin()
{
	m_delta.x = m_ship.getPosition().x - m_ennemie.getPosition().x;
	m_delta.y = m_ship.getPosition().y - m_ennemie.getPosition().y;
}
void EnemieShip::anglecalcul()
{

	float angle = atan2(m_delta.y, m_delta.x);
	m_angle = angle * 180.0f / 3.1415926f;

}
AABB EnemieShip::GetBoundingBox()
{
	Amin.x = m_ennemie.getPosition().x - m_ennemie.getRadius();
	Amin.y = m_ennemie.getPosition().y - m_ennemie.getRadius();

	Amax.x = m_ennemie.getPosition().x + m_ennemie.getRadius();
	Amax.y = m_ennemie.getPosition().y + m_ennemie.getRadius();

	AABB boundingbox(Amin, Amax);
	return boundingbox;
}
void EnemieShip::TakeDomage(int num, int score)
{
	m_timetotakedomage = m_takedomage.getElapsedTime();
	if (m_timetotakedomage.asSeconds() > 0.05)
	{
		m_score += score;
		m_vie -= num;
		if (m_vie == 0)
		{
			m_game.addScore(m_score);
			m_game.toberemoved(this);
		}
	}
	m_takedomage.restart();
}
void EnemieShip::resetmooveposition()
{
	m_moove.x = 0;
	m_moove.y = 0;
}


void EnemieShip::input(sf::Event event)
{
	resetmooveposition();
	m_input->processinput( event);
}

void EnemieShip::update(float deltatime)
{
	deltapositin();
	anglecalcul();
	m_ennemie.move(m_moove.x, m_moove.y);
	m_ennemie.setRotation(m_angle);
	if (m_fire)
	{
		m_fire = false;
		new Missile(m_game, m_ennemie, Type_Ennemie_Missile);
	}
	
}

void EnemieShip::render()
{
	m_game.getWindow()->draw(m_ennemie);
}

int& EnemieShip::gettype()
{
	return m_type;
}

Missile::Missile(Game& game, sf::CircleShape& circle ,const int& type):IGameObject(game), m_missile(sf::Vector2f(75,15)), m_velocity(12.5f) ,m_shape(circle)
{	
	m_type = type;
	m_vie = 1;
	set();
}

void Missile::set()
{
	//set texture
	if (m_type == Type_Missile)
		m_missile.setTexture(&m_game.gettexture().getTexture("resource\\space_cat_paw.png"));
	if (m_type == Type_Ennemie_Missile)
		m_missile.setTexture(&m_game.gettexture().getTexture("resource\\space_cat_enemie_paw.png"));
	//set Missile position and Origin
	m_missile.setOrigin(m_missile.getSize().x/2, m_missile.getSize().y / 2);
	m_missile.setPosition(m_shape.getPosition());
	//set angle
	m_angle = m_shape.getRotation();
	m_missile.setRotation(m_angle);
	// set move 
	float angle_rad = m_angle * (3.14159265f / 180.f);
	m_moove.x = m_velocity * std::cos(angle_rad);
	m_moove.y = m_velocity * std::sin(angle_rad);

}

void Missile::input(sf::Event event)
{
}

void Missile::update(float deltatime)
{
	m_missile.move(m_moove.x, m_moove.y);
}

void Missile::render()
{
	m_game.getWindow()->draw(m_missile);

}

int& Missile::gettype()
{
	return m_type;
}

AABB Missile::GetBoundingBox()
{
	Amin.x = m_missile.getPosition().x - m_missile.getSize().x/2;
	Amin.y = m_missile.getPosition().y - m_missile.getSize().y/2;

	Amax.x = m_missile.getPosition().x + m_missile.getSize().x/2;
	Amax.y = m_missile.getPosition().y + m_missile.getSize().y/2;

	AABB boundingbox(Amin, Amax );
	return boundingbox;
}

void Missile::TakeDomage(int num, int score)
{
	m_timetotakedomage = m_takedomage.getElapsedTime();
	if (m_timetotakedomage.asSeconds() > 0.05)
	{
		m_score += score;
		m_vie -= num;
		if (m_vie == 0)
		{
			m_game.addScore(m_score);
			m_game.toberemoved(this);
		}
	}
	m_takedomage.restart();
}

Barrier::Barrier(Game& game, Vec2& Centre, float distance, int Size_,int Position, int forwhat) :IGameObject(game), m_Centre(Centre), m_Distance(distance) , m_position(Position), m_Size(Size_)
{
	m_type = Type_Barrier;
	if (forwhat == Type_Barrier_Only_Misssile)
		m_type = Type_Barrier_Only_Misssile;
	
	initBarrer();
}

void Barrier::initBarrer()
{
	if (m_position == Position_Left)
	{
		m_Barrier.setSize(sf::Vector2f(10, m_Size));
		m_Barrier.setOrigin(sf::Vector2f(m_Barrier.getSize().x/2, m_Barrier.getSize().y/2));
		m_Barrier.setPosition(sf::Vector2f(m_Centre.x - m_Distance, m_Centre.y));
    }
	if (m_position == Position_Right)
	{
		m_Barrier.setSize(sf::Vector2f(10, m_Size));
		m_Barrier.setOrigin(sf::Vector2f(m_Barrier.getSize().x/2, m_Barrier.getSize().y / 2));
		m_Barrier.setPosition(sf::Vector2f(m_Centre.x + m_Distance, m_Centre.y));
	}
	if (m_position == Position_Top)
	{
		m_Barrier.setSize(sf::Vector2f(m_Size,10));
		m_Barrier.setOrigin(sf::Vector2f(m_Barrier.getSize().x / 2, m_Barrier.getSize().y / 2));
		m_Barrier.setPosition(sf::Vector2f(m_Centre.x, m_Centre.y -m_Distance ));
	}
	if (m_position == Position_Botom)
	{
		m_Barrier.setSize(sf::Vector2f(m_Size, 10));
		m_Barrier.setOrigin(sf::Vector2f(m_Barrier.getSize().x / 2, m_Barrier.getSize().y / 2));
		m_Barrier.setPosition(sf::Vector2f(m_Centre.x, m_Centre.y + m_Distance));
	}
}

void Barrier::input(sf::Event event)
{
}

void Barrier::update(float deltatime)
{
}

void Barrier::render()
{
	m_game.getWindow()->draw(m_Barrier);

}

int& Barrier::gettype()
{
	return m_type;
}

AABB Barrier::GetBoundingBox()
{
	Amin.x = m_Barrier.getPosition().x - m_Barrier.getSize().x /2;
	Amin.y = m_Barrier.getPosition().y - m_Barrier.getSize().y/2;

	Amax.x = m_Barrier.getPosition().x + m_Barrier.getSize().x/2;
	Amax.y = m_Barrier.getPosition().y + m_Barrier.getSize().y /2;

	AABB boundingbox(Amin, Amax);
	return boundingbox;
}

void Barrier::TakeDomage(int num, int score)
{

}

Asteroid::Asteroid(Game& game): IGameObject(game), m_angle(0), m_moove(0, 0)
{
	m_timetotakedomage = m_takedomage.getElapsedTime();
	m_type = Type_Asteroid;
	m_vie = 5;
	initAsteroid();
}

Asteroid::~Asteroid()
{
	delete m_randPosition;
}

void Asteroid::initAsteroid()
{
	//random Size 
	m_Asteroid.setRadius(m_rand->getrandomnumber(75, 200));
	//random speed
	m_velocity = m_rand->getrandomnumber(1, 5);
	//set RandomPosition
	m_randPosition = new RandomSpawn(Vec2{ -m_Asteroid.getRadius(),-m_Asteroid.getRadius() }, Vec2{ static_cast<float>(m_game.getWindowSize().x + m_Asteroid.getRadius()),static_cast<float>(m_game.getWindowSize().y + m_Asteroid.getRadius()) });
	//set Asteroid position and Origin
	m_Asteroid.setOrigin(m_Asteroid.getRadius(), m_Asteroid.getRadius());
	m_Asteroid.setPosition(m_randPosition->m_spawnCordonate());
	//set texture
	m_Asteroid.setTexture(&m_game.gettexture().getTexture("resource\\Asteroid.png"));
	// set angle
	m_angle = m_rand->getrandomnumber(0, 360);
	m_Asteroid.setRotation(m_angle);
	// set move 
	float angle_rad = m_angle * (3.14159265f / 180.f);
	m_moove.x = m_velocity * std::cos(angle_rad);
	m_moove.y = m_velocity * std::sin(angle_rad);
}

void Asteroid::input(sf::Event event)
{
}

void Asteroid::update(float deltatime)
{
	m_Asteroid.move(m_moove.x, m_moove.y);
}

void Asteroid::render()
{
	m_game.getWindow()->draw(m_Asteroid);
}

int& Asteroid::gettype()
{
	return m_type;
}

AABB Asteroid::GetBoundingBox()
{
	Amin.x = m_Asteroid.getPosition().x - m_Asteroid.getRadius();
	Amin.y = m_Asteroid.getPosition().y - m_Asteroid.getRadius();

	Amax.x = m_Asteroid.getPosition().x + m_Asteroid.getRadius();
	Amax.y = m_Asteroid.getPosition().y + m_Asteroid.getRadius();
	AABB boundingbox(Amin, Amax);
	return boundingbox;
}

void Asteroid::TakeDomage(int num, int score )
{

	m_timetotakedomage = m_takedomage.getElapsedTime();
	if(m_timetotakedomage.asSeconds() > 0.05 )
	{
		m_score += score;
		m_vie -= num;
		if (m_vie == 0)
		{
			m_game.addScore(m_score);
			m_game.toberemoved(this);
		}
	}
	m_takedomage.restart();
}
Commette::Commette(Game& game) : IGameObject(game), m_angle(0), m_moove(0, 0)
{
	m_timetotakedomage = m_takedomage.getElapsedTime();
	m_type = Type_Asteroid;
	m_vie = 5;
	initCommette();
}

Commette::~Commette()
{
	delete m_randPosition;
}

void Commette::initCommette()
{
	//random Size 
	m_Commette.setRadius(m_rand->getrandomnumber(25, 50));
	//random speed
	m_velocity = m_rand->getrandomnumber(5, 20);
	//set RandomPosition
	m_randPosition = new RandomSpawn(Vec2{ -m_Commette.getRadius(),-m_Commette.getRadius() }, Vec2{ static_cast<float>(m_game.getWindowSize().x + m_Commette.getRadius()),static_cast<float>(m_game.getWindowSize().y + m_Commette.getRadius()) });
	//set Asteroid position and Origin
	m_Commette.setOrigin(m_Commette.getRadius(), m_Commette.getRadius());
	m_Commette.setPosition(m_randPosition->m_spawnCordonate());
	//set texture
	m_Commette.setTexture(&m_game.gettexture().getTexture("resource\\Commette.png"));
	// set angle
	m_angle = m_rand->getrandomnumber(0, 360);
	m_Commette.setRotation(m_angle);
	// set move 
	float angle_rad = m_angle * (3.14159265f / 180.f);
	m_moove.x = m_velocity * std::cos(angle_rad);
	m_moove.y = m_velocity * std::sin(angle_rad);
}

void Commette::input(sf::Event event)
{
}

void Commette::update(float deltatime)
{
	m_Commette.move(m_moove.x, m_moove.y);
}

void Commette::render()
{
	m_game.getWindow()->draw(m_Commette);
}

int& Commette::gettype()
{
	return m_type;
}

AABB Commette::GetBoundingBox()
{
	Amin.x = m_Commette.getPosition().x - m_Commette.getRadius();
	Amin.y = m_Commette.getPosition().y - m_Commette.getRadius();

	Amax.x = m_Commette.getPosition().x + m_Commette.getRadius();
	Amax.y = m_Commette.getPosition().y + m_Commette.getRadius();
	AABB boundingbox(Amin, Amax);
	return boundingbox;
}

void Commette::TakeDomage(int num, int score)
{

	m_timetotakedomage = m_takedomage.getElapsedTime();
	if (m_timetotakedomage.asSeconds() > 0.05)
	{
		m_score += score;
		m_vie -= num;
		if (m_vie == 0)
		{
			m_game.addScore(m_score);
			m_game.toberemoved(this);
		}
	}
	m_takedomage.restart();
}
