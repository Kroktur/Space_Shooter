#pragma once
#include <SFML/Graphics.hpp>

class Iinput 
{
public:
		virtual ~Iinput() = default;
		virtual void processinput(sf::CircleShape& circle, sf::Event& event) =0;
		virtual void processinput(sf::RectangleShape& rectangle, sf::Event& event) = 0;
};

class PlayerInput : public Iinput
{
public:	
	void processinput(sf::CircleShape& circle, sf::Event& event)override;
	void processinput(sf::RectangleShape& circle, sf::Event& event)override;
};

class IaInput : public Iinput
{
public:
	void processinput(sf::CircleShape& circle, sf::Event& event) override;
	void processinput(sf::RectangleShape& circle, sf::Event& event)override;
};