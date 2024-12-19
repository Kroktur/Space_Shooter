#include "Menu.h"

 Menu::Menu(sf::RenderWindow* window, const float& framerate) : SceneBase(window, framerate), m_Background(sf::Vector2f(m_renderwindow->getSize()))
{
	 m_Background.setTexture(&m_texture.getTexture("resource\\Menu.png"));
	 init();
}

 Menu::~Menu()
 {
	 for (auto Object : m_allGameObject)
		 delete Object;
	 delete menuMusic;
 }

void Menu::init()
{
	MusicInit();
	SoundInit();
	playWidgetInit();
	titleWidgetInit();
	optionWidgetInit();
	highscoreWidgetInit();
	quitWidgetInit();
}

void Menu::MusicInit()
{
	menuMusic = new sf::Music();
	if(!menuMusic->openFromFile("resource\\menuMusic.mp3"))
		std::cerr << "Error : Cannot load the music file !\n";
	else
		menuMusic->setVolume(100.0f);
		menuMusic->setLoop(true);
		menuMusic->play();
}

void Menu::SoundInit()
{
	if (!hoverBuffer.loadFromFile("C:\\Users\\boulanger\\source\\repos\\Space_Shootertest\\Space_Shooter\\resource\\hoverSound.wav"))
		std::cerr << "Error : Cannot load the hover sound !\n";
	if (!clickBuffer.loadFromFile("C:\\Users\\boulanger\\source\\repos\\Space_Shootertest\\Space_Shooter\\resource\\clickSound.wav"))
		std::cerr << "Error : Cannot load the click sound !\n";

	hoverSound.setBuffer(hoverBuffer);
	clickSound.setBuffer(clickBuffer);
}

void Menu::processInput(sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2f mousePos = m_renderwindow->mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });

		for (auto Object : m_allGameObject)
		{
			
		}
	}
}


void Menu::update(const float& deltaTime)
{
	addObject();
	for (auto Object : m_allGameObject)
	{
		Object->update(deltaTime);
	}
	deleteObject();
	
}

void Menu::render()
{
	m_renderwindow->draw(m_Background);
	for (auto Object : m_allGameObject)
	{
		Object->render();
	}
}

void Menu::playWidgetInit()
{
	Vec2 widgetPlayPos = { static_cast<float>(m_renderwindow->getSize().x / 2),0 + 310 };
	Vec2 sizeOfPlay = { 350, 155 };
	auto play = new Rectanglewidget(*this, widgetPlayPos, sizeOfPlay, "Play", Play_Widget);
	play->settextSize(45);
	play->setTextPosition({ widgetPlayPos.x - 55, widgetPlayPos.y - 25 });
	play->setcolor(sf::Color(sf::Color::Blue));
	play->setTexture("resource\\etiquette.png");
	play->setFont("resource\\font\\static\\TMT-Paint-Regular.otf");
	play->GetBoundingBox();

}

void Menu::titleWidgetInit()
{
	Vec2 widgetTitlePos = { static_cast<float>(m_renderwindow->getSize().x / 2),0 + 70 };
	Vec2 sizeOfTitle = { 800, 120 };
	auto menuTitle = new Rectanglewidget(*this, widgetTitlePos, sizeOfTitle, "Spaceship Conqueror", Title_Widget);
	menuTitle->settextSize(45);
	menuTitle->setTextPosition({ widgetTitlePos.x - 320, widgetTitlePos.y - 25 });
	menuTitle->setcolor(sf::Color(sf::Color::Magenta));
	menuTitle->setTexture("resource\\etiquette.png");
	menuTitle->setFont("resource\\font\\static\\TMT-Paint-Regular.otf");
	menuTitle->GetBoundingBox();
}

void Menu::optionWidgetInit()
{
	Vec2 widgetOptionPos = { static_cast<float>(m_renderwindow->getSize().x / 2),0 + 440 };
	Vec2 sizeOfOption = { 350, 155 };
	auto option = new Rectanglewidget(*this, widgetOptionPos, sizeOfOption, "Option", Option_Widget);
	option->settextSize(45);
	option->setTextPosition({ widgetOptionPos.x - 90, widgetOptionPos.y - 25 });
	option->setcolor(sf::Color(sf::Color::Blue));
	option->setTexture("resource\\etiquette.png");
	option->setFont("resource\\font\\static\\TMT-Paint-Regular.otf");
	option->GetBoundingBox();
}

void Menu::highscoreWidgetInit()
{
	Vec2 widgetHighscorePos = { static_cast<float>(m_renderwindow->getSize().x / 2),0 + 575 };
	Vec2 sizeOfHighscore = { 350, 155 };
	auto highscore = new Rectanglewidget(*this, widgetHighscorePos, sizeOfHighscore, "High-Score", Highscore_Widget);
	highscore->settextSize(45);
	highscore->setTextPosition({ widgetHighscorePos.x - 165, widgetHighscorePos.y - 25 });
	highscore->setcolor(sf::Color(sf::Color::Blue));
	highscore->setTexture("resource\\etiquette.png");
	highscore->setFont("resource\\font\\static\\TMT-Paint-Regular.otf");
	highscore->GetBoundingBox();
}

void Menu::quitWidgetInit()
{
	Vec2 widgetQuitPos = { static_cast<float>(m_renderwindow->getSize().x / 2),0 + 705 };
	Vec2 sizeOfQuit = { 350, 155 };
	auto quit = new Rectanglewidget(*this, widgetQuitPos, sizeOfQuit, "Quit", Quit_Widget);
	quit->settextSize(45);
	quit->setTextPosition({ widgetQuitPos.x - 55, widgetQuitPos.y - 25 });
	quit->setcolor(sf::Color(sf::Color::Blue));
	quit->setTexture("resource\\etiquette.png");
	quit->setFont("resource\\font\\static\\TMT-Paint-Regular.otf");
	quit->GetBoundingBox();
	quit->GetBoundingBox();
}

//void Menu::MouseNav()
//{
//	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
//	{
//		if ()
//	}
//}

//void Menu::MouseNav()
//{
//	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
//	{
//		for (std::size_t i = 0; i < texts.size(); ++i)
//		{
//			if (texts[i].getGlobalBounds().contains(mouse_coord))
//			{
//				clickSound.play();
//				std::cout << options[i] << '\n';
//
//				if (options[i] == "Quit")
//					window->close();
//
//				else if (options[i] == "Play")
//					std::cout << "Launching the game :\n";
//
//				else if (options[i] == "Options")
//				{
//					inMainMenu = false;
//					return;
//				}
//
//				else if (options[i] == "High-Score")
//				{
//					inMainMenu = false;
//					inHighScoreMenu = true;
//				}
//
//			}
//		}
//	}
//}
