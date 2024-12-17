#include "IGameObject.h"
#include "Game.h"

IGameObject::~IGameObject()
{


}

IGameObject::IGameObject(Game& game) : m_game(game) , m_score(0)

{
	m_game.m_tobeaddGameObject.push_back(this);
	
}
