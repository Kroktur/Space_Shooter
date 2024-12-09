#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

enum mykeypressed
{
	Right,
	Left,
	Up,
	Down
};
class CircleShape
{
private:
	sf::RenderWindow& m_window;
	sf::CircleShape m_circle{ (50) };
	sf::Texture m_texture;
public:
	CircleShape(sf::RenderWindow& window) : m_window(window) { set(); }
	void deplacement(float deltaTime, int key)
	{
		float moveSpeed = 300.f;
		switch (key)
		{
		case Right:
			m_circle.move(sf::Vector2f(moveSpeed * deltaTime, 0.f));
			break;
		case Left:
			m_circle.move(sf::Vector2f(-moveSpeed * deltaTime, 0.f));
			break;
		case Up:
			m_circle.move(sf::Vector2f(0.f, -moveSpeed * deltaTime));
			break;
		case Down:
			m_circle.move(sf::Vector2f(0.f, moveSpeed * deltaTime));
			break;
		default:
			break;
		}
	}
	void deplacement(int key)
	{

		switch (key)
		{
		case Right:
			m_circle.move(sf::Vector2f(10.f, 0.f));
			break;
		case Left:
			m_circle.move(sf::Vector2f(-10.f, 0.f));
			break;
		case Up:
			m_circle.move(sf::Vector2f(0.f, -10.f));
			break;
		case Down:
			m_circle.move(sf::Vector2f(0.f, 10.f));
			break;
		default:
			break;
		}
	}
	void updatePosition(const sf::Time& deltaTime, const sf::Keyboard::Key& key) {

		if (sf::Keyboard::isKeyPressed(key)) {
			if (key == sf::Keyboard::D) deplacement(deltaTime.asSeconds(), Right);
			if (key == sf::Keyboard::Q) deplacement(deltaTime.asSeconds(), Left);
			if (key == sf::Keyboard::Z) deplacement(deltaTime.asSeconds(), Up);
			if (key == sf::Keyboard::S) deplacement(deltaTime.asSeconds(), Down);
		}
	}

	void rotation(float angle)
	{
		m_circle.setRotation(angle);
	}
	void set()
	{

		m_texture.loadFromFile("resource\\space_cat_.png");
		m_circle.setPosition(960, 540);
		m_circle.setTexture(&m_texture);
		m_circle.setOrigin(m_circle.getRadius(), m_circle.getRadius());
		/*m_circle.setOutlineColor(sf::Color::Red);
		m_circle.setOutlineThickness(5);*/
	}
	sf::CircleShape returnmyShape()
	{

		return m_circle;
	}



};
class Missile
{
protected:
	sf::RenderWindow& m_window;
	sf::CircleShape m_circle;
	sf::RectangleShape m_rectangle{ sf::Vector2f(60.f,30.f) };
	sf::Texture m_texture;
	float m_angle;
public:
	Missile(sf::RenderWindow& window, sf::CircleShape circle) :m_window(window), m_circle(circle) { set(); }
	void set()
	{


		m_texture.loadFromFile("resource\\space_cat_paw.png");
		m_rectangle.setPosition(m_circle.getPosition().x, m_circle.getPosition().y);
		m_rectangle.setTexture(&m_texture);
		m_rectangle.setOrigin(m_rectangle.getSize().x / 2 - m_circle.getRadius(), m_rectangle.getSize().x / 2);
		m_rectangle.setOutlineColor(sf::Color::Red);
		m_rectangle.setOutlineThickness(1);
	}
	void LunchMissile(float angle)
	{
		m_angle = angle;
		m_rectangle.setRotation(angle);
	}
	void setposition(const sf::Time& deltaTime)
	{
		/*float moveSpeed = 1.f;
		float angleradius = m_angle * (3.141592 / 180);
		float tangente = std::tan(angleradius);
		m_rectangle.move(sf::Vector2f(moveSpeed, tangente * moveSpeed));*/
	}
	sf::RectangleShape returnmyShape()
	{
		return m_rectangle;
	}


};
class Projectile {
private:
	sf::RenderWindow& m_window;
	sf::CircleShape m_shape{25};
	sf::Vector2f m_velocity;
	sf::Texture m_texturepaw;
	sf::CircleShape m_heroShip;
public : 
	Projectile(sf::RenderWindow& window ,sf::CircleShape circle) :m_window(window), m_heroShip(circle) { set(); }
	void set()
	{
		/*m_texturepaw.loadFromFile("C:\\Users\\ablanchet\\source\\repos\\Space_Shootertest1\\Space_Shooter\\resource\\space_cat_paw.png");
		m_shape.setTexture(&m_texturepaw);*/
		m_shape.setOrigin(m_shape.getRadius(), m_shape.getRadius());
		m_shape.setPosition(m_heroShip.getPosition());
		auto angle = m_heroShip.getRotation();
		m_shape.setRotation(angle);

	}
	void setvelocity(sf::Vector2f velocity)
	{
		m_velocity = velocity;
	}
	 sf::Vector2f getvelocity()
	{
		return m_velocity;
	}
	 void move(sf::Vector2f velocity, float deltatime)
	 {
		 m_shape.move(velocity * deltatime);
	 }
	sf::CircleShape returnmyShape()
	{

		return m_shape;
	}
	sf::CircleShape drawmyShape()
	{
		m_texturepaw.loadFromFile("resource\\space_cat_paw.png");
		m_shape.setTexture(&m_texturepaw);
		return m_shape;
	}
};
