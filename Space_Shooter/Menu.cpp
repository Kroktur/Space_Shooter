#include "Menu.h"
#include "WidgetGameObject.h"
 Menu::Menu(sf::RenderWindow* window, const float& framerate) : SceneBase(window, framerate)
{
	 m_Background.setSize(sf::Vector2f(m_renderwindow->getSize()));
	 m_Background.setTexture(&m_texture.getTexture("resource\\Menu.png"));
	init();
}

 Menu::~Menu()
 {
	 for (auto Object : m_allGameObject)
		delete Object;
 }

void Menu::init()
{



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
