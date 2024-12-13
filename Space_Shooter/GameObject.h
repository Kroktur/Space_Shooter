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
   sf::CircleShape& getShape();
   void boundingBoxS();
  
private:
    sf::CircleShape m_ship;
    sf::Vector2f m_position;
    Game& m_game;
    float firerate;
    float m_angle;
   
    std::vector<IWeapon*> m_allWeapon;
    sf::Clock clock;
    sf::Time elapsedTime;
     


    bool fire = false;
};


class Ennemie_Ship : public IGameObject
{
public:
    Ennemie_Ship(Game& game, sf::CircleShape& shape);
    ~Ennemie_Ship();
    void HandleInput() override;
    void Update() override;
    void Fire();
    void Render(sf::RenderWindow& window) override;
    void anglecalcul();
    void deltacalcul();
    sf::Vector2f SetPosition();
    void Getcloserfromship();
    void SetMagnetude();
    sf::CircleShape& getShape();
    void boundingBoxE();


private:
    sf::CircleShape& m_ship;
    sf::CircleShape m_enemie;
    sf::Vector2f m_position;
    Game& m_game;
    float m_angle;
    float m_magnetude;
    std::vector<IWeapon*> m_allWeapon;
    sf::Vector2f delta;
    float velocity;
    float firerate;
    sf::Clock clock;
    sf::Time elapsedTime;
    int random_number = 0;
    int actioncout = 0;
};