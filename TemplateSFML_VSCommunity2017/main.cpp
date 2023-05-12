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
	// créer la musique archi cool

	sf::SoundBuffer MusicBuffer;
	sf::Sound music;
	MusicBuffer.loadFromFile("sounds/Sounds For The Supermarket 1 (1975) - Grocery Store Music.wav");
	music.setBuffer(MusicBuffer);
	music.play();

	// créer la fenêtre

	sf::RenderWindow window(sf::VideoMode(800, 600), "Eloïse est un femelle");

	// créer le joueur

	Player player(550, 100, 15, 3);

	// créer la balle au mileu de l'écran, 50 pixels au dessus de la barre 

	Ball ball(window.getSize().x/2, player.getPosition().y - 100, 10, 300);

	// créer les briques

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

	// créer le fond dégradé

	sf::RectangleShape rdr2;
	rdr2.setSize(sf::Vector2f(window.getSize().x, 1));


	// créer le texte correspondant à la vie du joueur

	sf::Font MyFont;
	MyFont.loadFromFile("fonts/arial.ttf");
	sf::Text lifeText;
	lifeText.setFont(MyFont);
	lifeText.setCharacterSize(20);
	lifeText.setFillColor(sf::Color::White);

	
	// créer le temps, (nous sommes dieu dans ce programme).

	sf:: Clock clock;
	float ellapsedTime = 0;

	// on fait tourner le programme jusqu'à ce que la fenêtre soit fermée
	while (window.isOpen())
	{
		


		ellapsedTime = clock.restart().asSeconds();
		// on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
		sf::Event event;
		while (window.pollEvent(event))
		{
			// évènement "fermeture demandée" : on ferme la fenêtre
			if (event.type == sf::Event::Closed)
				window.close();

			else if (event.type == sf::Event::KeyPressed)
			{
				// Traiter les touches du clavier
				if (event.key.code == sf::Keyboard::Escape)
				{
					// Fermer la fenêtre en appuyant sur la touche Escape
				
				}

			}
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				// Traiter les clics de souris

			}
		}

		// déplacer la balle en fonction du temps qui passe

		ball.move(ellapsedTime);

		// détecter une collision avec la fenêtre

		ball.manageCollisionWith(window, player);

		// détecter une collision avec le joueur

		ball.update(player);

		// détecter une collision avec les briques

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
		
		// Dessiner le fond dégradé

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

		// Afficher la fenêtre

		window.display();

		int currentlife = player.getLife();
		if (currentlife >= 0) {
			printf("%s","zizi" );
		}
	}

	return 0;
}