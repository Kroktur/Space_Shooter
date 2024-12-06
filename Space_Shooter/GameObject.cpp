#include "GameObject.h"

Ship::Ship(): m_position(300,300) 
{

}

void Ship::HandleInput()
{

}

void Ship::Update()
{
	m_sprite.setRotation(m_angle);
}

void Ship::Render(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}
