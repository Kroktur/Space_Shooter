#pragma once
#include <iostream>
#include <random>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <ctime>
class Randomnumber
{
public:
   
    int getrandomnumber(int min, int max);



};

class IGameObject
{
public:
    virtual void HandleInput() = 0;
    virtual void Update() = 0;
    virtual void Fire() = 0;
    virtual void Render(sf::RenderWindow& window) = 0;
    virtual sf::CircleShape& getShape() = 0;
    virtual ~IGameObject() = default;
   
protected:
    Randomnumber* rand;
};
