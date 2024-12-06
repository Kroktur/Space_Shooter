#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include"IGameObject.h"
#include "IWeapon.h"
#include "Weapon.h"
class Game;

class Ship : public IGameObject
{
public:
    Ship(Game& game);
    ~Ship();
   void HandleInput() override;
   void Update() override;
    void Fire() ;
   void Render(sf::RenderWindow& window) override;
   float anglecalcul();
  
private:
    sf::CircleShape m_ship;
    sf::Vector2f m_positionrate;
    Game& m_game;
    float m_angle;
    std::vector<IWeapon*> m_allWeapon;
};