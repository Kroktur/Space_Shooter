#include "SceneBase.h"

SceneBase::SceneBase(sf::RenderWindow* window, const float& framerate) : m_renderwindow(window) , m_refreshTime(sf::seconds(1.f / framerate)) , m_totalscore(0)
{
	
}

sf::Time SceneBase::getRefreshTime() const
{
	return m_refreshTime;
}

TextureCache& SceneBase::gettexture()
{
	return m_texture;
}

FontCache& SceneBase::getfont()
{
	return m_font;
}
