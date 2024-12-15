#pragma once
#include <SFML/Graphics.hpp>
#include "playableGameObject.h"
#include "IGameObject.h"
enum AI_move
{
	Move_Right
	,Move_Left
	,Move_Down
	,Move_Up
	,Move_Closer_Player
	,Shoot
	,Do_Nothing
};

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