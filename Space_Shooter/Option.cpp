#include "Option.h"
#include "menuSpaceshooter.h"
#include <fstream>

Option::Option(sf::RenderWindow* win) : window(win), selectedOption(0), windowSize(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height)
{
    if (!font.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf"))
        std::cerr << "Error loading font\n";

    bgTexture = new sf::Texture();
    background = new sf::Sprite();

    if (!bgTexture->loadFromFile("C:\\Users\\boulanger\\source\\repos\\Space_Shootertest\\Space_Shooter\\resource\\galaxie.bmp"))
        std::cerr << "Error loading background texture\n";

    background->setTexture(*bgTexture);
    background->setScale(
        static_cast<float>(windowSize.x) / bgTexture->getSize().x,
        static_cast<float>(windowSize.y) / bgTexture->getSize().y
    );

    options = { "Change Resolution", "Configure Controls", "Back" };
    texts.resize(options.size());

    mouse_coord = { 0, 0 };

    for (size_t i = 0; i < texts.size(); ++i)
    {
        texts[i].setFont(font);
        texts[i].setString(options[i]);
        texts[i].setCharacterSize(50);
        texts[i].setPosition(100.f, 200.f + i * 100.f);
        texts[i].setFillColor(i == selectedOption ? sf::Color::Yellow : sf::Color::White);
    }

    loadKeyBindings();
}

Option::~Option() 
{
    delete background;
    delete bgTexture;
}

void Option::loadKeyBindings()
{
    std::ifstream file("keybindings.txt");

    keyBindings = {
    {"MoveUp", sf::Keyboard::W},
    {"MoveDown", sf::Keyboard::S},
    {"MoveLeft", sf::Keyboard::A},
    {"MoveRight", sf::Keyboard::D},
    {"Fire", sf::Keyboard::Space},
    {"Shield", sf::Keyboard::F}
    };

    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            size_t pos = line.find("=");
            if (pos != std::string::npos)
            {
                std::string action = line.substr(0, pos);
                int keyCode = std::stoi(line.substr(pos + 1));

                if (keyBindings.find(action) != keyBindings.end())
                    keyBindings[action] = static_cast<sf::Keyboard::Key>(keyCode);
            }
        }
        file.close();
        std::cout << "Key bindings loaded!\n";
    }
    else
    {
        std::cerr << "Error loading key bindings from file!\n";
    }
}

void Option::saveKeyBindings()
{
    std::ofstream file("keybindings.txt");

    if (file.is_open())
    {
        for (const auto& pair : keyBindings)
            file << pair.first << "=" << pair.second << std::endl;  
        file.close();
        std::cout << "Key bindings saved!\n";
    }
    else
        std::cerr << "Error saving key bindings to file!\n";
}

bool Option::isKeyTaken(sf::Keyboard::Key key)
{
    for (const auto& pair : keyBindings)
        if (pair.second == key)
            return true;  
    return false;  
}

void Option::displayOptions() 
{
    window->clear();
    window->draw(*background);

    for (auto& text : texts) 
        window->draw(text);

    window->display();
}

