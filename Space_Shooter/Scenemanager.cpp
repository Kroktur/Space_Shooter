#include "Scenemanager.h"


inline SceneManager::SceneManager(const int& width, const int& height, const std::string& title) :m_window(std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), title))
{

}

void SceneManager::Exe()
{
}
