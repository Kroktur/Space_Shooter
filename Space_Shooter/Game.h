#pragma once
#include <SFML/Graphics.hpp>
#include "SceneBase.h"
#include "IGameObject.h"
#include "MyMath.h"
class Rectanglewidgetupdatable;
class Rectanglewidget;
class GameInput;
class Ship;
class Barrier;
class Iinput;
class Game : public SceneBase
{
public:
    friend GameInput;
    
    Game(sf::RenderWindow* window, const float& framereta);
    ~Game();
    void processInput( sf::Event& event);
    void objectinput(sf::Event& event);
    void update(const float& deltaTime);
    void render();
    void init();
    void testColision(IGameObject* A, IGameObject* B);
    bool colision(AABB A, AABB B);
    //window 
   
    void spawnObject();
   
    void renderAABB();
    
private :

    sf::RectangleShape m_Background;
 
    Ship* m_player;
    bool m_showAABB = false;
    Iinput* m_input;
    float m_Borderlimit;
    Randomnumber m_rand;
    sf::Clock m_spawn;
    sf::Time m_spawnrime;
    int m_scorebase;
    Rectanglewidgetupdatable* tmps;
};