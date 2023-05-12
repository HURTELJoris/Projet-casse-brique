#pragma once
#include <SFML/Graphics.hpp>

class Player
{
private:
	sf::RectangleShape shape;
	sf::Vector2f position;
	sf::Vector2f size;
	int y;
	int width;
	int height;
	int life;
public:
	Player(int y, int width, int height, int life);
	~Player();
	void draw(sf::RenderWindow& window);
	sf::Vector2f getPosition();
	sf::Vector2f getSize();
	sf::RectangleShape getShape();
	int getWidth();
	int getHeight();
	void decreaseplayerlife();
	bool IsAlive();
	int getLife();
};