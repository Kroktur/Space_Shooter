#pragma once
#include "IGameObject.h"
#include "Game.h"
#include "Input.h"
#include<vector>
class Ship : public IGameObject
{
public:
    
    Ship(Game& game);
    void setShip();
    void input(sf::Event event) override;
    void update(float deltatime)override;
    void render() override;
  
    void resetmooveposition();
    
private:
   
    Game& m_game; 
    sf::CircleShape m_ship;
    sf::Vector2f m_position;
    float m_angle;
  
    
};
class EnemieShip : public IGameObject
{
public:
    void input(sf::Event event) override;
    void update(float deltatime)override;
    void render() override;
};
