#ifndef OPTIONSPACESHIP_H
#define OPTIONSPACESHIP_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <string>

class Option {
private:
    sf::RenderWindow* window;
    sf::Font font;
    sf::Sprite* background;
    sf::Texture* bgTexture;
    std::vector<sf::Text> texts;
    std::vector<std::string> options;
    bool keyHeld = false;
    int selectedOption;

    sf::Vector2u windowSize;
    sf::Vector2f mouse_coord;
    std::map<std::string, sf::Keyboard::Key> keyBindings;

    void loadKeyBindings();
    void saveKeyBindings();

public:
    Option(sf::RenderWindow* win);
    ~Option();

    void displayOptions();
    void handleInput();
    void mouseOptionNav();
    void updateHoverEffect();
    void applyChanges();
    void handleResolutionSelection();
    bool isKeyTaken(sf::Keyboard::Key key);
    std::string getKeyString(sf::Keyboard::Key key);
    void handleControlsConfiguration();
    void run();
};

#endif // OPTIONSPACESHIP_H

