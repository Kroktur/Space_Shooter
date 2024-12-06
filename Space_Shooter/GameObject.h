#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include"IGameObject.h"


class Ship : public IGameObject
{
public:
    Ship();
   void HandleInput() override;
   void Update() override;
   void Render(sf::RenderWindow& window) override;
private:
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    float m_angle;
    sf::Vector2f m_position;
};