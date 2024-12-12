#pragma once
#include "IGameObject.h"

class Widget : public IGameObject
{
public:

    virtual void setFont() = 0;
    virtual void setText() = 0;
    virtual void drawShape() = 0;

    virtual void input(sf::Event event) = 0;
    virtual void update(float deltatime) = 0;
    virtual void render() = 0;


private:
};

class Rectangle : public Widget
{
public:
    void setFont() override;

    void setText()override;

    void drawShape()override;

    void input(sf::Event event)override;

    void update(float deltatime) override;

    void render()override;

};