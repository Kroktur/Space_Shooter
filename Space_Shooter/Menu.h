#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
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
    void Menuinput(IGameObject* object);
    void playWidgetInit();
    void titleWidgetInit();
    void optionWidgetInit();
    void highscoreWidgetInit();
    void quitWidgetInit();
    void MouseNav();
    void changewindow(int type);
    void SoundInit();
    void MusicInit();

private:
    sf::Music* menuMusic;
    //sf::SoundBuffer hoverBuffer;
    //sf::SoundBuffer clickBuffer;
    //sf::Sound hoverSound;
    //sf::Sound clickSound;
};
