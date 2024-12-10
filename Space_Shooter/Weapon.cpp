#include "Weapon.h"
#include "Game.h"




Missile::Missile(sf::CircleShape& circle, Game& game) : m_missile(100), velcity(50)
{
	m_missile.setOrigin(m_missile.getRadius(), m_missile.getRadius());
	m_missile.setPosition(circle.getPosition());

	
	sf::Vector2i mousePos = sf::Mouse::getPosition(game.getWindow());
	sf::Vector2f target(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
	sf::Vector2f direction = target - circle.getPosition();
	float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	m_velocity = (direction / magnitude) * velcity;
	auto angle = circle.getRotation();
	m_missile.setRotation(angle);
	m_missile.setTexture(&game.gettexture().getTexture("resource\\space_cat_paw.png"));
}

void Missile::Update()
{
	m_missile.move(m_velocity.x , m_velocity.y);
	
}

void Missile::Render(sf::RenderWindow& window)
{
	window.draw(m_missile);
}

sf::Vector2f Missile::getPosition()
{
	return m_missile.getPosition();
}

float Missile::getRadius()
{
	return m_missile.getRadius();
}


EnnemieMissile::EnnemieMissile(sf::CircleShape& circle, Game& game) : m_missile(100), velcity(50)
{
	m_missile.setOrigin(m_missile.getRadius(), m_missile.getRadius());
	m_missile.setPosition(circle.getPosition());
	auto angle = circle.getRotation();
	auto radiantangle = angle * (3.14159f / 180.f);

	
	
	sf::Vector2f direction(std::cos(radiantangle), std::sin(radiantangle));
	
	m_velocity = direction * velcity;
	
	m_missile.setRotation(angle);
	m_missile.setTexture(&game.gettexture().getTexture("resource\\space_cat_enemie_paw.png"));
}

void EnnemieMissile::Update()
{
	m_missile.move(m_velocity.x, m_velocity.y);

}

void EnnemieMissile::Render(sf::RenderWindow& window)
{
	window.draw(m_missile);
}

sf::Vector2f EnnemieMissile::getPosition()
{
	return m_missile.getPosition();
}

float EnnemieMissile::getRadius()
{
	return m_missile.getRadius();
}
