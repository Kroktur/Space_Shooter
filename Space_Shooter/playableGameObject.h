#pragma once
#include "IGameObject.h"
#include "Game.h"

#include<vector>
class Iinput;
class PlayerInput;
class IaInput;
class Ship : public IGameObject
{
public:
    friend PlayerInput;
    Ship(Game& game);
    void setShip();
    void anglecalcul();
    void input(sf::Event event) override;
    void update(float deltatime)override;
    void render() override;
    int gettype() override;
    void resetmooveposition();
    sf::CircleShape& getcircle();
private:
    
 
    sf::CircleShape m_ship;
    sf::Vector2f m_position;
    float m_angle;
    const int m_type;

    Iinput* m_input;

    bool m_fire;
    const float m_firerate;
    sf::Clock m_clock;
    sf::Time m_elapsedTime;
};
class EnemieShip : public IGameObject
{
public:
    friend IaInput;
    EnemieShip(Game& game, sf::CircleShape& circle);
    void setennemie();
    sf::Vector2f SetrandomPosition();
    void input(sf::Event event) override;
    void update(float deltatime)override;
    void render() override;
    int gettype() override;
    void resetmooveposition();
    void deltapositin();
    void anglecalcul();
   
private:
    sf::Vector2f m_delta;
    sf::CircleShape m_ennemie;
    sf::CircleShape& m_ship;
    sf::Vector2f m_position;
    float m_angle;
    const int m_type;

     Iinput* m_input;

    bool m_fire;
    const float m_firerate;
    sf::Clock m_clock;
    sf::Time m_elapsedTime;
};

class Missile : public IGameObject
{
public:
    Missile(Game& game , sf::CircleShape& circle , const int& type );
    void set();
    void input(sf::Event event) override;
    void update(float deltatime)override;
    void render() override;
    int gettype() override;
    
private:
    sf::CircleShape m_missile;
    sf::Vector2f m_position;
    float m_velocity;
    sf::CircleShape& m_shape;
    const int m_type;
};



