#include "MyMath.h"
#include "playableGameObject.h"

constexpr float  g()
{
	return -9.81*100;
}

void Ship::updatePhysique(float deltaTime)
{
	if (isTurningLeft)
		m_angle -= 10.f;
	if (isTurningRight)
		m_angle += 10.f;

	if (!isAccelerating)
		m_acceleration = -0.8f * m_velocity;
	if (isAccelerating)
		m_acceleration += Vec2{ std::cos(m_angle - 3.14f / 2.f),std::sin(m_angle - 3.14f / 2.f) }*100;

	

	if (m_velocity.getlenght() > 200)
		m_velocity = m_velocity * (200 / m_velocity.getlenght());

	m_velocity += m_acceleration * deltaTime;


	m_position += m_velocity * deltaTime;
	m_totalTime = m_totalTime + deltaTime;
	
	float friction = 0.01f;
	
	if (m_velocity.getlenght() > 0.01f)
	{
		m_velocity = m_velocity * (1.0f - friction);
	}

	else
	{
		m_velocity = Vec2(0.0f, 0.0f);
	}

}


