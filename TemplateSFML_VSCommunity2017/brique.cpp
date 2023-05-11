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