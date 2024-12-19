#pragma once
#include "IGameObject.h"
#include "Game.h"
#include <string>
#include<vector>
enum Widget_type
{
    Classic_Widget
};
class Widget : public IGameObject
{
public:
    Widget(Game& game);
    virtual void setFont(std::string font) = 0;
    virtual void setTexture(std::string texture) = 0;
    virtual void setText(std::string text) = 0;
    virtual void setcolor(sf::Color color) = 0;
    virtual void settextSize(int txtsize) = 0;
    virtual void setTextPosition(Vec2 position) = 0;
    virtual int& getwidgettype() = 0;

    virtual void input(sf::Event event) = 0;
    virtual void update(float deltatime) = 0;
    virtual void render() = 0;
    virtual int& gettype() = 0;
    virtual AABB GetBoundingBox() = 0;
    virtual void TakeDomage(int num = 1, int score = 0) = 0;

protected:
    int m_typewidget;
    Game& m_game;
    sf::Text m_text;
    std::string m_textcontain;
};

class Rectanglewidget : public Widget
{
public:
  Rectanglewidget(Game& game, Vec2& position , Vec2& Size ,std::string texte , int typewidget = Classic_Widget );
  void setrectangle();


  void setFont(std::string font) ;
  void setText(std::string text);
  void setTexture(std::string texture);
  void setcolor(sf::Color color) ;
  void settextSize(int txtsize);
  void setTextPosition(Vec2 position);


  int& getwidgettype() override;
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

class RectangleWidgetUpdatable : public Widget
{
public:
    RectangleWidgetUpdatable(Game& game, Vec2 position, Vec2 Size, std::string texte, int* value, int typewidget = Classic_Widget);
    void setrectangle();


    void setFont(std::string font);
    void setText(std::string text);
    void setTexture(std::string texture);
    void setcolor(sf::Color color);
    void settextSize(int txtsize);
    void setTextPosition(Vec2 position);


    int& getwidgettype() override;
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
    int* m_value;
};






