#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "SceneBase.h"
#include "IGameObject.h"
#include "MyMath.h"
#include "playableGameObject.h"
#include "Input.h"
#include "MyMath.h"
#include "WidgetGameObject.h"

class DeathWidget : public SceneBase
{
	DeathWidget();
	~DeathWidget();
	void DeathWidgetInit();

};

