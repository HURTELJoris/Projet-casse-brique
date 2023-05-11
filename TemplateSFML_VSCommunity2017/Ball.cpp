#include "Ball.h"
#include "Player.h"

#include <cstdlib>
#include <ctime>
#define _USE_MATH_DEFINES
#include <math.h>

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


//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

void Ball::manageCollisionWith(sf::RenderWindow& window)
{
	// Si la balle sort de l'écran (par en haut)
	if (position.y <= 0)
	{
		// Inverse la direction sur l'axe y :
		direction.y *= -1;
		position.y = 0;
	}
	else if (position.y >= window.getSize().y - radius * 2)
	{
		// Inverse la direction sur l'axe y :
		direction.y *= -1;
		position.y = window.getSize().y - 2 * radius;
		int lost = true;
	}
	// Si la balle sort de l'écran (par les côtés)
	if (position.x <= 0)
	{
		direction.x *= -1;
		position.x = 0;
	}
	else if (position.x + 2 * radius >= window.getSize().x)
	{
		direction.x *= -1;
		position.x = window.getSize().x - 2 * radius;
	}
}

void Ball::update(Player& player) {
	
	// Créer le rectangle de la zone de collision de la balle avec la barre
	sf::FloatRect ballRect(position.x, position.y, 2 * radius, 2 * radius);
	sf::FloatRect playerRect(player.getPosition().x, player.getPosition().y, player.getSize().x, player.getSize().y);

	// Vérifier si la zone de collision de la balle intersecte le rectangle de la barre
	if (ballRect.intersects(playerRect)) {
		// Calcule la position relative de la balle par rapport à la plateforme
		double relativeIntersectX = position.x + radius - player.getPosition().x - player.getSize().x / 2.0;

		// Normalise la position relative de la balle
		double normalizedRelativeIntersectionX = relativeIntersectX / (player.getSize().x / 2.0);

		// Calcule l'angle de rebond de la balle en radians
		double maxAngle = 60.0; // Angle de rebond maximum en degrés
		double angle = normalizedRelativeIntersectionX * maxAngle * M_PI / 180.0;

		// Déplace la balle en dehors de la plateforme
		double overlap = ballRect.top + ballRect.height - playerRect.top;
		position.y -= overlap;
		direction.y = -std::abs(direction.y);

		// Change la direction de la balle en fonction de l'angle de rebond
		setAngle(angle);
	}
}



//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

sf::Vector2f Ball::getPosition() {
	return position;
}

float Ball::getRadius() {
	return radius;
}

sf::CircleShape Ball::getShape() const {
	return shape;
}

sf::Vector2f Ball::getDirection() const {
	return direction;
}