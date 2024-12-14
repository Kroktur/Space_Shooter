#include "playableGameObject.h"
#include "Input.h"

Ship::Ship(Game& game) :IGameObject(game), m_ship(50), m_angle(0), m_fire(false), m_firerate(0.25f), m_type(Type_Ship),m_position(0,0)
{
	
	setShip();
}

void Ship::setShip()
{
	//set texture
	m_ship.setTexture(&m_game.gettexture().getTexture("resource\\space_cat_.png"));
	//set Ship position and Origin
	m_ship.setOrigin(m_ship.getRadius(), m_ship.getRadius());
	m_ship.setPosition(m_game.getWindowSize().x / 2, m_game.getWindowSize().y / 2);
	//input
	m_input = new PlayerInput;
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
	m_input->processinput(*this, event);
}

void Ship::update(float deltatime)
{
	anglecalcul();
	m_ship.setRotation(m_angle);
	m_ship.move(m_position.x, m_position.y);
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
	m_position.x = 0;
	m_position.y = 0;
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

EnemieShip::EnemieShip(Game& game, sf::CircleShape& circle) :IGameObject(game), m_ennemie(50), m_ship(circle), m_angle(0), m_fire(false), m_firerate(1.f), m_type(Type_Ennemie_Ship), m_position(0, 0), m_delta(0, 0)
{
	setennemie();
}

void EnemieShip::setennemie()
{
	//set Ship position and Origin
	m_ennemie.setOrigin(m_ennemie.getRadius(), m_ennemie.getRadius());
	m_ennemie.setPosition(SetrandomPosition());
	//set texture
	m_ennemie.setTexture(&m_game.gettexture().getTexture("resource\\space_cat_enemie.png"));
	//input
	m_input = new IaInput;

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
void EnemieShip::resetmooveposition()
{
	m_position.x = 0;
	m_position.y = 0;
}
sf::Vector2f EnemieShip::SetrandomPosition()
{
	
	sf::Vector2f position;
	int min_x = m_ennemie.getRadius();
	int max_x = m_game.getWindowSize().x - m_ennemie.getRadius();
	int min_y = m_ennemie.getRadius();
	int max_y = m_game.getWindowSize().y - m_ennemie.getRadius();
	int min = 0;
	int max = 3;
	int random_border = m_rand->getrandomnumber(min, max);
	int rabdom_Window_x = m_rand->getrandomnumber(min_x, max_x);
	int rabdom_Window_y = m_rand->getrandomnumber(min_y, max_y);
	switch (random_border)
	{
	case 0:
		position.x = min_x;
		position.y = rabdom_Window_y;
		return position;
		break;
	case 1:
		position.x = rabdom_Window_x;
		position.y = min_y;
		return position;
		break;
	case 2:
		position.x = max_x;
		position.y = rabdom_Window_y;
		return position;
		break;
	case 3:
		position.x = rabdom_Window_x;
		position.y = max_y;
		return position;
		break;
	default:
		break;
	}
}

void EnemieShip::input(sf::Event event)
{
	resetmooveposition();
	m_input->processinput(*this, event);
}

void EnemieShip::update(float deltatime)
{
	deltapositin();
	anglecalcul();
	m_ennemie.move(m_position.x, m_position.y);
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

Missile::Missile(Game& game, sf::CircleShape& circle ,const int& type):IGameObject(game), m_missile(25), m_velocity(12.5f) ,m_shape(circle), m_type(type)
{	

	set();
}

void Missile::set()
{
	//set texture
	if (m_type == Type_Missile)
		m_missile.setTexture(&m_game.gettexture().getTexture("resource\\space_cat_paw.png"));
	if (m_type == Type_Ennemie_Missile)
		m_missile.setTexture(&m_game.gettexture().getTexture("resource\\space_cat_enemie_paw.png"));
	//set Ship position and Origin
	m_missile.setOrigin(m_missile.getRadius(), m_missile.getRadius());
	m_missile.setPosition(m_shape.getPosition());
	//set angle
	auto angle = m_shape.getRotation();
	m_missile.setRotation(angle);
	// set move 
	float angle_rad = angle * (3.14159265f / 180.f);
	m_position.x = m_velocity * std::cos(angle_rad);
	m_position.y = m_velocity * std::sin(angle_rad);

}

void Missile::input(sf::Event event)
{
}

void Missile::update(float deltatime)
{
	m_missile.move(m_position.x, m_position.y);
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
	Amin.x = m_missile.getPosition().x - m_missile.getRadius();
	Amin.y = m_missile.getPosition().y - m_missile.getRadius();

	Amax.x = m_missile.getPosition().x + m_missile.getRadius();
	Amax.y = m_missile.getPosition().y + m_missile.getRadius();

	AABB boundingbox(Amin, Amax );
	return boundingbox;
}

