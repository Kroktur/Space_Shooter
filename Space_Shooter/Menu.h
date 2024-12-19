#pragma once
#include <SFML/Graphics.hpp>
#include "SceneBase.h"
#include "IGameObject.h"
#include "MyMath.h"
#include "playableGameObject.h"
#include "Input.h"
#include "MyMath.h"
#include "WidgetGameObject.h"

class Menu : public SceneBase
{
public:

    Menu(sf::RenderWindow* window, const float& framerate);
    ~Menu();
    void init();
    void processInput(sf::Event& event);
    
    void update(const float& deltaTime);
    
    void render()override;
    
    void playWidgetInit();
    void titleWidgetInit();
    void optionWidgetInit();
    void highscoreWidgetInit();
    void quitWidgetInit();

private:

    sf::RectangleShape m_Background;
    
};

