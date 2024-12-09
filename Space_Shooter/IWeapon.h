#pragma once

#include <SFML/Graphics.hpp>
class IWeapon
{
public:

    virtual void Update() = 0;
    virtual void Render(sf::RenderWindow& window) = 0;
    virtual ~IWeapon() = default;
    virtual sf::Vector2f getPosition() = 0;
    virtual float getRadius() = 0;
private:

};
