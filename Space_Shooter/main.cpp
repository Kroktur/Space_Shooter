//#include <iostream>
//#include <SFML/Graphics.hpp>
//struct Vec2
//{
//	Vec2(float x_, float y_): x(x_), y(y_){}
//	float x;
//	float y;
//};
//struct Boule 
//{
//	Boule(Vec2& position_ , Vec2& vitesse_): position(position_), vitesse(vitesse_){}
//	Vec2 position;
//	Vec2 vitesse;
//
//};
//
//int main()
//{
//	auto framerate = 60;
//	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
//	sf::CircleShape circle;
//	window.setFramerateLimit(framerate);
//	float time = 0;
//	
//	while (window.isOpen())
//	{
//		sf::Event event;
//		window.clear();
//		// process input 
//
//
//		//update
//		if ()
//		{
//
//
//
//		}
//
//
//		//render
//        
//		window.display();
//		time += 1 / framerate;
//	}
//
//}
#include <SFML/Graphics.hpp>
constexpr float  g()
{
    return -981;
}
struct Vec2
{
    Vec2(float x_, float y_);

    float x;
    float y;

    Vec2& operator+=(const Vec2& op2);
};

Vec2 operator+(const Vec2& op1, const Vec2& op2);
Vec2 operator-(const Vec2& op1, const Vec2& op2);
Vec2 operator/(const Vec2& op1, const float& op2);
Vec2 operator*(const Vec2& op1, const float& op2);

Vec2::Vec2(float x_, float y_) : x(x_), y(y_)
{
}

Vec2 operator+(const Vec2& op1, const Vec2& op2)
{
    return { op1.x + op2.x, op1.y + op2.y };
}

Vec2 operator-(const Vec2& op1, const Vec2& op2)
{
    return { op1.x - op2.x, op1.y - op2.y };
}

Vec2 operator/(const Vec2& op1, const float& op2)
{
    return { op1.x / op2, op1.y / op2 };
}

Vec2 operator*(const Vec2& op1, const float& op2)
{
    return { op1.x * op2, op1.y * op2 };
}

Vec2& Vec2::operator+=(const Vec2& op2)
{
    x += op2.x;
    y += op2.y;
    return *this;
}
struct Boule
{
    Vec2 position;
    Vec2 vitesse;
};

void updateBallWithNumericalIntegration(Boule& boule, float totalTime, float deltatime) 
{
    boule.position += boule.vitesse * deltatime; 
    Vec2 acceleration{ 0.f , -g()};
    boule.vitesse += acceleration * deltatime;
}

void updateBallWithAnalyticalSolution(Boule& boule, float totalTime , float deltatime)
{
  
    boule.position.y = -g() * (totalTime * totalTime) / 2;
}

int main()
{
    const int fps = 500;
    const float deltatime = 1.f / static_cast<float>(fps);
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
    window.setFramerateLimit(fps);

    Boule boule1{ {100, 0}, {0, 0} };
    Boule boule2{ {300, 0}, {0, 0} };

    float totalTime = 0.f;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        updateBallWithNumericalIntegration(boule1, totalTime, deltatime);
        updateBallWithAnalyticalSolution(boule2, totalTime, deltatime);

        sf::CircleShape shape1(50.f);
        shape1.setPosition(boule1.position.x, boule1.position.y);
        shape1.setFillColor(sf::Color::Green);
        window.draw(shape1);

        sf::CircleShape shape2(50.f);
        shape2.setPosition(boule2.position.x, boule2.position.y);
        shape2.setFillColor(sf::Color::Blue);
        window.draw(shape2);

        window.display();

        totalTime += deltatime;
    }

    return 0;
}