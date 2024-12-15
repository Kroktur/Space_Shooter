#include "Game.h"
#include "playableGameObject.h"


// A enlever 
#include "iostream"
void Game::testColision(IGameObject* A, IGameObject* B)
{
	
		if (colision(A->GetBoundingBox(), B->GetBoundingBox()) == true)
		{
			if ((A->gettype() == Type_Missile && B->gettype() == Type_Ennemie_Ship)
				|| (A->gettype() == Type_Ennemie_Ship && B->gettype() == Type_Missile))
			{
				/*A->TakeDomage();
				B->TakeDomage();*/
			}
			if ((A->gettype() == Type_Ship && B->gettype() == Type_Ennemie_Ship)
					|| (A->gettype() == Type_Ennemie_Ship && B->gettype() == Type_Ship))
			{
					std::cout << "enemie colision me";
			}
			if ((A->gettype() == Type_Ennemie_Missile && B->gettype() == Type_Ship)
				|| (A->gettype() == Type_Ship && B->gettype() == Type_Ennemie_Missile))
			{
				std::cout << "ennemie touched me";
			}

		}
		
	
		
}

bool Game::colision(AABB A, AABB B)
{
	
	
	if (A.Amax.x < B.Amin.x || A.Amin.x > B.Amax.x || A.Amax.y < B.Amin.y || A.Amin.y > B.Amax.y)
		return false;
	else 
	return true;
}
