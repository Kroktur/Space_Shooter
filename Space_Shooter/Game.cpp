#include "Game.h"
#include "IGameObject.h"
#include "GameObject.h"
#include "IWeapon.h"
#include "Weapon.h"
Game::Game() : m_window(sf::VideoMode(1920, 1080), "SFML works!") { m_window.setFramerateLimit(60); }

Game::~Game()
{
    for (auto Object : m_allGameObject)
        delete Object;
    m_allGameObject.clear();
}

void Game::run()
{
    init();
    while (m_window.isOpen())
    {
        
        m_window.clear();
      
       

            
       
            HandleInput();
            Update();
            Render();
           
      

     
    }
    
}

void Game::init()
{
    IGameObject* ship;
    ship = new Ship(*this);
    IGameObject* enemie;
    enemie = new Ennemie_Ship(*this, ship->getShape());
    IGameObject* enemie2;
    enemie2 = new Ennemie_Ship(*this, ship->getShape());
    IGameObject* enemie3;
    enemie3 = new Ennemie_Ship(*this, ship->getShape());
    IGameObject* enemie4;
    enemie4 = new Ennemie_Ship(*this, ship->getShape());
    m_allGameObject.push_back(ship);
    m_allGameObject.push_back(enemie);
    m_allGameObject.push_back(enemie2);
    m_allGameObject.push_back(enemie3);
    m_allGameObject.push_back(enemie4);
    m_Background.setSize(static_cast<sf::Vector2f>(m_window.getSize()));
    m_Background.setTexture(&m_texture.getTexture("resource\\galaxie.bmp"));
}

sf::Vector2u Game::getWindowSize()
{
    return m_window.getSize();
}

TextureCache& Game::gettexture()
{
    return m_texture;
}

sf::RenderWindow& Game::getWindow()
{
    return m_window;
}



void Game::HandleInput()
{
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_window.close();

        if (event.type == sf::Event::MouseEntered)
        {
            inWindow = true;
        }
        if (event.type == sf::Event::MouseLeft)
        {
            inWindow = false;
        }
      
    }

   
   
    for (auto Object : m_allGameObject)
    {
        Object->HandleInput();
    }
       
    
}

void Game::Update()
{
    if (inWindow)
    {
        for (auto Object : m_allGameObject)
        {
            Object->Update();
        }
    }
}

inline void Game::Render()
{
  
        m_window.draw(m_Background);
        for (auto Object : m_allGameObject)
        {
            Object->Render(m_window);
        }
        m_window.display();
    
}
