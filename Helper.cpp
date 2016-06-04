#include "Helper.h"
#include <SFML\Graphics.hpp>
#include <cmath>

sf::Vector2f Helper::CalculatePoint(sf::Vector2f origin, float distance, float angle)
{
	//bx = ax + d*cos(t);
	//by = ay + d*sin(t)

	sf::Vector2f finalPoint;
	finalPoint.x = (int)(origin.x + distance * cos(angle));
	finalPoint.y = (int)(origin.y + distance * sin(angle));

	return finalPoint;
}