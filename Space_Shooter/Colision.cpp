#include "Game.h"
#include "playableGameObject.h"


// A enlever 
#include "iostream"
void Game::testColision(IGameObject* A, IGameObject* B)
{
	if (A->gettype() == Type_Ennemie_Ship)
	{
		if (colision(A->GetBoundingBox(), B->GetBoundingBox()) == true)
		{
			/*std::cout << "test";*/
		}
		
	}
		
}

bool Game::colision(AABB& A, AABB& B)
{
	
	std::cout << A.Amax.x << std::endl;
	/*if (A.Amax.x < B.Amin.x || A.Amin.x > B.Amax.x || A.Amax.y < B.Amin.y || A.Amin.y > B.Amax.y)
		return false;
	else 
	return false;*/
	return true;
}
