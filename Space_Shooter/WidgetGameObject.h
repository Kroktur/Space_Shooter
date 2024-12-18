#pragma once
#include "IGameObject.h"
#include "Game.h"
#include <string>
#include<vector>
class Widget : public IGameObject
{
public:
    Widget(Game& game);
    virtual void setFont(std::string font) = 0;
    virtual void setText(std::string text ,int size, sf::Color color) = 0;

    virtual void input(sf::Event event) = 0;
    virtual void update(float deltatime) = 0;
    virtual void render() = 0;
    virtual int& gettype() = 0;
    virtual AABB GetBoundingBox() = 0;
    virtual void TakeDomage(int num = 1, int score = 0) = 0;

protected:
    Game& m_game;
    sf::Text m_text;
};

class Rectangle : public Widget
{
public:
  Rectangle(Game& game, Vec2& position , Vec2& Size);
  void setrectangle();
  void setFont(std::string font) ;
  void setText(std::string text, int size, sf::Color color);
  void input(sf::Event event)override;
  void update(float deltatime) override;
  void render()override;
  int& gettype() override;
  AABB GetBoundingBox() override;
  void TakeDomage(int num = 1, int score = 0) override;
private:
    
    sf::RectangleShape m_rectangle;
    Vec2& m_size;
    Vec2& m_currentposition;
};






