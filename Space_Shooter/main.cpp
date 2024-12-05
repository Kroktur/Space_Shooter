#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include "circle.h"
std::vector<sf::Vector2f> getStarVertices(float radius, sf::Vector2f center, float angle)
{
    std::vector<sf::Vector2f> result;
    result.reserve(7);

    for (int i = 0; i < 7; ++i)
    {
        float alpha = 2.f * 3.1415926535f / 7.f * static_cast<float>(i);
        float x = radius * std::cos(alpha + angle);
        float y = radius * std::sin(alpha + angle);
        result.push_back(center + sf::Vector2f(x, y));
    }

    return result;
}

int main()
{
    std::vector<Projectile> projectiles;

    sf::Clock movement;

    bool inWindow = false;

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
    CircleShape testc(window);
    sf::RectangleShape background(sf::Vector2f(window.getSize()));
    sf::Texture backgroundtexture;
    backgroundtexture.loadFromFile("resource\\galaxie.bmp");
    background.setTexture(&backgroundtexture);
    window.setFramerateLimit(240);
    sf::CircleShape shape(300.f, 3);
    shape.setFillColor(sf::Color::Green);

    Missile m(window, testc.returnmyShape());
    bool lunchmissile = false;

    sf::RectangleShape rectangle(sf::Vector2f(200.f, 100.f));
    rectangle.setOrigin(100, 50);
    rectangle.setPosition(300.f, 300.f);
    rectangle.setFillColor(sf::Color::Green);

    float angle = 0.f;

    sf::Texture texture;
    texture.loadFromFile("C:/Src/BeginningSFML/Truc.bmp");

    sf::Sprite sprite;
    sprite.setTexture(texture);

    sf::Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/Arial.ttf"))
        std::cerr << "Failed to load font" << std::endl;

    sf::Text text;
    text.setFont(font);

    text.setString("Hello world");

    text.setCharacterSize(24); // in pixels, not points!
    text.setFillColor(sf::Color::White);

    const sf::Clock clock;
    const sf::Clock spawnClock;
    const sf::Time refreshTime = sf::seconds(1.f / 60.f);
    auto startSpawn = spawnClock.getElapsedTime().asMilliseconds();
    auto previous = clock.getElapsedTime().asMilliseconds();
    auto lag = 0.0;

    int counter = 0;
    bool isStopped = false;
    auto test = sf::Color::Black;
    sf::Text text1;
    sf::Text text2;

    text1.setFont(font);
    text1.setCharacterSize(24); // in pixels, not points!
    text1.setFillColor(sf::Color::White);
    text1.setPosition(sf::Vector2f(250, 0));

    text2.setFont(font);
    text2.setCharacterSize(24); // in pixels, not points!
    text2.setFillColor(sf::Color::White);
    text2.setPosition(sf::Vector2f(350, 0));

    while (window.isOpen())
    {
        if (const auto lastSpawnTick = spawnClock.getElapsedTime().asMilliseconds(); lastSpawnTick - startSpawn >= 1000)
        {
            if (!isStopped)
                text.setString(std::to_string(++counter));

            startSpawn = lastSpawnTick;

        }

        sf::Time deltaTime = movement.restart();


        const auto current = clock.getElapsedTime().asMilliseconds();
        const auto elapsed = current - previous;
        previous = current;
        lag += elapsed;
        window.clear(test);

        // input
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                    isStopped = !isStopped;

                /* if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                     testc.deplacement(Right);
                 if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                     testc.deplacement(Left);
                 if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
                     testc.deplacement(Up);
                 if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                     testc.deplacement(Down);*/
            }
            if (event.type == sf::Event::MouseEntered)
            {
                test = sf::Color::Blue;
                inWindow = true;

            }
            if (event.type == sf::Event::MouseLeft)
            {
                test = sf::Color::Black;
                inWindow = false;
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

               Projectile project(window,testc.returnmyShape());
               /* sf::CircleShape projectile(10);
                sf::Texture texturemissile;
                texturemissile.loadFromFile("resource\\space_cat_paw.png");
                projectile.setTexture(&texturemissile);
               */
                
                /*projectile.setOrigin(projectile.getRadius(), projectile.getRadius());
                projectile.setPosition(testc.returnmyShape().getPosition());*/

                sf::Vector2f target(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
                sf::Vector2f direction = target - testc.returnmyShape().getPosition();
                float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
                sf::Vector2f velocity = (direction / magnitude) * 300.f;
                project.setvelocity(velocity);
                projectiles.push_back({ project  });
            }

        }






        //testc.updatePosition(deltaTime, sf::Keyboard::D);
        //testc.updatePosition(deltaTime, sf::Keyboard::Q);
        //testc.updatePosition(deltaTime, sf::Keyboard::Z);
        //testc.updatePosition(deltaTime, sf::Keyboard::S);



        std::vector<sf::Vertex> lines;
        auto P = getStarVertices(200.f, sf::Vector2f(300.f, 300.f), angle);
        angle = angle + 0.01f;

        for (int i = 0; i < 7; ++i)
        {
            sf::RectangleShape rectangle(sf::Vector2f(3.f, 3.f));
            rectangle.setPosition(P[i]);
            rectangle.setFillColor(sf::Color::Red);
            /* window.draw(rectangle);*/
        }

        lines.reserve(14);

        int startIdx = 0;
        for (int i = 0; i < 7; ++i)
        {
            int endIdx = (startIdx + 3) % 7;
            lines.push_back(P[startIdx]);
            lines.push_back(P[endIdx]);
            startIdx = endIdx;
        }

        sprite.setOrigin(64, 64);
        sprite.setPosition(300.f, 300.f);

        while (refreshTime.asMilliseconds() > 0.0
            && lag >= refreshTime.asMilliseconds())
        {
            // update
            sprite.setRotation(-2.f * (angle * 180 / 3.14));
            lag -= refreshTime.asMilliseconds();

            text1.setString("x :" + std::to_string(sf::Mouse::getPosition(window).x));
            text2.setString("y :" + std::to_string(sf::Mouse::getPosition(window).y));

            auto mousePos = sf::Mouse::getPosition(window);
            auto rectangleBounds = rectangle.getGlobalBounds();

            if (rectangleBounds.contains(mousePos.x, mousePos.y))
            {
                rectangle.setFillColor(sf::Color::Red);
            }
            else
            {
                rectangle.setFillColor(sf::Color::Green);
            }



        }

        // render
    /*    window.draw(&lines[0], 14, sf::Lines);
        window.draw(sprite);*/

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f shipPos = testc.returnmyShape().getPosition();
        float deltaX = mousePos.x - shipPos.x;
        float deltaY = mousePos.y - shipPos.y;
        float angle_ = std::atan2(deltaY, deltaX) * 180 / 3.14159f;


        sf::Vector2f rectanglepos = rectangle.getPosition();
        float deltaX_r = mousePos.x - rectanglepos.x;
        float deltaY_r = mousePos.y - rectanglepos.y;

        float angle_rec = std::atan2(deltaY_r, deltaX_r) * 180 / 3.14159f;



        /*testc.returnmyShape().setRotation(40);*/
        


        if (inWindow)
        {
            window.draw(text1);
            window.draw(text2);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                testc.deplacement(deltaTime.asSeconds(), Right);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                testc.deplacement(deltaTime.asSeconds(), Left);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                testc.deplacement(deltaTime.asSeconds(), Down);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
                testc.deplacement(deltaTime.asSeconds(), Up);
            testc.rotation(angle_);
            rectangle.getGlobalBounds();
            rectangle.getLocalBounds();
            rectangle.setRotation(60);

           

            for (auto& projectile : projectiles)
            {
                projectile.move(projectile.getvelocity(), deltaTime.asSeconds());
            }



          /*  if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                lunchmissile = !lunchmissile;
                m.LunchMissile(angle_);

            }*/
            auto testcBound = testc.returnmyShape().getGlobalBounds();
            auto rectanglebound = rectangle.getGlobalBounds();
            if (testcBound.intersects(rectanglebound))
            {
                 rectangle.setFillColor(sf::Color::Black);
            }

        }

        window.draw(background);


        if (lunchmissile)
        {

            window.draw(m.returnmyShape());
            m.setposition(deltaTime);
        }
        for ( auto& projectile : projectiles)
        {
            
            window.draw(projectile.drawmyShape());
           
        }

       
      /*  window.draw(rectangle);*/
        window.draw(testc.returnmyShape());
        window.draw(text);


        window.display();
    }
 
    return 0;
}