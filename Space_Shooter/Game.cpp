#include "Game.h"
#include "IGameObject.h"

Game::Game() : m_window(sf::VideoMode(1920, 1080), "SFML works!") { m_window.setFramerateLimit(60); }

Game::~Game()
{
    for (auto Object : m_allGameObject)
        delete Object;
    m_allGameObject.clear();
}

void Game::run()
{
    while (m_window.isOpen())
    {
        HandleInput();

        Update();

        Render();
    }
}

void Game::HandleInput()
{

}

void Game::Update()
{
    for (auto Object : m_allGameObject)
    {
        Object->Update();
    }
}

inline void Game::Render()
{
    for (auto Object : m_allGameObject)
    {
        Object->Render(m_window);
    }
}
