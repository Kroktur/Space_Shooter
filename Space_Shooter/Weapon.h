#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include"IGameObject.h"
#include"IWeapon.h"
#include "Weapon.h"
#include "Game.h"
class Missile : public IWeapon
{
public:
	Missile(sf::CircleShape& circle, Game& game);
	void Update() override;
	void Render(sf::RenderWindow& window) override;
	sf::Vector2f getPosition() override;
	float getRadius();
private:
	sf::CircleShape m_missile;
	sf::Vector2f m_velocity;
	float velcity;
};

class EnnemieMissile : public IWeapon
{
public:
	EnnemieMissile(sf::CircleShape& circle, Game& game);
	void Update() override;
	void Render(sf::RenderWindow& window) override;
	sf::Vector2f getPosition() override;
	float getRadius();
private:
	sf::CircleShape m_missile;
	sf::Vector2f m_velocity;
	float velcity;
};

