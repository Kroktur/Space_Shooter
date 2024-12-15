#include "IGameObject.h"
#include "Game.h"

IGameObject::~IGameObject()
{
	m_game.m_toberemovedGameObject.push_back(this);
}

IGameObject::IGameObject(Game& game) : m_game(game)
{
	m_game.m_tobeaddGameObject.push_back(this);

}
