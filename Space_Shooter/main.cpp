#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Scenemanager.h"
#include "playableGameObject.h"
#include"Game.h"
#include "MyGame.h"
#include "Menu.h"
#include "OptionMenu.h"
int main()
{

    SceneManager sceneManager(1920, 1080, "Test Manager" , sf::Style::Fullscreen );
    sceneManager.push_back(std::make_unique<Menu>(sceneManager.getWindow(), 30.f));
    sceneManager.push_back(std::make_unique<Game>(sceneManager.getWindow(), 60));
    sceneManager.push_back(std::make_unique<OptionMenu>(sceneManager.getWindow(), 30));
    sceneManager.setCurrentScene(1);
    sceneManager.Exe();

    return 0;
}