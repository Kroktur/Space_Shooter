#pragma once
#include <SFML/Graphics.hpp>


class SceneBase
{
public:
    SceneBase(sf::RenderWindow* window, const float& framerate);
    virtual ~SceneBase() = default;
    virtual void processInput(const sf::Event& event) = 0;
    virtual void update(const float& deltaTime) = 0;
    virtual void render() = 0;
    sf::Time getRefreshTime()const
    {
        return m_refreshTime;
    }
protected:
    sf::RenderWindow* m_renderwindow;
    sf::Time m_refreshTime;
};
