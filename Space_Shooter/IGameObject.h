#pragma once
#include <SFML/Graphics.hpp>

class IGameObject
{
public:
    virtual ~IGameObject() = default;

    virtual void input(sf::Event event) = 0;
    virtual void update(float deltatime) = 0;
    virtual void render() = 0;
    

private:

};