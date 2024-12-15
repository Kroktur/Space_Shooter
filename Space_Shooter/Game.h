#pragma once
#include <SFML/Graphics.hpp>
#include "SceneBase.h"
#include "IGameObject.h"
#include "MyMath.h"
class Game : public SceneBase
{
public:

    friend IGameObject;
    Game(sf::RenderWindow* window, const float& framereta);
    ~Game();
    void processInput(const sf::Event& event);
    void update(const float& deltaTime);
    void render();
    void init();
    void testColision(IGameObject* A, IGameObject* B);
    bool colision(AABB A, AABB B);
    //window 
    sf::Vector2u getWindowSize();
    sf::RenderWindow* getWindow();

private :

    std::vector<IGameObject*> m_allGameObject;
    std::vector<IGameObject*> m_goingtoaddGameObject;
    std::vector<IGameObject*> m_objectsToRemove;
};