#include "Menu.h"

 Menu::Menu(sf::RenderWindow* window, const float& framerate) : SceneBase(window, framerate), m_Background(sf::Vector2f(m_renderwindow->getSize()))
{
	init();
}

 Menu::~Menu()
 {
	 for (auto Object : m_allGameObject)
		 delete Object;
 }

void Menu::init()
{
	playWidgetInit();
	titleWidgetInit();
	optionWidgetInit();
	highscoreWidgetInit();
	quitWidgetInit();

}

void Menu::playWidgetInit()
{
	m_Background.setTexture(&m_texture.getTexture("resource\\Menu.png"));
	Vec2 widgetPlayPos = { static_cast<float>(m_renderwindow->getSize().x / 2),0 + 310 };
	Vec2 sizeOfPlay = { 350, 155 };
	auto play = new Rectanglewidget(*this, widgetPlayPos, sizeOfPlay, "Play", Play_Widget);
	play->settextSize(45);
	play->setTextPosition({ widgetPlayPos.x - 55, widgetPlayPos.y - 25 });
	play->setcolor(sf::Color(sf::Color::Black));
	play->setTexture("resource\\etiquette.png");
	play->setFont("resource\\font\\static\\TMT-Paint-Regular.otf");
}

void Menu::titleWidgetInit()
{
	m_Background.setTexture(&m_texture.getTexture("resource\\Menu.png"));
	Vec2 widgetTitlePos = { static_cast<float>(m_renderwindow->getSize().x / 2),0 + 70 };
	Vec2 sizeOfTitle = { 800, 120 };
	auto play = new Rectanglewidget(*this, widgetTitlePos, sizeOfTitle, "Spaceship Conqueror", Title_Widget);
	play->settextSize(45);
	play->setTextPosition({ widgetTitlePos.x - 320, widgetTitlePos.y - 25 });
	play->setcolor(sf::Color(sf::Color::Black));
	play->setTexture("resource\\etiquette.png");
	play->setFont("resource\\font\\static\\TMT-Paint-Regular.otf");
}

void Menu::optionWidgetInit()
{
	m_Background.setTexture(&m_texture.getTexture("resource\\Menu.png"));
	Vec2 widgetOptionPos = { static_cast<float>(m_renderwindow->getSize().x / 2),0 + 440 };
	Vec2 sizeOfOption = { 350, 155 };
	auto play = new Rectanglewidget(*this, widgetOptionPos, sizeOfOption, "Option", Option_Widget);
	play->settextSize(45);
	play->setTextPosition({ widgetOptionPos.x - 90, widgetOptionPos.y - 25 });
	play->setcolor(sf::Color(sf::Color::Black));
	play->setTexture("resource\\etiquette.png");
	play->setFont("resource\\font\\static\\TMT-Paint-Regular.otf");
}

void Menu::highscoreWidgetInit()
{
	m_Background.setTexture(&m_texture.getTexture("resource\\Menu.png"));
	Vec2 widgetHighscorePos = { static_cast<float>(m_renderwindow->getSize().x / 2),0 + 575 };
	Vec2 sizeOfHighscore = { 350, 155 };
	auto play = new Rectanglewidget(*this, widgetHighscorePos, sizeOfHighscore, "High-Score", Highscore_Widget);
	play->settextSize(45);
	play->setTextPosition({ widgetHighscorePos.x - 165, widgetHighscorePos.y - 25 });
	play->setcolor(sf::Color(sf::Color::Black));
	play->setTexture("resource\\etiquette.png");
	play->setFont("resource\\font\\static\\TMT-Paint-Regular.otf");
}

void Menu::quitWidgetInit()
{
	m_Background.setTexture(&m_texture.getTexture("resource\\Menu.png"));
	Vec2 widgetQuitPos = { static_cast<float>(m_renderwindow->getSize().x / 2),0 + 705 };
	Vec2 sizeOfQuit = { 350, 155 };
	auto play = new Rectanglewidget(*this, widgetQuitPos, sizeOfQuit, "Quit", Quit_Widget);
	play->settextSize(45);
	play->setTextPosition({ widgetQuitPos.x - 55, widgetQuitPos.y - 25 });
	play->setcolor(sf::Color(sf::Color::Black));
	play->setTexture("resource\\etiquette.png");
	play->setFont("resource\\font\\static\\TMT-Paint-Regular.otf");
}

void Menu::processInput(sf::Event& event)
{
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
