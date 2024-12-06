#pragma once

#include <SFML/Graphics.hpp>
class IWeapon
{
public:

    virtual void Update() = 0;
    virtual void Render(sf::RenderWindow& window) = 0;
    virtual ~IWeapon() = default;
private:

};
