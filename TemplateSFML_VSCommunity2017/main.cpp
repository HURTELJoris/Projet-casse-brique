#include <SFML/Graphics.hpp>
#include "Ball.h"

double mapValue(double X, double min, double max, double nMin, double nMax)
{
	double Y = (X - min) / (max - min) * (nMax - nMin) + nMin;

	/*

	Y : valeur dans l'intervalle 2
	A : minimum intervalle 1
	N : maximum intervalle 1
	C : minimum intervalle 2
	D : maximum intervalle 2
	X : valeur dans l'intervalle 1

	*/
	return Y;
};

int main(int argc, char **argv)
{
	Ball ball(200, 250, 10, 200);
	sf::RenderWindow window(sf::VideoMode(800, 600), "Eloïse est un femelle");

	/*
	sf::RectangleShape rectangle(sf::Vector2f(100, 50));
	rectangle.setPosition(200, 150);
	rectangle.setFillColor(sf::Color::Red);
	rectangle.setOutlineColor(sf::Color::Blue);
	rectangle.setOutlineThickness(12);
	
	sf::CircleShape circle(50);
	circle.setPosition(400, 300);
	circle.setFillColor(sf::Color::Green);
	circle.setOutlineColor(sf::Color::Blue);
	circle.setOutlineThickness(12);
	*/
	sf::RectangleShape rdr2;
	rdr2.setSize(sf::Vector2f(window.getSize().x, 1));


	

	sf:: Clock clock;
	sf::Vector3f xFactor(10, 20, 30);
	float ellapsedTime = 0;


	// LA BARRE
	sf::RectangleShape bar(sf::Vector2f(200, 20));
	bar.setFillColor(sf::Color::Green);
	bar.setOrigin(bar.getSize() / 2.0f); // Définir l'origine de la barre au milieu

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

		
		ball.move(ellapsedTime);
		ball.manageCollisionWith(window);
		

		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		// mets la position de la barre en bas et l'emplacement en x de la souris
		bar.setPosition(static_cast<float>(mousePosition.x), window.getSize().y - 25);
		ball.manageCollisionWith2(bar);
		window.clear(sf::Color::White);
		
		
		for (int i = 0; i < window.getSize().y; i++) {

			double mappedValue = mapValue(i, 0, window.getSize().y, 0, 255);
			rdr2.setFillColor(sf::Color(mappedValue, mappedValue, 0));
			rdr2.setPosition(0, i);
			window.draw(rdr2);
		}

		/*
		rdr2.setPosition(0, 0);
		window.draw(rdr2);
		window.draw(rectangle);
		window.draw(circle);
		*/
		ball.draw(window);

		window.draw(bar);
		window.display();
	}

	return 0;
}