#include "brique.h"

Brick::Brick(int x, int y, int width, int height, int health) : health(health)
{
	position = sf::Vector2f(x, y);
	size = sf::Vector2f(width, height);
	shape.setPosition(position);
	shape.setSize(size);
	shape.setFillColor(getColorFromLife());
}

Brick::~Brick()
{
}

void Brick::draw(sf::RenderWindow & window)
{
	window.draw(shape);
}

sf::Color Brick::getColorFromLife()
{
	if (health == 3) {
		return sf::Color(255, 0, 0); // Rouge
	}
	else if (health == 2) {
		return sf::Color(255, 255, 0); // Jaune
	}
	else if (health == 1) {
		return sf::Color(0, 255, 0); // Vert
	}
	else {
		return sf::Color(255, 255, 255); // Blanc
	}
}

bool Brick::isAlive()
{
	return health > 0;
}

void Brick::hit()
{
	if (health > 0) {
		health--;
		shape.setFillColor(getColorFromLife());
	}
}

sf::Vector2f Brick::getPosition()
{
	return position;
}

sf::Vector2f Brick::getSize()
{
	return size;
}