#include "Scenemanager.h"


inline SceneManager::SceneManager(const int& width, const int& height, const std::string& title) :m_window(std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), title))
{

}
void SceneManager::processInput()
{
    // input
    sf::Event event;
    while (m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_window->close();

        if (event.type == sf::Event::KeyPressed)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                if (m_currentScene == m_scenes.front().get())
                    m_currentScene = m_scenes.back().get();
                else if (m_currentScene == m_scenes.back().get())
                    m_currentScene = m_scenes.front().get();
            }
        }

        m_currentScene->processInput(event);
    }
}

void SceneManager::Exe()
{
    // We start the clock
    const sf::Clock clock;
    const sf::Clock spawnClock;
    float startSpawn = spawnClock.getElapsedTime().asMilliseconds();
    float previous = clock.getElapsedTime().asMilliseconds();
    auto lag = 0.0;

    int counter = 0;
    while (m_window->isOpen())
    {
        if (const float lastSpawnTick = spawnClock.getElapsedTime().asMilliseconds(); lastSpawnTick - startSpawn > 1000)
        {
            std::cout << "FPS: " << counter << std::endl;
            startSpawn = lastSpawnTick;
            counter = 0;
        }

        const float current = clock.getElapsedTime().asMilliseconds();
        const auto elapsed = current - previous;
        previous = current;
        lag += elapsed;
        m_window->clear();

        processInput();
        m_currentScene->processInput(event);
        while (m_currentScene->getRefreshTime().asMilliseconds() > 0.0
            && lag >= m_currentScene->getRefreshTime().asMilliseconds())
        {
            
            m_currentScene->update(elapsed);
            lag -= m_currentScene->getRefreshTime().asMilliseconds();
            ++counter;
        }

        m_currentScene->render();
        m_window->display();
    }
}
