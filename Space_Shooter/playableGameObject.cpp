#include "playableGameObject.h"
#include "Input.h"
#include <cmath>


Ship::Ship(SceneBase& game) :IGameObject(game), m_ship(50), m_angle(0), m_fire(false), m_firerate(0.25f), m_moove(0, 0)
{
	
	m_type = Type_Ship;
	m_vie = 10;
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
	if (m_vie <= 0)
	{
		m_game.addScore(m_score);
		m_game.toberemoved(this);
	}
	auto countlive = m_vie;
	Vec2 position = { 0 + 50,static_cast<float>(m_game.getWindowSize().y) - 50 };
	Vec2 Size = { 50, 50 };
	while (countlive > 0)
	{
		new Lives(m_game, position, Size);
		position.x += 70;

		--countlive;
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
	m_timetotakedomage = m_takedomage.getElapsedTime();
	if (m_timetotakedomage.asSeconds() > 0.05)
	{
		m_score += score;
		m_vie -= num;
		
	}
	m_takedomage.restart();

}

EnemieShip::EnemieShip(SceneBase& game, sf::CircleShape& circle) :
	IGameObject(game)
, m_ennemie(50)
, m_ship(circle)
, m_angle(0)
, m_fire(false)
, m_firerate(2.5f)
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
	m_randPosition = new RandomSpawn(Vec2{ -m_ennemie.getRadius(),-m_ennemie.getRadius() },
		Vec2{static_cast<float>(m_game.getWindowSize().x + m_ennemie.getRadius()),static_cast<float>(m_game.getWindowSize().y + m_ennemie.getRadius())});
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
	if (m_vie <= 0)
	{
		m_game.addScore(m_score);
		m_game.toberemoved(this);
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

Missile::Missile(SceneBase& game, sf::CircleShape& circle ,const int& type):
	IGameObject(game)
	, m_missile(sf::Vector2f(75,15))
	,m_shape(circle)
{	
	m_type = type;
	m_vie = 1;
	set();
}

void Missile::set()
{
	//set texture
	if (m_type == Type_Missile)
	{
		m_missile.setTexture(&m_game.gettexture().getTexture("resource\\space_cat_paw.png"));
		m_velocity = 25.f;
	}
	if (m_type == Type_Ennemie_Missile)
	{
		m_missile.setTexture(&m_game.gettexture().getTexture("resource\\space_cat_enemie_paw.png"));
		m_velocity = 12.5f;
	}
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
	if (m_vie <= 0)
	{
		m_game.addScore(m_score);
		m_game.toberemoved(this);
	}
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
		
	}
	m_takedomage.restart();
}

Barrier::Barrier(SceneBase& game, Vec2& Centre, float distance, int Size_,int Position, int forwhat) :IGameObject(game), m_Centre(Centre), m_Distance(distance) , m_position(Position), m_Size(Size_)
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

Asteroid::Asteroid(SceneBase& game): IGameObject(game), m_angle(0), m_moove(0, 0)
{

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
	if (m_vie <= 0)
	{
		m_game.addScore(m_score);
		m_game.toberemoved(this);
	}
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
		
	}
	m_takedomage.restart();
}
Commette::Commette(SceneBase& game) : IGameObject(game), m_angle(0), m_moove(0, 0)
{
	m_timetotakedomage = m_takedomage.getElapsedTime();
	m_type = Type_Commette;
	m_vie = 1;
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
	m_velocity = m_rand->getrandomnumber(5, 15);
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
	if (m_vie <= 0)
	{
		m_game.addScore(m_score);
		m_game.toberemoved(this);
	}
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
		
	}
	m_takedomage.restart();
}

Lives::Lives(SceneBase& game, Vec2 position, Vec2 Size) : IGameObject(game), m_position(position), m_Size(Size)
{
	m_type = Type_Live;
	m_vie = 1;
	initlives();
}

Lives::~Lives()
{
}

void Lives::initlives()
{
	//set size
	m_lives.setSize(sf::Vector2f(m_Size.x, m_Size.y));
	// set Position and origin
	m_lives.setOrigin(m_lives.getSize().x / 2, m_lives.getSize().y / 2);
	m_lives.setPosition(sf::Vector2f(m_position.x, m_position.y));
	//set texture
	m_lives.setTexture(&m_game.gettexture().getTexture("resource\\heart.png"));
}

void Lives::input(sf::Event event)
{
}

void Lives::update(float deltatime)
{
	if (m_vie <=  0)
	{
		m_game.addScore(m_score);
		m_game.toberemoved(this);
	}
}

void Lives::render()
{
	m_game.getWindow()->draw(m_lives);
}

int& Lives::gettype()
{
	return m_type;
}

AABB Lives::GetBoundingBox()
{
	Amin.x = m_lives.getPosition().x - m_lives.getSize().x / 2;
	Amin.y = m_lives.getPosition().y - m_lives.getSize().y / 2;

	Amax.x = m_lives.getPosition().x + m_lives.getSize().x / 2;
	Amax.y = m_lives.getPosition().y + m_lives.getSize().y / 2;

	AABB boundingbox(Amin, Amax);
	return boundingbox;
}

void Lives::TakeDomage(int num, int score)
{

	
		m_vie -= num;
		if (m_vie < 0)
			m_vie = 0;
	
}
BossTentacle::BossTentacle(SceneBase& game, sf::CircleShape& circle ):
	IGameObject(game)
	, m_bossfox(300)
	,m_ship(circle)
	, m_angle(0)
	, m_fire(false)
	, m_firerate(0.5f)
	, m_moove(0, 0)
	, m_delta(0, 0)