void Option::handleResolutionSelection()
{
    std::vector<sf::Vector2u> resolutions =
    {
        {1280, 720},
        {1920, 1080},
        {2560, 1440},
        {3840, 2160}
    };

    if (std::find(resolutions.begin(), resolutions.end(), sf::Vector2u(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height)) == resolutions.end())
        resolutions.push_back({ sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height });

    std::vector<sf::Text> resolutionTexts(resolutions.size());
    int selectedResolution = 0;

    for (size_t i = 0; i < resolutions.size(); ++i)
    {
        resolutionTexts[i].setFont(font);
        resolutionTexts[i].setString(std::to_string(resolutions[i].x) + " x " + std::to_string(resolutions[i].y));
        resolutionTexts[i].setCharacterSize(50);
        resolutionTexts[i].setPosition(200.f, 200.f + i * 100.f);
        resolutionTexts[i].setFillColor(i == selectedResolution ? sf::Color::Yellow : sf::Color::White);
    }

    bool choosingResolution = true;

    while (choosingResolution && window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window->close();
                return;
            }

            if (event.type == sf::Event::MouseMoved)
            {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
                sf::Vector2f mouseCoords = window->mapPixelToCoords(mousePosition);

                for (size_t i = 0; i < resolutionTexts.size(); ++i)
                    if (resolutionTexts[i].getGlobalBounds().contains(mouseCoords))
                        selectedResolution = static_cast<int>(i);
            }

            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
                sf::Vector2f mouseCoords = window->mapPixelToCoords(mousePosition);

                for (size_t i = 0; i < resolutionTexts.size(); ++i)
                {
                    if (resolutionTexts[i].getGlobalBounds().contains(mouseCoords))
                    {
                        windowSize = resolutions[selectedResolution];
                        applyChanges();
                        choosingResolution = false;
                    }
                }
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Down)
                    selectedResolution = (selectedResolution + 1) % resolutions.size();

                if (event.key.code == sf::Keyboard::Up)
                    selectedResolution = (selectedResolution - 1 + resolutions.size()) % resolutions.size();

                if (event.key.code == sf::Keyboard::Enter)
                {
                    windowSize = resolutions[selectedResolution];
                    applyChanges();
                    choosingResolution = false;
                }

                if (event.key.code == sf::Keyboard::Escape)
                    choosingResolution = false;
            }
        }

        for (size_t i = 0; i < resolutionTexts.size(); ++i)
            resolutionTexts[i].setFillColor(i == selectedResolution ? sf::Color::Yellow : sf::Color::White);

        window->clear();
        window->draw(*background);
        for (const auto& text : resolutionTexts)
            window->draw(text);
        window->display();
    }
}

void Option::handleInput()
{
    sf::Event event;
    while (window->pollEvent(event))
        if (event.type == sf::Event::Closed)
            window->close();
}

void Option::updateHoverEffect()
{
    sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window));

    for (size_t i = 0; i < texts.size(); ++i)
    {
        if (texts[i].getGlobalBounds().contains(mousePos))
            texts[i].setFillColor(sf::Color::Yellow);  
        else
            texts[i].setFillColor(sf::Color::White);  
    }
}

void Option::handleControlsConfiguration()
{
    sf::RenderWindow configWindow(sf::VideoMode(800, 600), "Configure Controls");

    bool configuringControls = true;
    int selectedControl = -1;
    std::vector<sf::Text> controlTexts(keyBindings.size());

    int i = 0;
    for (auto& keyBinding : keyBindings)
    {
        controlTexts[i].setFont(font);
        controlTexts[i].setString(keyBinding.first + ": " + getKeyString(keyBinding.second));
        controlTexts[i].setCharacterSize(50);
        controlTexts[i].setPosition(200.f, 200.f + i * 100.f);
        controlTexts[i].setFillColor(i == selectedControl ? sf::Color::Yellow : sf::Color::White);
        ++i;
    }

    while (configuringControls && configWindow.isOpen())
    {
        sf::Event event;
        while (configWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                configWindow.close();
                return;
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                for (int i = 0; i < controlTexts.size(); ++i)
                {
                    if (controlTexts[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(configWindow))))
                    {
                        selectedControl = i;
                        controlTexts[i].setString(keyBindings[options[i]] + ": Press any key...");
                        break;
                    }
                }
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (selectedControl >= 0 && selectedControl < keyBindings.size())
                {
                    if (isKeyTaken(event.key.code))
                    {
                        sf::Text errorText;
                        errorText.setFont(font);
                        errorText.setString("Key already used, please choose another one.");
                        errorText.setCharacterSize(30);
                        errorText.setPosition(200.f, 400.f);
                        errorText.setFillColor(sf::Color::Red);
                        configWindow.draw(errorText);
                        configWindow.display();
                        continue;
                    }

                    keyBindings[options[selectedControl]] = event.key.code;

                    controlTexts[selectedControl].setString(options[selectedControl] + ": " + getKeyString(event.key.code));
                    saveKeyBindings();
                    selectedControl = -1;
                }
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                configuringControls = false;
        }

        for (size_t i = 0; i < controlTexts.size(); ++i)
            controlTexts[i].setFillColor(i == selectedControl ? sf::Color::Yellow : sf::Color::White);

        configWindow.clear();
        configWindow.draw(*background);
        for (const auto& text : controlTexts)
            configWindow.draw(text);
        configWindow.display();
    }
}

