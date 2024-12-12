#pragma once
#include "IGameObject.h"

class Ship : public IGameObject
{
public:
    void input(sf::Event event) override;
    void update(float deltatime)override;
    void render() override;
};
class EnemieShip : public IGameObject
{
public:
    void input(sf::Event event) override;
    void update(float deltatime)override;
    void render() override;
};
