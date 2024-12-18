#include "WidgetGameObject.h"

// a elenver
#include <iostream>
Widget::Widget(Game& game) : IGameObject(game), m_game(game)
{
}

Rectangle::Rectangle(Game& game, Vec2& position, Vec2& Size) :Widget(game), m_currentposition(position), m_size(Size)
{
	m_type = Type_RectangleWidget;
	setrectangle();
}

void Rectangle::setrectangle()
{ 
	// setSize Origin and Position of widget
	m_rectangle.setSize(sf::Vector2f(m_size.x, m_size.y));
	m_rectangle.setOrigin(sf::Vector2f(m_rectangle.getSize().x / 2, m_rectangle.getSize().y / 2));
	m_rectangle.setPosition(sf::Vector2f(m_currentposition.x, m_currentposition.y));
	// set position text


	//m_text.setOrigin(m_rectangle.getOrigin());
	m_text.setPosition(0,0);
	m_text.setString("Hello World");
	m_text.setFillColor(sf::Color::White);
	m_text.setCharacterSize(50);
}

void Rectangle::setFont(std::string font)
{
	m_text.setFont(m_game.getfont().getFont(font));
}

void Rectangle::setText(std::string text, int size, sf::Color color)
{

	m_text.setString(text);

	// choix de la taille des caractères
	m_text.setCharacterSize(size); // exprimée en pixels, pas en points !

	// choix de la couleur du texte
	m_text.setFillColor(color);
}



void Rectangle::input(sf::Event event)
{
}

void Rectangle::update(float deltatime)
{
}

void Rectangle::render()
{
	m_game.getWindow()->draw(m_text);
}

int& Rectangle::gettype()
{
	return m_type;
}

AABB Rectangle::GetBoundingBox()
{
	Amin.x = m_rectangle.getPosition().x - m_rectangle.getSize().x / 2;
	Amin.y = m_rectangle.getPosition().y - m_rectangle.getSize().y / 2;

	Amax.x = m_rectangle.getPosition().x + m_rectangle.getSize().x / 2;
	Amax.y = m_rectangle.getPosition().y + m_rectangle.getSize().y / 2;

	AABB boundingbox(Amin, Amax);
	return boundingbox;
}

void Rectangle::TakeDomage(int num, int score)
{
}

