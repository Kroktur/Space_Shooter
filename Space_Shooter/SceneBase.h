#pragma once
#include <SFML/Graphics.hpp>
#include "Ressource.h"
#include "IGameObject.h"

class SceneBase
{
public:
    friend IGameObject;
    SceneBase(sf::RenderWindow* window, const float& framerate);
    virtual ~SceneBase() = default;
    virtual void processInput( sf::Event& event) = 0;
    virtual void update(const float& deltaTime) = 0;
    virtual void render() = 0;
    sf::Time getRefreshTime()const;
    void addObject();
    void toberemoved(IGameObject* it);
    void deleteObject();
    void addScore(int score = 1);
    sf::Vector2u getWindowSize();
    sf::RenderWindow* getWindow();
    TextureCache& gettexture();
    FontCache& getfont();
protected:
    sf::RenderWindow* m_renderwindow;
    sf::Time m_refreshTime;
    TextureCache m_texture;
    FontCache m_font;
    int m_totalscore ;
    std::vector<IGameObject*> m_allGameObject;
    std::vector<IGameObject*> m_tobeaddGameObject;
    std::vector<IGameObject*> m_toberemovedGameObject;
};