std::string Option::getKeyString(sf::Keyboard::Key key)
{
    switch (key)
    {
    case sf::Keyboard::A: return "A";
    case sf::Keyboard::B: return "B";
    case sf::Keyboard::C: return "C";
    case sf::Keyboard::D: return "D";
    case sf::Keyboard::E: return "E";
    case sf::Keyboard::F: return "F";
    case sf::Keyboard::G: return "G";
    case sf::Keyboard::H: return "H";
    case sf::Keyboard::I: return "I";
    case sf::Keyboard::J: return "J";
    case sf::Keyboard::K: return "K";
    case sf::Keyboard::L: return "L";
    case sf::Keyboard::M: return "M";
    case sf::Keyboard::N: return "N";
    case sf::Keyboard::O: return "O";
    case sf::Keyboard::P: return "P";
    case sf::Keyboard::Q: return "Q";
    case sf::Keyboard::R: return "R";
    case sf::Keyboard::S: return "S";
    case sf::Keyboard::T: return "T";
    case sf::Keyboard::U: return "U";
    case sf::Keyboard::V: return "V";
    case sf::Keyboard::W: return "W";
    case sf::Keyboard::X: return "X";
    case sf::Keyboard::Y: return "Y";
    case sf::Keyboard::Z: return "Z";
    case sf::Keyboard::Space: return "Space";

    default: return "Unknown";
    }
}

void Option::mouseOptionNav()
{
    static bool mouseClicked = false;

    sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window));

    for (std::size_t i = 0; i < texts.size(); ++i)
    {
        if (texts[i].getGlobalBounds().contains(mousePos))
        {
            texts[i].setFillColor(sf::Color::Yellow);
            selectedOption = i;
        }
        else
            texts[i].setFillColor(sf::Color::White);
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mouseClicked)
    {
        for (std::size_t i = 0; i < texts.size(); ++i)
        {
            if (texts[i].getGlobalBounds().contains(mousePos))
            {
                std::cout << "Option clicked: " << options[i] << '\n';

                if (options[i] == "Change Resolution")
                    handleResolutionSelection();
                else if (options[i] == "Configure Controls")
                    handleControlsConfiguration();  
                else if (options[i] == "Back")
                    return;

                mouseClicked = true;
                break;
            }
        }
    }
    else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
        mouseClicked = false;
}

void Option::run()
{
    bool inOptionsMenu = true;

    while (inOptionsMenu && window->isOpen())
    {
        handleInput();        
        mouseOptionNav();          
        updateHoverEffect();  
        displayOptions();     

        if (options[selectedOption] == "Back")
            inOptionsMenu = false;
    }
}

void Option::applyChanges()
{
    window->create(sf::VideoMode(windowSize.x, windowSize.y), "Spaceship Conqueror", sf::Style::Fullscreen);
    background->setScale(
        static_cast<float>(windowSize.x) / bgTexture->getSize().x,
        static_cast<float>(windowSize.y) / bgTexture->getSize().y);

    for (size_t i = 0; i < texts.size(); ++i)
    {
        texts[i].setPosition(100.f, 200.f + i * 100.f);
        texts[i].setCharacterSize(50);
    }
    saveKeyBindings();
}