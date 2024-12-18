#pragma once
#include <random>
#include <ctime>
#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>

struct  Vec2
{
	Vec2(float x_ = 0, float y_ = 0);
	float x;
	float y;

	float getlenght();
	Vec2& operator+=(const Vec2& op1);
	Vec2& operator-=(const Vec2& op1);

};

Vec2 operator+(const Vec2& op1, const Vec2& op2);
Vec2 operator-(const Vec2& op1, const Vec2& op2);
Vec2 operator/(const Vec2& op1, const float& op2);
Vec2 operator*(const Vec2& op1, const float& op2);
Vec2 operator*(const float& op1, const Vec2& op2);


struct AABB
{
	AABB(Vec2 Amin_, Vec2 Amax);
	Vec2 Amin;
	Vec2 Amax;
};



class Randomnumber
{
public:
	int getrandomnumber(int min, int max);
};
class RandomSpawn
{

public:
	RandomSpawn(Vec2 Min, Vec2 Max);
	sf::Vector2f m_spawnCordonate();

private:
	Randomnumber m_rand;
	Vec2 m_Min;
	Vec2 m_Max;
};



