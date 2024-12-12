#pragma once
class SceneManager;
#include <iostream>


class myGame
{
public:
    myGame(SceneManager* scene);
    ~myGame() = default;
    void Exe();
private:
    SceneManager* m_scene;
};

