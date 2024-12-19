#include "Menu.h"

 Menu::Menu(sf::RenderWindow* window, const float& framerate) : SceneBase(window, framerate), m_Background(sf::Vector2f(m_renderwindow->getSize()))
{
	 m_Background.setTexture(&m_texture.getTexture("resource\\Menu.png"));
	init();
}

void Menu::init()
{




}

void Menu::processInput(sf::Event& event)
{
}

void Menu::update(const float& deltaTime)
{
}

void Menu::render()
{
	m_renderwindow->draw(m_Background);
	for (auto Object : m_allGameObject)
	{
		Object->render();
	}
}
