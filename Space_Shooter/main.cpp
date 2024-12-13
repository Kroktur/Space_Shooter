#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Scenemanager.h"
#include "playableGameObject.h"
#include"Game.h"
#include "MyGame.h"

int main()
{
  
    SceneManager sceneManager(1920, 1080, "Test Manager",sf::Style::Fullscreen );
     /* sceneManager.push_back(std::make_unique<Menu>(sceneManager.getWindow(), 30.f));*/
     sceneManager.push_back(std::make_unique<Game>(sceneManager.getWindow(), 60));
     sceneManager.setCurrentScene(0);
     sceneManager.Exe();
   /* sf::RenderWindow window(sf::VideoMode(600, 600), "test");
    SceneManager sceneManager(600, 600, "Test Manager");
    sceneManager.Exe();*/
   /* Game game(window,40);
    IGameObject* gameobjct = new Ship(game);*/
  /*  sf::CircleShape circle;

    sf::Event event ;
    Iinput* input = new PlayerInput;
    input->processinput(circle);*/

   /* SceneManger* scene
    
    scene = new SceneBase;
    scene.push_back() < Pipi >

        MyGame game(scene);
        MyGame.exe();*/


    return 0;
}
//#include <iostream>
//#include <SFML/Graphics.hpp>
//
//std::vector<sf::Vector2f> getStarVertices(float radius, sf::Vector2f center, float angle)
//{
//    std::vector<sf::Vector2f> result;
//    result.reserve(7);
//
//    for (int i = 0; i < 7; ++i)
//    {
//        float alpha = 2.f * 3.1415926535f / 7.f * static_cast<float>(i);
//        float x = radius * std::cos(alpha + angle);
//        float y = radius * std::sin(alpha + angle);
//        result.push_back(center + sf::Vector2f(x, y));
//    }
//
//    return result;
//}
//
//class SceneBasetset
//{
//public:
//    SceneBasetset(sf::RenderWindow* window, const float& framerate)
//        : m_renderWindow(window)
//        , m_refreshTime(sf::seconds(1.f / framerate))
//    {
//
//    }
//
//    virtual ~SceneBasetset() = default;
//    virtual void processInput(const sf::Event& event) = 0;
//    virtual void update(const float& deltaTime) = 0;
//    virtual void render() = 0;
//
//    sf::Time getRefreshTime() const
//    {
//        return m_refreshTime;
//    }
//
//protected:
//    sf::RenderWindow* m_renderWindow;
//    sf::Time m_refreshTime;
//};
//
//class Gametset : public SceneBasetset
//{
//public:
//    Gametset(sf::RenderWindow* window, const float& framerate)
//        : SceneBasetset(window, framerate)
//    {
//        m_shape.setRadius(300.f);
//        m_shape.setPointCount(10);
//        m_shape.setFillColor(sf::Color::Blue);
//    }
//
//    void processInput(const sf::Event& event) override
//    {
//
//    }
//
//    void update(const float& deltaTime) override
//    {
//
//    }
//
//    void render() override
//    {
//        m_renderWindow->draw(m_shape);
//    }
//
//private:
//    sf::CircleShape m_shape;
//};
//
//class Menu : public SceneBasetset
//{
//public:
//    Menu(sf::RenderWindow* window, const float& framerate)
//        : SceneBasetset(window, framerate)
//    {
//        m_shape.setRadius(300.f);
//        m_shape.setPointCount(10);
//        m_shape.setFillColor(sf::Color::Green);
//    }
//
//    void processInput(const sf::Event& event) override
//    {
//
//    }
//
//    void update(const float& deltaTime) override
//    {
//
//    }
//
//    void render() override
//    {
//        m_renderWindow->draw(m_shape);
//    }
//
//private:
//    sf::CircleShape m_shape;
//};
//
//class SceneManagertst
//{
//public:
//    SceneManagertst(const int& width, const int& height, const std::string& title)
//        : m_window(std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), title))
//        , m_currentScene(nullptr)
//    {
//        //m_scenes.push_back(std::make_unique<Menu>(m_window.get(), 30.f));
//        //m_scenes.push_back(std::make_unique<Game>(m_window.get(), 60.f));
//        //m_currentScene = m_scenes.front().get();
//    }
//
//    void push_back(std::unique_ptr<SceneBasetset> scene)
//    {
//        m_scenes.push_back(std::move(scene));
//    }
//
//    sf::RenderWindow* getWindow()
//    {
//        return m_window.get();
//    }
//
//    void setCurrentScene(const int& index)
//    {
//        m_currentScene = m_scenes[index].get();
//    }
//
//    void processInput()
//    {
//        // input
//        sf::Event event;
//        while (m_window->pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//                m_window->close();
//
//            if (event.type == sf::Event::KeyPressed)
//            {
//                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
//                {
//                    if (m_currentScene == m_scenes.front().get())
//                        m_currentScene = m_scenes.back().get();
//                    else if (m_currentScene == m_scenes.back().get())
//                        m_currentScene = m_scenes.front().get();
//                }
//            }
//
//            m_currentScene->processInput(event);
//        }
//    }
//
//    void exec()
//    {
//        // We start the clock
//        const sf::Clock clock;
//        const sf::Clock spawnClock;
//        float startSpawn = spawnClock.getElapsedTime().asMilliseconds();
//        float previous = clock.getElapsedTime().asMilliseconds();
//        auto lag = 0.0;
//
//        int counter = 0;
//        while (m_window->isOpen())
//        {
//            if (const float lastSpawnTick = spawnClock.getElapsedTime().asMilliseconds(); lastSpawnTick - startSpawn > 1000)
//            {
//                std::cout << "FPS: " << counter << std::endl;
//                startSpawn = lastSpawnTick;
//                counter = 0;
//            }
//
//            const float current = clock.getElapsedTime().asMilliseconds();
//            const auto elapsed = current - previous;
//            previous = current;
//            lag += elapsed;
//            m_window->clear();
//
//            processInput();
//
//            while (m_currentScene->getRefreshTime().asMilliseconds() > 0.0
//                && lag >= m_currentScene->getRefreshTime().asMilliseconds())
//            {
//                m_currentScene->update(elapsed);
//                lag -= m_currentScene->getRefreshTime().asMilliseconds();
//                ++counter;
//            }
//
//            m_currentScene->render();
//            m_window->display();
//        }
//    }
//
//
//private:
//    std::unique_ptr<sf::RenderWindow> m_window;
//    std::vector<std::unique_ptr<SceneBasetset>> m_scenes;
//    SceneBasetset* m_currentScene;
//};
//
//int main()
//{
//    SceneManagertst sceneManager(600, 600, "Test Manager");
//    sceneManager.push_back(std::make_unique<Menu>(sceneManager.getWindow(), 30.f));
//    sceneManager.push_back(std::make_unique<Gametset>(sceneManager.getWindow(), 60.f));
//    sceneManager.setCurrentScene(0);
//    sceneManager.exec();
//    //sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");
//    //window.setFramerateLimit(60);
//    //sf::CircleShape shape(300.f, 3);
//    //shape.setFillColor(sf::Color::Green);
//
//    //sf::RectangleShape rectangle(sf::Vector2f(200.f, 200.f));
//    //rectangle.setPosition(200.f, 200.f);
//    //rectangle.setFillColor(sf::Color::Blue);
//
//    //float angle = 0.f;
//
//    //sf::Texture texture;
//    //texture.loadFromFile("C:/Src/BeginningSFML/Truc.bmp");
//
//    //sf::Sprite sprite;
//    //sprite.setTexture(texture);
//
//    //sf::Font font;
//    //if (!font.loadFromFile("C:/Windows/Fonts/Arial.ttf"))
//    //    std::cerr << "Failed to load font" << std::endl;
//
//    //sf::Text text;
//    //text.setFont(font); 
//
//    //text.setString("Hello world");
//
//    //text.setCharacterSize(24); // in pixels, not points!
//    //text.setFillColor(sf::Color::White);
//
//    //const sf::Clock clock;
//    //const sf::Clock spawnClock;
//    //const sf::Time refreshTime = sf::seconds(1.f / 60.f);
//    //auto startSpawn = spawnClock.getElapsedTime().asMilliseconds();
//    //auto previous = clock.getElapsedTime().asMilliseconds();
//    //auto lag = 0.0;
//
//    //int counter = 0;
//    //bool isStopped = false;
//
//    //while (window.isOpen())
//    //{
//    //    if (const auto lastSpawnTick = spawnClock.getElapsedTime().asMilliseconds(); lastSpawnTick - startSpawn >= 1000)
//    //    {
//    //        if (!isStopped)
//                //text.setString(std::to_string(++counter));
//
//    //        startSpawn = lastSpawnTick;
//    //    }
//
//    //    const auto current = clock.getElapsedTime().asMilliseconds();
//    //    const auto elapsed = current - previous;
//    //    previous = current;
//    //    lag += elapsed;
//    //    window.clear();
//
//    //    // input
//    //    sf::Event event;
//    //    while (window.pollEvent(event))
//    //    {
//    //        if (event.type == sf::Event::Closed)
//    //            window.close();
//
//    //        if (event.type == sf::Event::KeyPressed)
//    //        {
//    //            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
//                //	isStopped = !isStopped;
//    //        }
//    //    }
//
//    //    std::vector<sf::Vertex> lines;
//    //    auto P = getStarVertices(200.f, sf::Vector2f(300.f, 300.f), angle);
//    //    angle = angle + 0.01f;
//
//    //    for (int i = 0; i < 7; ++i)
//    //    {
//    //        sf::RectangleShape rectangle(sf::Vector2f(3.f, 3.f));
//    //        rectangle.setPosition(P[i]);
//    //        rectangle.setFillColor(sf::Color::Red);
//    //        window.draw(rectangle);
//    //    }
//
//    //    lines.reserve(14);
//
//    //    int startIdx = 0;
//    //    for (int i = 0; i < 7; ++i)
//    //    {
//    //        int endIdx = (startIdx + 3) % 7;
//    //        lines.push_back(P[startIdx]);
//    //        lines.push_back(P[endIdx]);
//    //        startIdx = endIdx;
//    //    }
//
//    //    sprite.setOrigin(64, 64);
//    //    sprite.setPosition(300.f, 300.f);
//
//    //    while (refreshTime.asMilliseconds() > 0.0
//    //        && lag >= refreshTime.asMilliseconds())
//    //    {
//    //        // update
//    //        sprite.setRotation(-2.f * (angle * 180 / 3.14));
//    //        lag -= refreshTime.asMilliseconds();
//    //    }
//
//    //    // render
//    //    window.draw(&lines[0], 14, sf::Lines);
//    //    window.draw(sprite);
//    //    window.draw(text);
//    //    window.display();
//    //}
//
//    return 0;
//}