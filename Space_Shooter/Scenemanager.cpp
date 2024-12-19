#include "Scenemanager.h"



SceneManager::SceneManager(const int& width, const int& height, const std::string& title, const int& style) :m_window(std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), title , style))
{

}
void SceneManager::processInput()
{
    // input
   
    while (m_window->pollEvent(m_event))
    {
        if (m_event.type == sf::Event::Closed)
            m_window->close();

        if (m_event.type == sf::Event::KeyPressed)
        {
          /*  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                if (m_currentScene == m_scenes.front().get())
                    m_currentScene = m_scenes.back().get();
                else if (m_currentScene == m_scenes.back().get())
                    m_currentScene = m_scenes.front().get();
            }*/
        }
    }
}

void SceneManager::push_back(std::unique_ptr<SceneBase> scene)
{
    
        m_scenes.push_back(std::move(scene));
    
}

void SceneManager::setCurrentScene(const int& index)
{
    m_currentScene = m_scenes[index].get();
}

sf::RenderWindow* SceneManager::getWindow()
{
    return m_window.get();
}



void SceneManager::Exe()
{
    // We start the clock
    const sf::Clock clock;
    const sf::Clock spawnClock;
  /*  float startSpawn = spawnClock.getElapsedTime().asMilliseconds();*/
    float previous = clock.getElapsedTime().asSeconds();
    auto lag = 0.0;
  
   /* int counter = 0;*/
    while (m_window->isOpen())
    {
   

        const float current = clock.getElapsedTime().asMilliseconds();
        const auto elapsed = current - previous;
        previous = current;
        lag += elapsed;
       
        m_window->clear();

        processInput();
        m_currentScene->processInput(m_event);
       
        while (m_currentScene->getRefreshTime().asMilliseconds() > 0.0
            && lag >= m_currentScene->getRefreshTime().asMilliseconds())
        {
            
            m_currentScene->update(elapsed);
            lag -= m_currentScene->getRefreshTime().asMilliseconds();
            /*++counter;*/
        }

        m_currentScene->render();
        m_window->display();
    }
    
}
