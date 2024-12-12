#include <iostream>
#include <SFML/Graphics.hpp>


class SceneBase
{
public:
    SceneBase(sf::RenderWindow* window, const float& framereta) : m_renderwindow(window), m_refreshTime(framereta)
    {
        
    }
    virtual ~SceneBase() = default;
    virtual void processInput(const sf::Event& event) = 0;
    virtual void update(const float& deltaTime) = 0;
    virtual void render() = 0;
    float getRefreshTime()const
    {
        return m_refreshTime;
    }
protected:
    sf::RenderWindow* m_renderwindow;
   float m_refreshTime;
 };

class SceneManager
{
public :
    SceneManager(const int& width, const int& height, const std::string& title) : window(std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), title))
    {
        m_scene.push_back(std::make_unique<Game>(window.get(), 60));
        m_scene.push_back(std::make_unique<Menu>(window.get(), 30));
    }
private :
    std::unique_ptr<sf::RenderWindow> window;
    std::vector<std::unique_ptr<SceneBase>> m_scene;
    SceneBase* m_curentscene;
};

class Game : public SceneBase
{
    Game(sf::RenderWindow* window, const float& framereta) : SceneBase(window, framereta)
    {
       
    }
    void processInput(const sf::Event& event)
    {

    }
    void update(const float& deltaTime)
    {

 }
    void render()
    {

  }
};
class Menu : public SceneBase
{
    Menu(sf::RenderWindow* window, const float& framereta) : SceneBase(window, framereta)
    {

    }
    void processInput(const sf::Event& event)
    {

    }
    void update(const float& deltaTime)
    {

    }
    void render()
    {

    }
};
int main()
{
   

    return 0;
}