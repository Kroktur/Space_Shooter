#include "MyMath.h"
#include "playableGameObject.h"

void Ship::updatePhysique(float deltatime)
{
	if (isTurningLeft)
		m_angle -= 30.f;
	if (isTurningRight)
		m_angle += 0.05f;

	if (!isAccelerating)
		acceleration = 300.f * m_velocity;
	if (isAccelerating)
		acceleration += Vec2{ std::cos(m_angle - 3.14f / 2.f),std::sin(m_angle - 3.14f / 2.f) }*100;

	m_position += m_velocity * deltatime;
	if (m_velocity.getlenght() > 200)
		m_velocity = m_velocity * (200 / m_velocity.getlenght());
}