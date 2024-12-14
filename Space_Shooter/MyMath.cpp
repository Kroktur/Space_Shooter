#include "MyMath.h"
#include <cmath>

int Randomnumber::getrandomnumber(int min, int max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(min, max);
	return dis(gen);
}

Vec2::Vec2(float x_, float y_) : x(x_), y(y_) {}

AABB::AABB(Vec2 Amin_, Vec2 Amax) : Amin(Amin_), Amax(Amax){}

