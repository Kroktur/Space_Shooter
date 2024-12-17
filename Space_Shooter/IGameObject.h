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
    , Type_Barrier =4
    , Type_Barrier_Only_Misssile = 5
    ,Type_Asteroid =6
    ,Type_Commette = 7
};
enum BarrierPosition
{
    Position_Left = 0
    , Position_Right = 1
    , Position_Top = 2
    , Position_Botom = 3
};
class IGameObject
{
public:
   
    virtual ~IGameObject();
    IGameObject(Game& game);
    virtual void input(sf::Event event) = 0;
    virtual void update(float deltatime) = 0;
    virtual void render() = 0;
    virtual int& gettype() =0;
    virtual AABB GetBoundingBox() = 0;
    virtual void TakeDomage(int num = 1, int score = 0) = 0;
protected:
    Game& m_game;
    Randomnumber* m_rand;
    RandomSpawn* m_randPosition;
    int m_score;
    int m_vie;
    Vec2 Amin;
    Vec2 Amax;
    int m_type;
    sf::Clock m_takedomage;
    sf::Time m_timetotakedomage;
};

