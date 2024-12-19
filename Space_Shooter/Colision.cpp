#include "Game.h"
#include "playableGameObject.h"



void Game::testColision(IGameObject* A, IGameObject* B)
{
	//allway destroy the lives  
	if ((A->gettype() == Type_Live))
	{
		A->TakeDomage();
		
	}
	if ((B->gettype() == Type_Live))
	{
		B->TakeDomage();

	}

		if (colision(A->GetBoundingBox(), B->GetBoundingBox()) == true)
		{
			// i touched Enemy
			if ((A->gettype() == Type_Missile && B->gettype() == Type_Ennemie_Ship))
			{
				A->TakeDomage();
				B->TakeDomage(1, m_scorebase);
			}
			if ((A->gettype() == Type_Ennemie_Ship && B->gettype() == Type_Missile))
			{
				A->TakeDomage(1, m_scorebase);
				B->TakeDomage();
			}
			// enemy colision me
			if ((A->gettype() == Type_Ship && B->gettype() == Type_Ennemie_Ship))
			{
				A->TakeDomage();
				B->TakeDomage(1, -m_scorebase);
			}
			if ((A->gettype() == Type_Ennemie_Ship && B->gettype() == Type_Ship))
			{
				A->TakeDomage(1, -m_scorebase);
				B->TakeDomage();
			}
			//enemy touched me
			if ((A->gettype() == Type_Ennemie_Missile && B->gettype() == Type_Ship))
			{
				A->TakeDomage(1, -m_scorebase);
				B->TakeDomage();
			}
			if ((A->gettype() == Type_Ship && B->gettype() == Type_Ennemie_Missile))
			{
				A->TakeDomage();
				B->TakeDomage(1, -m_scorebase);
			}
			//Missile against Missile
			if ((A->gettype() == Type_Ennemie_Missile && B->gettype() == Type_Missile))
			{
				A->TakeDomage();
				B->TakeDomage();
			}
			if ((A->gettype() == Type_Missile && B->gettype() == Type_Ennemie_Missile))
			{
				A->TakeDomage();
				B->TakeDomage();
			}
			//Barrier
			if ((A->gettype() == Type_Barrier )
				|| ( B->gettype() == Type_Barrier))
			{
				A->TakeDomage(10000,0);
				B->TakeDomage(10000,0);
				
			}
			//Barrier spatial missile
			if ((A->gettype() == Type_Barrier_Only_Misssile && B->gettype() == Type_Missile)
				|| (A->gettype() == Type_Missile && B->gettype() == Type_Barrier_Only_Misssile))
			{
				A->TakeDomage();
				B->TakeDomage();
			}
			//Barrier spatial Ennemie missile
			if ((A->gettype() == Type_Barrier_Only_Misssile && B->gettype() == Type_Ennemie_Missile)
				|| (A->gettype() == Type_Ennemie_Missile && B->gettype() == Type_Barrier_Only_Misssile))
			{
				A->TakeDomage();
				B->TakeDomage();
			}
			//Barrier spatial Fox boss missile
			if ((A->gettype() == Type_Barrier_Only_Misssile && B->gettype() == Type_FoxMissille)
				|| (A->gettype() == Type_FoxMissille && B->gettype() == Type_Barrier_Only_Misssile))
			{
				A->TakeDomage(100,0);
				B->TakeDomage(100, 0);
			}
			//Asteroid against Missile
			if ((A->gettype() == Type_Asteroid && B->gettype() == Type_Missile))
			{
				A->TakeDomage(1,m_scorebase);
				B->TakeDomage();	
			}
			if ((A->gettype() == Type_Missile && B->gettype() == Type_Asteroid))
			{
				A->TakeDomage();
				B->TakeDomage(1,m_scorebase);
			}
			//Asteroid against Ship
			if ((A->gettype() == Type_Asteroid && B->gettype() == Type_Ship))
			{
				A->TakeDomage(1, -m_scorebase);
				B->TakeDomage();
			
			}
			if ((A->gettype() == Type_Ship && B->gettype() == Type_Asteroid))
			{
				A->TakeDomage();
				B->TakeDomage(1, -m_scorebase);

			}
			//Asteroid against Enemy Missile
			if ((A->gettype() == Type_Asteroid && B->gettype() == Type_Ennemie_Missile)
				|| (A->gettype() == Type_Ennemie_Missile && B->gettype() == Type_Asteroid))
			{
				A->TakeDomage();
				B->TakeDomage();
			
			}
			//Asteroid against Ennemie Ship
			if ((A->gettype() == Type_Asteroid && B->gettype() == Type_Ennemie_Ship)
				|| (A->gettype() == Type_Ennemie_Ship && B->gettype() == Type_Asteroid))
			{
				A->TakeDomage();
				B->TakeDomage();
				
			}
			//comets against Missile
			if ((A->gettype() == Type_Commette && B->gettype() == Type_Missile))
			{
				A->TakeDomage(1, m_scorebase);
				B->TakeDomage();
			}
			if ((A->gettype() == Type_Missile && B->gettype() == Type_Commette))
			{
				A->TakeDomage();
				B->TakeDomage(1, m_scorebase);
			}
			//comets against Ship
			if ((A->gettype() == Type_Commette && B->gettype() == Type_Ship))
			{
				A->TakeDomage(1, -m_scorebase);
				B->TakeDomage();

			}
			if ((A->gettype() == Type_Ship && B->gettype() == Type_Commette))
			{
				A->TakeDomage();
				B->TakeDomage(1, -m_scorebase);

			}
			//comets against Ennemie Missile
			if ((A->gettype() == Type_Commette && B->gettype() == Type_Ennemie_Missile)
				|| (A->gettype() == Type_Ennemie_Missile && B->gettype() == Type_Commette))
			{
				A->TakeDomage();
				B->TakeDomage();

			}
			//comets against Ennemie Ship
			if ((A->gettype() == Type_Commette && B->gettype() == Type_Ennemie_Ship)
				|| (A->gettype() == Type_Ennemie_Ship && B->gettype() == Type_Commette))
			{
				A->TakeDomage();
				B->TakeDomage();

			}
			//missile against fox boss
			if ((A->gettype() == Type_BossFox && B->gettype() == Type_Missile))
			{
				A->TakeDomage(1, m_scorebase);
				B->TakeDomage();
			}
			if ((A->gettype() == Type_Missile && B->gettype() == Type_BossFox))
			{
				A->TakeDomage();
				B->TakeDomage(1, m_scorebase);
			}
			//player against fox boss
			if ((A->gettype() == Type_BossFox && B->gettype() == Type_Ship))
			{
				A->TakeDomage(1, -m_scorebase);
				B->TakeDomage();
			}
			if ((A->gettype() == Type_Ship && B->gettype() == Type_BossFox))
			{
				A->TakeDomage();
				B->TakeDomage(1, -m_scorebase);
			}
			//missile againsst missile fox boss
			if ((A->gettype() == Type_FoxMissille && B->gettype() == Type_Missile))
			{
				A->TakeDomage();
				B->TakeDomage();
			}
			if ((A->gettype() == Type_Missile && B->gettype() == Type_FoxMissille))
			{
				A->TakeDomage();
				B->TakeDomage();
			}
			//Player against missile fox boss
			if ((A->gettype() == Type_FoxMissille && B->gettype() == Type_Ship))
			{
				A->TakeDomage(1, -m_scorebase);
				B->TakeDomage();
			}
			if ((A->gettype() == Type_Ship && B->gettype() == Type_FoxMissille))
			{
				A->TakeDomage();
				B->TakeDomage(1, -m_scorebase);
			}

			//player against fox boss
			if ((A->gettype() == Type_BossFox && B->gettype() == Type_Ennemie_Ship))
			{
				A->TakeDomage(1, -m_scorebase);
				B->TakeDomage();
			}
			if ((A->gettype() == Type_Ennemie_Ship && B->gettype() == Type_BossFox))
			{
				A->TakeDomage();
				B->TakeDomage();
			}
		}
		
	
		
}

bool Game::colision(AABB A, AABB B)
{	
	if (A.Amax.x <= B.Amin.x || A.Amin.x >= B.Amax.x || A.Amax.y <= B.Amin.y || A.Amin.y >= B.Amax.y)
		return false;
	else 
	return true;
}
