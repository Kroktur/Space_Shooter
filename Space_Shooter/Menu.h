#pragma once
#include <SFML/Graphics.hpp>
#include "SceneBase.h"
#include "IGameObject.h"
#include "MyMath.h"
class Rectanglewidgetupdatable;
class Rectanglewidget;
class Menu : public SceneBase
{
public:

    Menu(sf::RenderWindow* window, const float& framerate);
    ~Menu();
    void init();
    void processInput(sf::Event& event);
    
    void update(const float& deltaTime);
    
    void render();
    

private:
    
    Rectanglewidgetupdatable* tmps;
};

