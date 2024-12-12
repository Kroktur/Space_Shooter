#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "SceneBase.h"

class SceneManager
{
public:
    SceneManager(const int& width, const int& height, const std::string& title);
    void Exe();
private:
    std::unique_ptr<sf::RenderWindow> m_window;
    std::vector<std::unique_ptr<SceneBase>> m_scenes;
    SceneBase* m_curentscene;
};
