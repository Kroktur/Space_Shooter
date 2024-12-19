#include "OptionMenu.h"


OptionMenu::OptionMenu(sf::RenderWindow* window, const float& framerate) : SceneBase(window, framerate), m_Background(sf::Vector2f(m_renderwindow->getSize()))
{
	m_Background.setTexture(&m_texture.getTexture("resource\\galaxie2.bmp"));
	init();
}

OptionMenu::~OptionMenu()
{
	for (auto Object : m_allGameObject)
		delete Object;
}

void OptionMenu::init()
{
	titleOptionWidgetInit();
	resolutionWidgetInit();
	controlsWidgetInit();
	backWidgetInit();

}

void OptionMenu::titleOptionWidgetInit()
{
	Vec2 widgetControlsPos = { static_cast<float>(m_renderwindow->getSize().x / 2),0 + 100 };
	Vec2 sizeOfControls = { 800, 120 };
	auto play = new Rectanglewidget(*this, widgetControlsPos, sizeOfControls, "Options", Title_Widget);
	play->settextSize(45);
	play->setTextPosition({ widgetControlsPos.x - 130, widgetControlsPos.y - 25 });
	play->setcolor(sf::Color(sf::Color::Magenta));
	play->setTexture("resource\\etiquette.png");
	play->setFont("resource\\font\\static\\TMT-Paint-Regular.otf");
}

void OptionMenu::resolutionWidgetInit()
{
	Vec2 widgetResolutionPos = { static_cast<float>(m_renderwindow->getSize().x / 2),0 + 350 };
	Vec2 sizeOfResolution = { 450, 155 };
	auto play = new Rectanglewidget(*this, widgetResolutionPos, sizeOfResolution, "Resolution", Play_Widget);
	play->settextSize(45);
	play->setTextPosition({ widgetResolutionPos.x - 160, widgetResolutionPos.y - 25 });
	play->setcolor(sf::Color(sf::Color::Blue));
	play->setTexture("resource\\etiquette.png");
	play->setFont("resource\\font\\static\\TMT-Paint-Regular.otf");
}

void OptionMenu::controlsWidgetInit()
{
	Vec2 widgetControlsPos = { static_cast<float>(m_renderwindow->getSize().x / 2),0 + 600 };
	Vec2 sizeOfControls = { 450, 155 };
	auto play = new Rectanglewidget(*this, widgetControlsPos, sizeOfControls, "Controls", Title_Widget);
	play->settextSize(45);
	play->setTextPosition({ widgetControlsPos.x - 130, widgetControlsPos.y - 25 });
	play->setcolor(sf::Color(sf::Color::Blue));
	play->setTexture("resource\\etiquette.png");
	play->setFont("resource\\font\\static\\TMT-Paint-Regular.otf");
}

void OptionMenu::backWidgetInit()
{
	Vec2 widgetBackPos = { static_cast<float>(m_renderwindow->getSize().x / 2),0 + 850 };
	Vec2 sizeOfBack = { 450, 155 };
	auto play = new Rectanglewidget(*this, widgetBackPos, sizeOfBack, "Back", Quit_Widget);
	play->settextSize(45);
	play->setTextPosition({ widgetBackPos.x - 55, widgetBackPos.y - 25 });
	play->setcolor(sf::Color(sf::Color::Blue));
	play->setTexture("resource\\etiquette.png");
	play->setFont("resource\\font\\static\\TMT-Paint-Regular.otf");
}

void OptionMenu::processInput(sf::Event& event)
{
}

void OptionMenu::update(const float& deltaTime)
{
	addObject();
	for (auto Object : m_allGameObject)
	{
		Object->update(deltaTime);
	}
	deleteObject();

}

void OptionMenu::render()
{
	m_renderwindow->draw(m_Background);
	for (auto Object : m_allGameObject)
	{
		Object->render();
	}
}