#pragma once
#include "IGameObject.h"
#include "Game.h"

#include<vector>
class Iinput;
class PlayerInput;
class IaInput;
class IaBossFoxInput;

class lunchroudmissile
{
public:
    void lunch(int numofmissille, SceneBase& game, sf::CircleShape& circle, int type);
};

class Ship : public IGameObject
{
public:
    friend PlayerInput;
    Ship(SceneBase& game);
    ~Ship();
    void setShip();
    void anglecalcul();
    void input(sf::Event event) override;
    void update(float deltatime)override;
    void render() override;
    int& gettype() override;
    void resetmooveposition();
    AABB GetBoundingBox() override;
   
    sf::CircleShape& getcircle();
    void TakeDomage(int num = 1, int score =0);
private:
    
    

    sf::CircleShape m_ship;
    sf::Vector2f m_moove;
    float m_angle;
    

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
    EnemieShip(SceneBase& game, sf::CircleShape& circle);
    ~EnemieShip();
    void setennemie();
    void input(sf::Event event) override;
    void update(float deltatime)override;
    void render() override;
    int& gettype() override;
    void resetmooveposition();
    void deltapositin();
    void anglecalcul();
    AABB GetBoundingBox() override;
    void TakeDomage(int num = 1, int score =0);
private:

   
 
    sf::Vector2f m_delta;
    sf::CircleShape m_ennemie;
    sf::CircleShape& m_ship;
    sf::Vector2f m_moove;
    float m_angle;
     Iinput* m_input;

    bool m_fire;
    const float m_firerate;
    sf::Clock m_clock;
    sf::Time m_elapsedTime;
};

class Missile : public IGameObject
{
public:
    Missile(SceneBase& game , sf::CircleShape& circle , const int& type );
    void set();
    void input(sf::Event event) override;
    void update(float deltatime)override;
    void render() override;
    int& gettype() override;
    AABB GetBoundingBox() override;
    void TakeDomage(int num = 1, int score = 0);
private:

  

   
    float m_angle;
    sf::RectangleShape m_missile;
    sf::Vector2f m_moove;
    float m_velocity;
    sf::CircleShape& m_shape;
     
};
class Barrier : public IGameObject
{
public:
    Barrier(SceneBase& game, Vec2& Centre, float distance, int Size_, int Position ,int forwhat = 0);
    void initBarrer();
    void input(sf::Event event);
    void update(float deltatime);
    void render();
    int& gettype();
    AABB GetBoundingBox();
    void TakeDomage(int num = 1, int score = 0);

private:
    Vec2 Amin;
    Vec2 Amax;
    Vec2& m_Centre;
    float& m_Distance;
    int& m_position; 
    int& m_Size;
    sf::RectangleShape m_Barrier;

};
class Asteroid : public IGameObject
{
public:
    Asteroid(SceneBase& game);
    ~Asteroid();
    void initAsteroid();
    void input(sf::Event event) ;
     void update(float deltatime);
     void render() ;
     int& gettype() ;
     AABB GetBoundingBox();
     void TakeDomage(int num = 1, int score = 0) ;
private:

  
    float m_velocity;
   
    float m_angle;
    
    sf::CircleShape m_Asteroid;
    sf::Vector2f m_moove;
};
class Commette : public IGameObject
{
public:
    Commette(SceneBase& game);
    ~Commette();
    void initCommette();
    void input(sf::Event event);
    void update(float deltatime);
    void render();
    int& gettype();
    AABB GetBoundingBox();
    void TakeDomage(int num = 1, int score = 0);
private:


    float m_velocity;

    float m_angle;

    sf::CircleShape m_Commette;
    sf::Vector2f m_moove;
};
class Lives : public IGameObject
{
public:

  
    Lives(SceneBase& game, Vec2 position, Vec2 Size);
    ~Lives();

    void initlives();
    void input(sf::Event event);
    void update(float deltatime);
    void render();
    int& gettype();
    AABB GetBoundingBox();
    void TakeDomage(int num = 1, int score = 0);
protected:
    sf::RectangleShape m_lives;
    Vec2& m_position;
    Vec2& m_Size;
};
class BossTentacle : public IGameObject
{
public:
    friend IaBossFoxInput;
    BossTentacle(SceneBase& game, sf::CircleShape& circle);
    ~BossTentacle();
    void setennemie();
    void input(sf::Event event) override;
    void update(float deltatime)override;
    void render() override;
    int& gettype() override;
    void resetmooveposition();
    void deltapositin();
    AABB GetBoundingBox() override;
    void TakeDomage(int num = 1, int score = 0);
  

private:



    sf::Vector2f m_delta;
    sf::CircleShape m_bossfox;
    sf::Vector2f m_moove;
    float m_angle;
    Iinput* m_input;
    sf::CircleShape& m_ship;
    bool m_fire;
    const float m_firerate;
    sf::Clock m_clock;
    sf::Time m_elapsedTime;
};
class FoxMissille : public IGameObject
{
public:
    FoxMissille(SceneBase& game, sf::CircleShape& circle, float angmle);
    void set();
    void input(sf::Event event) override;
    void update(float deltatime)override;
    void render() override;
    int& gettype() override;
    AABB GetBoundingBox() override;
    void TakeDomage(int num = 1, int score = 0);
private:




    float& m_angle;
    sf::RectangleShape m_fishmissile;
    sf::Vector2f m_moove;
    float m_velocity;
    sf::CircleShape& m_shape;

};