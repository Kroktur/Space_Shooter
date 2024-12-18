#include "MyMath.h"
#include "playableGameObject.h"


constexpr float  g()
{
	return -9.81f * 100.f;
}

void Ship::updateGravityIntegration(Ship& ship, float totalTime, float deltaTime)
{
    ship.m_position += ship.m_velocity * deltaTime; 
	Vec2 acceleration{ 0.f, -g() };
	ship.m_velocity += acceleration * deltaTime;
}


void Ship::updatePhysique(float deltaTime)
{
	float accelerationFactor = getPlayerShipThrust() * deltaTime;

    Vec2 acceleration{ 0.f, 0.f };

    if (m_isAccelerating) 
    {
        float angle_rad = m_angle * (3.14159265359f / 180.f);
        acceleration += Vec2{ std::cos(angle_rad), std::sin(angle_rad) };
    }

    if (m_isTurningLeft) 
    {
        m_angle -= m_rotationSpeed * deltaTime;
    }
    if (m_isTurningRight) 
    {
        m_angle += m_rotationSpeed * deltaTime;
    }

    Vec2 friction = -m_velocity * 0.1f;

    m_velocity += (acceleration + friction) * deltaTime;
      
    if (m_velocity.dotProduct(m_velocity,m_velocity) > m_maxVelocity)
    {
        m_velocity = normalize(m_velocity) * m_maxVelocity;
    }

    m_position += m_velocity * deltaTime;

    m_ship.setPosition(m_position.x, m_position.y);
    m_ship.setRotation(m_angle);

    const int fps = 500;
    const float deltatime = 1.f / static_cast<float>(fps);

    float totalTime = 0.f;
    
    Vec2 gravity{ 0.f, g() };
    acceleration += gravity;

}

float Ship::getPlayerShipMaxVelocity()
{
    return m_maxVelocity;
}
