#pragma once
#include <SFML/Graphics.hpp>
#include "Ressource.h"

class SceneBase
{
public:
    SceneBase(sf::RenderWindow* window, const float& framerate);
    virtual ~SceneBase() = default;
    virtual void processInput( sf::Event& event) = 0;
    virtual void update(const float& deltaTime) = 0;
    virtual void render() = 0;
    sf::Time getRefreshTime()const;
    
    TextureCache& gettexture();
    
protected:
    sf::RenderWindow* m_renderwindow;
    sf::Time m_refreshTime;
    TextureCache m_texture;
    int m_totalscore;
};
