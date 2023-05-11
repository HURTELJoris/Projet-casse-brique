#include "Player.h"

Player::Player(int y, int width_, int height_) : y(y) {
	position = sf::Vector2f(0, y);
	size = sf::Vector2f(width_, height_);
	shape.setPosition(position);
	shape.setSize(size);
	shape.setFillColor(sf::Color::Green);
	this->width = width_;
	this->height = height_;
}

Player::~Player() {}

void Player::draw(sf::RenderWindow& window) {
	// R�cup�rer la position actuelle de la souris
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

	// Mettre � jour la position horizontale de la forme du joueur
	position.x = mousePosition.x - size.x / 2;

	// V�rifier si le joueur sort de l'�cran � gauche
	if (position.x < 0) {
		position.x = 0;
	}

	// V�rifier si le joueur sort de l'�cran � droite
	if (position.x + size.x > window.getSize().x) {
		position.x = window.getSize().x - size.x;
	}

	// Mettre � jour la position verticale de la forme du joueur
	position.y = y;
	shape.setPosition(position);

	// Dessiner la forme du joueur
	window.draw(shape);
}

sf::Vector2f Player::getPosition() {
	return position;
}

sf::Vector2f Player::getSize() {
	return size;
}

sf::RectangleShape Player::getShape(){
	return shape;
}

int Player::getWidth() {
	return width;
}

int Player::getHeight() {
	return height;
}