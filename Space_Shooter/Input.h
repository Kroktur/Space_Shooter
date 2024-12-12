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
	
};

class IaInput : public Iinput
{
public:
	void processinput(IGameObject& object, sf::Event& event) override;
	
};