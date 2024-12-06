#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

class Menu {
    int pos;
    bool keyHeld, optionSelected;

    sf::RenderWindow* window;
    sf::RectangleShape* winclose;
    sf::Font* font;
    sf::Texture* image;
    sf::Sprite* menuBackground;
    sf::Music* menuMusic;

    sf::Vector2i pos_mouse;
    sf::Vector2f mouse_coord;

    std::vector<const char*> options;
    std::vector<sf::Vector2f> coords;
    std::vector<sf::Text> texts;
    std::vector<std::size_t> sizes;

protected:
    void setValues();
    void loopEvents();
    void drawAll();

public:
    Menu();
    ~Menu();
    void runMenu();
};


