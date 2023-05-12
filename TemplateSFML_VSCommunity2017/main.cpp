#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Player.h"
#include "brique.h"
#include <deque>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

double mapValue(double X, double min, double max, double nMin, double nMax)
{
	double Y = (X - min) / (max - min) * (nMax - nMin) + nMin;

	return Y;
};

int main(int argc, char **argv)
{
	// cr�er la musique archi cool

	sf::SoundBuffer MusicBuffer;
	sf::Sound music;
	MusicBuffer.loadFromFile("sounds/Sounds For The Supermarket 1 (1975) - Grocery Store Music.wav");
	music.setBuffer(MusicBuffer);
	music.play();

	// cr�er la fen�tre

	sf::RenderWindow window(sf::VideoMode(800, 600), "Elo�se est un femelle");

	// cr�er le joueur

	Player player(550, 100, 15, 3);

	// cr�er la balle au mileu de l'�cran, 50 pixels au dessus de la barre 

	Ball ball(window.getSize().x/2, player.getPosition().y - 100, 10, 300);

	// cr�er les briques

	std::deque<Brick*> bricks;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 5; j++) {
			int intitialgapleft = 25;
			int intitialgaptop = 50;
			int gaphorizontal = 130;
			int gapvertical = 45;
			bricks.push_back(new Brick(intitialgapleft + gaphorizontal * i, intitialgaptop + gapvertical * j, 100, 20, 3));
		}
	}

	// cr�er le fond d�grad�

	sf::RectangleShape rdr2;
	rdr2.setSize(sf::Vector2f(window.getSize().x, 1));


	// cr�er le texte correspondant � la vie du joueur

	sf::Font MyFont;
	MyFont.loadFromFile("fonts/arial.ttf");
	sf::Text lifeText;
	lifeText.setFont(MyFont);
	lifeText.setCharacterSize(20);
	lifeText.setFillColor(sf::Color::White);

	
	// cr�er le temps, (nous sommes dieu dans ce programme).

	sf:: Clock clock;
	float ellapsedTime = 0;

	// on fait tourner le programme jusqu'� ce que la fen�tre soit ferm�e
	while (window.isOpen())
	{
		


		ellapsedTime = clock.restart().asSeconds();
		// on inspecte tous les �v�nements de la fen�tre qui ont �t� �mis depuis la pr�c�dente it�ration
		sf::Event event;
		while (window.pollEvent(event))
		{
			// �v�nement "fermeture demand�e" : on ferme la fen�tre
			if (event.type == sf::Event::Closed)
				window.close();

			else if (event.type == sf::Event::KeyPressed)
			{
				// Traiter les touches du clavier
				if (event.key.code == sf::Keyboard::Escape)
				{
					// Fermer la fen�tre en appuyant sur la touche Escape
				
				}

			}
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				// Traiter les clics de souris

			}
		}

		// d�placer la balle en fonction du temps qui passe

		ball.move(ellapsedTime);

		// d�tecter une collision avec la fen�tre

		ball.manageCollisionWith(window, player);

		// d�tecter une collision avec le joueur

		ball.update(player);

		// d�tecter une collision avec les briques

		for (int i = 0; i < bricks.size(); i++) {
			ball.updatebrique(*bricks[i]);
		}

		// effacer les briques

		for (int i = 0; i < bricks.size(); i++) {
			if (!bricks[i]->isAlive()) {
				bricks.erase(bricks.begin() + i);
				break;
			}
		}

		window.clear(sf::Color::White);
		
		// Dessiner le fond d�grad�

		for (int i = 0; i < window.getSize().y; i++)
		{
			double mappedValue = mapValue(i, 0, window.getSize().y, 0, 255);
			rdr2.setFillColor(sf::Color(mappedValue, mappedValue, 0));
			rdr2.setPosition(0, i);
			window.draw(rdr2);
		}

		// Dessiner le joueur

		player.draw(window);

		// Dessiner la balle

		ball.draw(window);

		// Dessiner les briques

		for (int i = 0; i < bricks.size(); i++) {
			bricks[i]->draw(window);
		}

		// Dessiner le texte correspondant aux vies restantes

		lifeText.setString("Vie : " + std::to_string(player.getLife())); 
		lifeText.setPosition(window.getSize().x -75, 5);
		window.draw(lifeText);

		// Afficher la fen�tre

		window.display();

		int currentlife = player.getLife();
		if (currentlife >= 0) {
			printf("%s","zizi" );
		}
	}

	return 0;
}