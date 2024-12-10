#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include "ressourceCache.h"
class IGameObject;

class Game
{
public:
    Game(float framerate =60);
    ~Game(); 
    void run();
    void init();
    sf::Vector2u getWindowSize();
    TextureCache& gettexture();
    sf::RenderWindow& getWindow();
    void HandleInput();
    void Update();
    void Render();
private:
    sf::RenderWindow m_window;
    std::vector<IGameObject*> m_allGameObject;
    sf::Event event;
    bool inWindow = false;
    TextureCache m_texture;
    sf::RectangleShape m_Background;
    sf::Clock clock;
    sf::Time elapsedTime;
    float framerate;
};
