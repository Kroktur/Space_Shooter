#pragma once
#include "IGameObject.h"
#include "Game.h"

#include<vector>
class Iinput;
class PlayerInput;
class IaInput;
class Ship : public IGameObject
{
public:
	friend PlayerInput;
	Ship(Game& game);
	~Ship();
	void setShip();
	void anglecalcul();
	void input(sf::Event event) override;
	void update(float deltatime)override;
	void render() override;
	int& gettype() override;
	void resetmooveposition();
	AABB GetBoundingBox() override;
	void updateGravityIntegration(Ship& ship, float totalTime, float deltaTime);
	void updatePhysique(float deltaTime);

		///////////physique
	Vec2 getPlayerShipSize() { return{ 32.f, 32.f }; }
	float getPlayerShipThrust() { return 400.f; }
	float getPlayerShipMaxVelocity();
	///////////////
	sf::CircleShape& getcircle();
	void TakeDomage(int num = 1, int score = 0);


private:

	sf::CircleShape m_ship;
	sf::Vector2f m_moove;
	Vec2 m_position{ m_game.getWindowSize().x / 2.f, m_game.getWindowSize().y / 2.f };
	float m_angle;
	Vec2 m_velocity{ 0.f, 0.f };
	Vec2 m_acceleration{ 0.f, 0.f };
	float m_maxVelocity;
	float m_rotationSpeed = 180.f;

	Iinput* m_input;

	bool m_fire;
	const float m_firerate;
	sf::Clock m_clock;
	sf::Time m_elapsedTime;

	bool m_isAccelerating = false;
	bool m_isTurningLeft = false;
	bool m_isTurningRight = false;

};
class EnemieShip : public IGameObject
{
public:
	friend IaInput;
	EnemieShip(Game& game, sf::CircleShape& circle);
	~EnemieShip();
	void setennemie();
	void input(sf::Event event) override;
	void update(float deltatime)override;
	void render() override;
	int& gettype() override;
	void resetmooveposition();
	void deltapositin();
	void anglecalcul();
	AABB GetBoundingBox() override;
	void TakeDomage(int num = 1, int score = 0);
private:


	sf::Vector2f m_delta;
	sf::CircleShape m_ennemie;
	sf::CircleShape& m_ship;
	sf::Vector2f m_moove;
	float m_angle;
	Iinput* m_input;

	bool m_fire;
	const float m_firerate;
	sf::Clock m_clock;
	sf::Time m_elapsedTime;


};

class Missile : public IGameObject
{
public:
	Missile(Game& game, sf::CircleShape& circle, const int& type);
	void set();
	void input(sf::Event event) override;
	void update(float deltatime)override;
	void render() override;
	int& gettype() override;
	AABB GetBoundingBox() override;
	void TakeDomage(int num = 1, int score = 0);
private:


		float m_angle;
	sf::RectangleShape m_missile;
	sf::Vector2f m_moove;
	float m_velocity;
	sf::CircleShape& m_shape;


};
class Barrier : public IGameObject
{
public:
	Barrier(Game& game, Vec2& Centre, float distance, int Size_, int Position, int forwhat = 0);
	void initBarrer();
	void input(sf::Event event);
	void update(float deltatime);
	void render();
	int& gettype();
	AABB GetBoundingBox();
	void TakeDomage(int num = 1, int score = 0);

private:
	Vec2 Amin;
	Vec2 Amax;
	Vec2& m_Centre;
	float& m_Distance;
	int& m_position;
	int& m_Size;
	sf::RectangleShape m_Barrier;

};
class Asteroid : public IGameObject
{
public:
	Asteroid(Game& game);
	~Asteroid();
	void initAsteroid();
	void input(sf::Event event);
	void update(float deltatime);
	void render();
	int& gettype();
	AABB GetBoundingBox();
	void TakeDomage(int num = 1, int score = 0);
private:

	float m_velocity;
	float m_angle;

	sf::CircleShape m_Asteroid;
	sf::Vector2f m_moove;


};