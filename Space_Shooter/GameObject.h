#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include"IGameObject.h"
class Game;

class Ship : public IGameObject
{
public:
    Ship(Game& game);
   void HandleInput() override;
   void Update() override;
   void Render(sf::RenderWindow& window) override;
   float anglecalcul();
private:
    sf::CircleShape m_ship;
    sf::Vector2f m_positionrate;
    sf::RenderWindow m_window;
    float m_angle;

};