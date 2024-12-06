#pragma once

#include <SFML/Graphics.hpp>
class IGameObject
{
public:
    virtual void HandleInput() = 0;
    virtual void Update() = 0;
    virtual void Render(sf::RenderWindow& window) = 0;
    virtual ~IGameObject() = default;
private:

};
