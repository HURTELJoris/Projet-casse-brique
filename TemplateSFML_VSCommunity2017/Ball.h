#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "brique.h"
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
class Ball
{
private:
	sf::CircleShape shape;
	sf::Vector2f oldPosition;
	sf::Vector2f position;
	float speed;
	int radius;
	sf::Vector2f direction;
	static bool isRandInitialized;
	double randomizeAngle();
	void setAngle(double angle);
public:
	Ball(int x, int y, int radius, float speed);
	~Ball();
	void move(float ellapsedTime);
	void draw(sf::RenderWindow& window);
	float getSpeed();
	void setSpeed(float newSpeed);
	void setPosition(sf::Vector2f newPosition);
	void setDirection(sf::Vector2f newDirection);
	sf::Vector2f getPosition();
	float getRadius();
	void manageCollisionWith(sf::RenderWindow& window, Player& player);
	sf::CircleShape getShape() const;
	sf::Vector2f getDirection() const;
	void update(Player& player);
	void updatebrique(Brick& brique);
	sf::SoundBuffer collisionSoundBuffer;
	sf::SoundBuffer lose1lifeSoundBuffer;
	sf::SoundBuffer loseSoundBuffer;
	sf::Sound collisionSound;
	sf::Sound lose1life;
	sf::Sound lose;
};