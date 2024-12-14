#pragma once
#include <random>
#include <ctime>
struct  Vec2
{
    Vec2(float x_ = 0, float y_ = 0);

    float x;
    float y;
};
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
