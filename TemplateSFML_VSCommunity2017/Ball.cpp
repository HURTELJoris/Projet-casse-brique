#include "Ball.h"

bool Ball::isRandInitialized = false;


double Ball::randomizeAngle()
{
	if (!isRandInitialized)
	{
		srand(time(NULL));
		isRandInitialized = true;
	}

	return (((double)rand() / (double)RAND_MAX) * 60.0) - 30.0;
}

void Ball::setAngle(double angle)
{
	direction.x = sin(angle);
	direction.y = -cos(angle);
}

Ball::Ball(int x, int y, int radius, float speed)
{
	position.x = x;
	position.y = y;
	oldPosition = position;
	shape.setFillColor(sf::Color(sf::Color::White));
	this->radius = radius;
	shape.setRadius(radius);
	this->speed = speed;

	setAngle(randomizeAngle());

}

Ball::~Ball()
{
}

void Ball::move(float ellapsedTime)
{
	position += ellapsedTime * speed * direction;
}

void Ball::draw(sf::RenderWindow & window)
{
	shape.setPosition(position);
	window.draw(shape);
}

float Ball::getSpeed()
{
	return speed;
}

void Ball::setSpeed(float newSpeed)
{
	speed = newSpeed;
}

void Ball::setPosition(sf::Vector2f newPosition)
{
	position = newPosition;
	oldPosition = position;
}

void Ball::setDirection(sf::Vector2f newDirection)
{
	direction = newDirection;
}

void Ball::manageCollisionWith(sf::RenderWindow& window) 
{
	// Si la balle sort de l'écran (par en haut)
	if (position.y <= 0 || position.y >= window.getSize().y - radius * 2)
	{
		// Inverse la direction sur l'axe y :
		direction.y *= -1;
	}
	// Si la balle sort de l'écran (par les côtés)
	if (position.x <= 0 || position.x >= window.getSize().x - radius*2)
	{
		// Inverse la direction sur l'axe y :
		direction.x *= -1;
	}
}

void Ball::manageCollisionWith2(sf::RectangleShape& bar)
{
	// Si la balle sort de l'écran (par en haut)
	if (position.y <= 0 || position.y >= bar.getSize().y - radius * 2)
	{
		// Inverse la direction sur l'axe y :
		direction.y *= -1;
	}
	// Si la balle sort de l'écran (par les côtés)
	if (position.x <= 0 || position.x >= bar.getSize().x - radius * 2)
	{
		// Inverse la direction sur l'axe y :
		direction.x *= -1;
	}
}