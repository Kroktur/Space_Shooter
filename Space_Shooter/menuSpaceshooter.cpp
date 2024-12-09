#include "menuSpaceshooter.h"
#include "Option.h"

Menu::Menu() 
{
    window = new sf::RenderWindow();
    winclose = new sf::RectangleShape();
    font = new sf::Font();
    image = new sf::Texture();
    menuBackground = new sf::Sprite();
    menuMusic = new sf::Music();

    inMainMenu = true;

    setValues();
}

Menu::~Menu() 
{
    delete window;
    delete winclose;
    delete font;
    delete image;
    delete menuBackground;
    delete menuMusic;
}

void Menu::setValues() 
{
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    window->create(desktopMode, "Menu SFML", sf::Style::Fullscreen);

    float screenWidth = static_cast<float>(desktopMode.width);
    float screenHeight = static_cast<float>(desktopMode.height);

    pos = 0;
    keyHeld = optionSelected = false;

    font->loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");
    image->loadFromFile("C:\\Users\\boulanger\\source\\repos\\Space_Shootertest\\Space_Shooter\\resource\\menuBackground.png");

    menuBackground->setTexture(*image);

    menuBackground->setScale(screenWidth / menuBackground->getTexture()->getSize().x,
        screenHeight / menuBackground->getTexture()->getSize().y);

    pos_mouse = { 0, 0 };
    mouse_coord = { 0, 0 };

    options = { "Spaceship Conqueror", "Play", "Options", "High-Score", "Quit" };
    texts.resize(5);
    coords = { {1115,70},{1270,380},{1235,550},{1200,730},{1270,900} };
    sizes = { 45,55,55,55,55 };

    for (std::size_t i{}; i < texts.size(); ++i) 
    {
        texts[i].setFont(*font);
        texts[i].setString(options[i]);
        texts[i].setCharacterSize(sizes[i]);
        texts[i].setOutlineColor(sf::Color::Blue);
        texts[i].setPosition(coords[i]);
    }

    texts[1].setOutlineThickness(4);
    pos = 1;

    winclose->setSize(sf::Vector2f(screenWidth * 0.02f, screenHeight * 0.03f));
    winclose->setPosition(screenWidth - winclose->getSize().x - 10, 10);
    winclose->setFillColor(sf::Color::Transparent);

    if (!menuMusic->openFromFile("C:\\Users\\boulanger\\source\\repos\\Space_Shootertest\\Space_Shooter\\resource\\menuMusic.mp3")) 
        std::cerr << "Error : Cannot load the music file !\n";
    else 
    {
        menuMusic->setVolume(30.0f);
        menuMusic->setLoop(true);
        menuMusic->play();
    }

    if (!hoverBuffer.loadFromFile("C:\\Users\\boulanger\\source\\repos\\Space_Shootertest\\Space_Shooter\\resource\\hoverSound.wav")) 
        std::cerr << "Error : Cannot load the hover sound !\n";
    if (!clickBuffer.loadFromFile("C:\\Users\\boulanger\\source\\repos\\Space_Shootertest\\Space_Shooter\\resource\\clickSound.wav")) 
        std::cerr << "Error : Cannot load the click sound !\n";

    hoverSound.setBuffer(hoverBuffer);
    clickSound.setBuffer(clickBuffer);
}

void Menu::loopEvents() 
{
    sf::Event event;
    while (window->pollEvent(event)) 
    {
        if (event.type == sf::Event::Closed)
            window->close();

        pos_mouse = sf::Mouse::getPosition(*window);
        mouse_coord = window->mapPixelToCoords(pos_mouse);

        bool soundPlayed = false;
        for (std::size_t i = 0; i < texts.size(); ++i) 
        {
            if (texts[i].getGlobalBounds().contains(mouse_coord)) 
            {
                if (pos != i && !soundPlayed) 
                { 
                    hoverSound.play();
                    soundPlayed = true;
                }
                texts[i].setOutlineThickness(4);
                texts[i].setFillColor(sf::Color::Yellow);
                pos = i;
            }
            else 
            {
                texts[i].setOutlineThickness(0);
                texts[i].setFillColor(sf::Color::Green);
            }
        }

        MouseNav();
        KeyboardNav();

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
            if (winclose->getGlobalBounds().contains(mouse_coord))
                window->close();
    }
}

void Menu::MouseNav()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        for (std::size_t i = 0; i < texts.size(); ++i)
        {
            if (texts[i].getGlobalBounds().contains(mouse_coord))
            {
                clickSound.play();
                std::cout << options[i] << '\n';

                if (options[i] == "Quit")
                    window->close();

                else if (options[i] == "Play")
                    std::cout << "Launching the game :\n";

                else if (options[i] == "Options")
                {
                    inMainMenu = false; 
                    return;             
                }

                else if (options[i] == "High-Score")
                    std::cout << "Showing high scores :\n";
            }
        }
    }
}

void Menu::KeyboardNav() 
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !keyHeld)
    {
        if (pos < 4)
        {
            ++pos;
            keyHeld = true;
            texts[pos].setOutlineThickness(4);
            texts[pos - 1].setOutlineThickness(0);
            keyHeld = false;
            optionSelected = false;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !keyHeld)
    {
        if (pos > 1)
        {
            --pos;
            keyHeld = true;
            texts[pos].setOutlineThickness(4);
            texts[pos + 1].setOutlineThickness(0);
            keyHeld = false;
            optionSelected = false;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !optionSelected)
    {
        optionSelected = true;
        if (pos == 4)
            window->close();
        std::cout << options[pos] << '\n';
    }
}

void Menu::drawAll() 
{
    window->clear();
    window->draw(*menuBackground);
    for (auto t : texts)
        window->draw(t);
    window->display();
}

void Menu::runMenu()
{
    while (window->isOpen())
    {
        if (inMainMenu)
        {
            loopEvents();
            drawAll();
        }
        else
        {
            Option optionsMenu(window);
            optionsMenu.run(); 

            inMainMenu = true; 
        }
    }
}