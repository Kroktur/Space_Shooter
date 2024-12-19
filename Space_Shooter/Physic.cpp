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

	m_acceleration = Vec2(0.0f, 0.0f);

	if (isAccelerating)
		m_acceleration += Vec2{ std::cos(m_angle - 3.14f / 2.f),std::sin(m_angle - 3.14f / 2.f) }*100;
	if (!isAccelerating)
		m_acceleration = 10.f * m_velocity;

	if (!isTurningLeft)
		m_acceleration = 10.f * m_velocity;
	if (!isTurningRight)
		m_acceleration = 10.f * m_velocity;

	m_velocity += m_acceleration * deltaTime;
	m_position += m_velocity * deltaTime;

	if (m_velocity.getlenght() > 200)
		m_velocity = m_velocity * (200 / m_velocity.getlenght());

	else if (m_velocity.getlenght() < 0.01f)
	{
		m_velocity = Vec2(0.0f, 0.0f);
	}

}

