#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Player.h"
#include "brique.h"

double mapValue(double X, double min, double max, double nMin, double nMax)
{
	double Y = (X - min) / (max - min) * (nMax - nMin) + nMin;

	return Y;
};

int main(int argc, char **argv)
{
	Ball ball(200, 250, 10, 200);
	Player player(550, 100, 15);
	Brick brique(200, 250, 10, 200,3);

	sf::RenderWindow window(sf::VideoMode(800, 600), "Eloïse est un femelle");

	// Créer le fond dégradé
	sf::RectangleShape rdr2;
	rdr2.setSize(sf::Vector2f(window.getSize().x, 1));


	

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


		// détecter une collision avec le joueur
		

		ball.move(ellapsedTime);

		ball.manageCollisionWith(window);


		ball.update(player);

		window.clear(sf::Color::White);
		
		// Dessiner le fond dégradé
		for (int i = 0; i < window.getSize().y; i++)
		{
			double mappedValue = mapValue(i, 0, window.getSize().y, 0, 255);
			rdr2.setFillColor(sf::Color(mappedValue, mappedValue, 0));
			rdr2.setPosition(0, i);
			window.draw(rdr2);
		}

		player.draw(window);
		ball.draw(window);
		brique.draw(window);
		window.display();
	}

	return 0;
}