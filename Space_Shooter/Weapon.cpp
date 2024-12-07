#include "Weapon.h"
#include "Game.h"




Missile::Missile(sf::CircleShape& circle, Game& game) : m_missile(25)
{
	m_missile.setOrigin(m_missile.getRadius(), m_missile.getRadius());
	m_missile.setPosition(circle.getPosition());

	
	sf::Vector2i mousePos = sf::Mouse::getPosition(game.getWindow());
	sf::Vector2f target(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
	sf::Vector2f direction = target - circle.getPosition();
	float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	m_velocity = (direction / magnitude) * 20.f;
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
