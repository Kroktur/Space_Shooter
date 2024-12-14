#pragma once
#include <SFML/Graphics.hpp>
#include "playableGameObject.h"
#include "IGameObject.h"
class Iinput 
{
public:
		virtual ~Iinput() = default;
		virtual void processinput(IGameObject& object, sf::Event& event) =0;

	
};


class PlayerInput : public Iinput
{
public:	
	void processinput(IGameObject& object, sf::Event& event)override;
private:
	float m_velocity;
};

class IaInput : public Iinput
{
public:
	IaInput();
	void processinput(IGameObject& object, sf::Event& event) override;
private:
	int m_actioncout;
	float m_velocity;
	int  m_random_number;
};