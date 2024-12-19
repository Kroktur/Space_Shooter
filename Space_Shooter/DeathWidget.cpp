#include "DeathWidget.h"

void DeathWidget::DeathWidgetInit()
{
	Vec2 deathWidgetPos = { static_cast<float>(m_renderwindow->getSize().x / 2),0 + 70 };
	Vec2 sizeOfdeathWidget = { 800, 120 };
	auto deathWidget = new Rectanglewidget(*this, deathWidgetPos, sizeOfdeathWidget, "You're a dead cat!", Title_Widget);
	deathWidget->settextSize(45);
	deathWidget->setTextPosition({ deathWidgetPos.x - 320, deathWidgetPos.y - 25 });
	deathWidget->setcolor(sf::Color(sf::Color::Magenta));
	deathWidget->setTexture("resource\\etiquette.png");
	deathWidget->setFont("resource\\font\\static\\TMT-Paint-Regular.otf");
	deathWidget->GetBoundingBox();
}