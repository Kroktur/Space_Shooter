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
			// i touched Ennemie
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
			// enemie colision me
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
			//ennemie touched me
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
			//Barrier spetial missile
			if ((A->gettype() == Type_Barrier_Only_Misssile && B->gettype() == Type_Missile)
				|| (A->gettype() == Type_Missile && B->gettype() == Type_Barrier_Only_Misssile))
			{
				A->TakeDomage();
				B->TakeDomage();
			}
			//Barrier spetial Ennemie missile
			if ((A->gettype() == Type_Barrier_Only_Misssile && B->gettype() == Type_Ennemie_Missile)
				|| (A->gettype() == Type_Ennemie_Missile && B->gettype() == Type_Barrier_Only_Misssile))
			{
				A->TakeDomage();
				B->TakeDomage();
			}
			//Barrier spetial Fox boss missile
			if ((A->gettype() == Type_Barrier_Only_Misssile && B->gettype() == Yype_FoxMissille)
				|| (A->gettype() == Yype_FoxMissille && B->gettype() == Type_Barrier_Only_Misssile))
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
			//Asteroid against Ennemie Missile
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
			//Commette against Missile
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
			//Commette against Ship
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
			//Commette against Ennemie Missile
			if ((A->gettype() == Type_Commette && B->gettype() == Type_Ennemie_Missile)
				|| (A->gettype() == Type_Ennemie_Missile && B->gettype() == Type_Commette))
			{
				A->TakeDomage();
				B->TakeDomage();

			}
			//Commette against Ennemie Ship
			if ((A->gettype() == Type_Commette && B->gettype() == Type_Ennemie_Ship)
				|| (A->gettype() == Type_Ennemie_Ship && B->gettype() == Type_Commette))
			{
				A->TakeDomage();
				B->TakeDomage();

			}
			//missile againsst bossfox
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
			//player against bossfox
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
			if ((A->gettype() == Yype_FoxMissille && B->gettype() == Type_Missile))
			{
				A->TakeDomage();
				B->TakeDomage();
			}
			if ((A->gettype() == Type_Missile && B->gettype() == Yype_FoxMissille))
			{
				A->TakeDomage();
				B->TakeDomage();
			}
			//Plyer againsst missile fox boss
			if ((A->gettype() == Yype_FoxMissille && B->gettype() == Type_Ship))
			{
				A->TakeDomage(1, -m_scorebase);
				B->TakeDomage();
			}
			if ((A->gettype() == Type_Ship && B->gettype() == Yype_FoxMissille))
			{
				A->TakeDomage();
				B->TakeDomage(1, -m_scorebase);
			}

			//player against bossfox
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
