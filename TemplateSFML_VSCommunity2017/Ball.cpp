#include "Ball.h"
#include "Player.h"
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

void Ball::manageCollisionWith(sf::RenderWindow& window, Player& player)
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

	// Détecter une collision avec le joueur

	sf::FloatRect ballBounds(position.x, position.y, radius * 2, radius * 2);
	sf::FloatRect playerBounds = player.getShape().getGlobalBounds();
	if (ballBounds.intersects(playerBounds)) {
		// Inverse la direction sur l'axe y :
		direction.y *= -1;

		// Ajuste la position de la balle pour éviter qu'elle ne reste coincée dans le joueur :
		if (direction.y > 0) {
			// si la balle se déplace vers le bas
			position.y = playerBounds.top - radius * 2 - 1;
		}
		else {
			// si la balle se déplace vers le haut
			position.y = playerBounds.top + playerBounds.height + 1;
		}
	}
}

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