#include "MyMath.h"
#include "playableGameObject.h"

void updateBallWithNumericalIntegration(Boule& boule, float totalTime, float deltaTime)
{
	boule.position += boule.vitesse * deltaTime;
	Vec2 acceleration{ 0.f, -g() };
	boule.vitesse += acceleration * deltaTime;
}