{
	m_type = Type_BossFox;
	m_vie = 90;
	setennemie();
}

BossTentacle::~BossTentacle()
{
	delete m_input;
	delete m_randPosition;
}

void BossTentacle::setennemie()
{
	//set RandomSpawn
	m_randPosition = new RandomSpawn(Vec2{ -m_bossfox.getRadius(),-m_bossfox.getRadius() },
		Vec2{ static_cast<float>(m_game.getWindowSize().x + m_bossfox.getRadius()),static_cast<float>(m_game.getWindowSize().y + m_bossfox.getRadius()) });
	//set EnemieShip position and Origin
	m_bossfox.setOrigin(m_bossfox.getRadius(), m_bossfox.getRadius());
	m_bossfox.setPosition(m_randPosition->m_spawnCordonate());
	
	//set texture
	m_bossfox.setTexture(&m_game.gettexture().getTexture("resource\\Foxopus.png"));
	//input
	m_input = new IaBossFoxInput(*this);

}
AABB BossTentacle::GetBoundingBox()
{
	Amin.x = m_bossfox.getPosition().x - m_bossfox.getRadius();
	Amin.y = m_bossfox.getPosition().y - m_bossfox.getRadius();

	Amax.x = m_bossfox.getPosition().x + m_bossfox.getRadius();
	Amax.y = m_bossfox.getPosition().y + m_bossfox.getRadius();

	AABB boundingbox(Amin, Amax);
	return boundingbox;
}
void BossTentacle::TakeDomage(int num, int score)
{
	m_timetotakedomage = m_takedomage.getElapsedTime();
	if (m_timetotakedomage.asSeconds() > 0.05)
	{
		m_score += score;
		m_vie -= num;

	}
	m_takedomage.restart();
}
void BossTentacle::resetmooveposition()
{
	m_moove.x = 0;
	m_moove.y = 0;
}
void BossTentacle::deltapositin()
{
	m_delta.x = m_ship.getPosition().x - m_bossfox.getPosition().x;
	m_delta.y = m_ship.getPosition().y - m_bossfox.getPosition().y;
}


void BossTentacle::input(sf::Event event)
{
	resetmooveposition();
	m_input->processinput(event);
}

void BossTentacle::update(float deltatime)
{
	deltapositin();
	m_bossfox.move(m_moove.x, m_moove.y);
	if (m_fire)
	{
		m_fire = false;
		lunchroudmissile lunch;
		lunch.lunch(m_rand->getrandomnumber(10,50), m_game, m_bossfox, Yype_FoxMissille);
	}
	if (m_vie <= 0)
	{
		m_game.addScore(m_score);
		m_game.toberemoved(this);
	}
}

void BossTentacle::render()
{
	m_game.getWindow()->draw(m_bossfox);


}

int& BossTentacle::gettype()
{
	return m_type;
}
FoxMissille::FoxMissille(SceneBase& game, sf::CircleShape& circle, float angle) :
	IGameObject(game)
	, m_fishmissile(sf::Vector2f(75, 15))
	, m_shape(circle)
	,m_angle(angle)
{
	m_type = Yype_FoxMissille;
	m_vie = 3;
	set();
}

void FoxMissille::set()
{
	//set texture
	
		m_fishmissile.setTexture(&m_game.gettexture().getTexture("resource\\space_fish.png"));
		m_velocity = 6;
	
	//set Missile position and Origin
	m_fishmissile.setOrigin(m_fishmissile.getSize().x / 2, m_fishmissile.getSize().y / 2);
	m_fishmissile.setPosition(m_shape.getPosition());
	//set angle
	 
	m_fishmissile.setRotation(m_angle);
	// set move 
	float angle_rad = m_angle * (3.14159265f / 180.f);
	m_moove.x = m_velocity * std::cos(angle_rad);
	m_moove.y = m_velocity * std::sin(angle_rad);

}

void FoxMissille::input(sf::Event event)
{
}

void FoxMissille::update(float deltatime)
{
	m_fishmissile.move(m_moove.x, m_moove.y);
	if (m_vie <= 0)
	{
		m_game.addScore(m_score);
		m_game.toberemoved(this);
	}
}

void FoxMissille::render()
{
	m_game.getWindow()->draw(m_fishmissile);

}

int& FoxMissille::gettype()
{
	return m_type;
}

AABB FoxMissille::GetBoundingBox()
{
	Amin.x = m_fishmissile.getPosition().x - m_fishmissile.getSize().x / 2;
	Amin.y = m_fishmissile.getPosition().y - m_fishmissile.getSize().y / 2;

	Amax.x = m_fishmissile.getPosition().x + m_fishmissile.getSize().x / 2;
	Amax.y = m_fishmissile.getPosition().y + m_fishmissile.getSize().y / 2;

	AABB boundingbox(Amin, Amax);
	return boundingbox;
}

void FoxMissille::TakeDomage(int num, int score)
{
	m_timetotakedomage = m_takedomage.getElapsedTime();
	if (m_timetotakedomage.asSeconds() > 0.05)
	{
		m_score += score;
		m_vie -= num;

	}
	m_takedomage.restart();
}

void lunchroudmissile::lunch(int numofmissille, SceneBase& game, sf::CircleShape& circle, int type )
{
	auto angle_of_missile = 360 / numofmissille;
	auto start_angle = 0;
	for (auto idx = 0; idx < numofmissille ; ++idx)
	{
		if(type == Yype_FoxMissille)
		new FoxMissille(game, circle, start_angle);
		start_angle += angle_of_missile;
	}
}
