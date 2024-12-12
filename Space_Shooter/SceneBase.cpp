#include "SceneBase.h"

inline SceneBase::SceneBase(sf::RenderWindow* window, const float& framerate) : m_renderwindow(window) , m_refreshTime(sf::seconds(1.f / framerate))
{
	
}
