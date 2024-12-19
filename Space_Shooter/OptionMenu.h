#pragma once
#include <SFML/Graphics.hpp>
#include "SceneBase.h"
#include "IGameObject.h"
#include "MyMath.h"
#include "playableGameObject.h"
#include "Input.h"
#include "MyMath.h"
#include "WidgetGameObject.h"

class OptionMenu : public SceneBase
{
public:

    OptionMenu(sf::RenderWindow* window, const float& framerate);
    ~OptionMenu();
    void init();
    void processInput(sf::Event& event);

    void update(const float& deltaTime);

    void render()override;

    void titleOptionWidgetInit();
    void resolutionWidgetInit();
    void controlsWidgetInit();
    void backWidgetInit();

private:

    sf::RectangleShape m_Background;

};
