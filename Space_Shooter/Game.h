#pragma once
#include <SFML/Graphics.hpp>
#include "SceneBase.h"
#include "IGameObject.h"
#include "MyMath.h"
class Ship;
class Game : public SceneBase
{
public:

    friend IGameObject;
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
    sf::Vector2u getWindowSize();
    sf::RenderWindow* getWindow();
    void spawnObject();
    void addObject();
    void toberemoved(IGameObject* it);
    void deleteObject();
    void renderAABB();
private :

    sf::RectangleShape m_Background;
    std::vector<IGameObject*> m_allGameObject;
    std::vector<IGameObject*> m_tobeaddGameObject;
    std::vector<IGameObject*> m_toberemovedGameObject;
    Ship* m_player;
    bool m_showAABB = false;
};