#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
class IGameObject;

class Game
{
public:
    Game();
    ~Game(); 
    void run();
    void HandleInput();
    void Update();
    void Render();
private:
    sf::RenderWindow m_window;
    std::vector<IGameObject*> m_allGameObject;


};
