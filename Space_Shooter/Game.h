#pragma once
#include <SFML/Graphics.hpp>
#include "SceneBase.h"


class Game : public SceneBase
{
public:
   
    Game(sf::RenderWindow* window, const float& framereta);
    void processInput(const sf::Event& event);
    void update(const float& deltaTime);
    void render();
    void run();

    //window 
    sf::Vector2u getWindowSize();
    sf::RenderWindow* getWindow();
  
};