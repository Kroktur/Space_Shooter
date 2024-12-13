#include "IGameObject.h"
#include "Game.h"

IGameObject::IGameObject(Game& game) : m_game(game)
{
	game.m_goingtoaddGameObject.push_back(this);

}
