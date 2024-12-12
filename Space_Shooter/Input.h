#pragma once
#include <SFML/Graphics.hpp>

class Iinput 
{
public:
		Iinput(sf::Event event): m_event(&event){}
		virtual ~Iinput() = default;
		virtual void processinput() =0;
protected:
	sf::Event* m_event;
};


class PlayerInput : public Iinput
{
public:
	PlayerInput(sf::Event event) : Iinput(event){}

private:

};