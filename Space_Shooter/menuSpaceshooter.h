#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

class Menu {
    int pos;
    bool keyHeld, optionSelected, inMainMenu;

    sf::RenderWindow* window;
    sf::RectangleShape* winclose;
    sf::Font* font;
    sf::Texture* image;
    sf::Sprite* menuBackground;
    sf::Music* menuMusic;
    sf::SoundBuffer hoverBuffer;
    sf::SoundBuffer clickBuffer;
    sf::Sound hoverSound;
    sf::Sound clickSound;

    sf::Vector2i pos_mouse;
    sf::Vector2f mouse_coord;

    std::vector<const char*> options;
    std::vector<sf::Vector2f> coords;
    std::vector<sf::Text> texts;
    std::vector<std::size_t> sizes;

protected:
    void setValues();
    void loopEvents();
    void KeyboardNav();
    void MouseNav();
    void drawAll();

public:
    Menu();
    ~Menu();
    void runMenu();
};


