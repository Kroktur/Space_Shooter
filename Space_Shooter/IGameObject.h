#pragma once
#include <SFML/Graphics.hpp>
#include "MyMath.h"
class Game;

enum  GameOvject
{
    Type_Ship = 0
    ,Type_Ennemie_Ship = 1
    , Type_Missile = 2
    , Type_Ennemie_Missile = 3

};
class IGameObject
{
public:
   
    virtual ~IGameObject() = default;
    IGameObject(Game& game);
    virtual void input(sf::Event event) = 0;
    virtual void update(float deltatime) = 0;
    virtual void render() = 0;
    virtual int& gettype() =0;
    virtual AABB GetBoundingBox() = 0;

protected:
    Game& m_game;
    Randomnumber* m_rand;
   
};

