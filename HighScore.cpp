#include "HighScore.h"

using namespace sf;
using namespace std;

HighScore::HighScore(RenderWindow *window, GestionLeap *leap)  : _window(window), _leap(leap) {
}

void HighScore::run()
{
	Texture image;
	Sprite background;

	if (!image.loadFromFile("image/highScore.png"))
		std::cerr << "Erreur chargement image/highScore.png" << std::endl;
	else
		background.setTexture(image);	

	Text text("Retour");
		text.setPosition(700, 550);
		text.setColor(Color::Black);


	bool out;
	int lastMenuTouch;
	Clock chrono;
	Time begin;

	CircleShape pointeur(10.f);

	while (_window->isOpen())
    {		
		_leap->refresh(); // Refresh de la frame		

		// Déplacement du pointeur
			pointeur.move(_leap->moveX() / 10, _leap->moveY() * -1 / 10);

		// === Contrôle des bords ===
			if(pointeur.getPosition().x <= 0) // Si la phrase touche le haut
				pointeur.setPosition(0, pointeur.getPosition().y); // On l'empêche de sortir
			if(pointeur.getPosition().x + pointeur.getRadius() * 2 >= WIDTH_WINDOWS) // Si la phrase touche bas
				pointeur.setPosition(WIDTH_WINDOWS - pointeur.getRadius() * 2, pointeur.getPosition().y); // On l'empêche de sortir
			if(pointeur.getPosition().y <= 0) // Si la phrase touche la gauche
				pointeur.setPosition(pointeur.getPosition().x, 0); // On l'empêche de sortir		 
			if(pointeur.getPosition().y + pointeur.getRadius() * 2 >= HEIGHT_WINDOWS) // Si la phrase touche droite
				pointeur.setPosition(pointeur.getPosition().x, HEIGHT_WINDOWS - pointeur.getRadius() * 2); // On l'empêche de sortir
		// === FIN Contrôle des bords ===

		// === Contrôle du menu ===
			if( pointeur.getPosition().x + pointeur.getRadius() > text.getGlobalBounds().left &&
				pointeur.getPosition().x + pointeur.getRadius() < text.getGlobalBounds().left + text.getGlobalBounds().width &&
				pointeur.getPosition().y + pointeur.getRadius() > text.getGlobalBounds().top &&
				pointeur.getPosition().y + pointeur.getRadius() < text.getGlobalBounds().top + text.getGlobalBounds().height) // Si on touche le menu
			{
				if(out)
					begin = chrono.getElapsedTime();

				out = false;
				
				if(chrono.getElapsedTime().asSeconds() - begin.asSeconds() > 0.5) // Si on est dessus depuis plus de 0.5sec. alors on valide
							return;
			}
			else// Si on touche pas le menu
			{
				chrono.restart();
				out = true;
			}
				
									
		// === FIN Contrôle du menu ===

		// === Couleur du pointeur ===
			if(chrono.getElapsedTime().asSeconds() - begin.asSeconds() < 0.1)
				pointeur.setFillColor(Color(255, 0, 0, 200));
			else if(chrono.getElapsedTime().asSeconds() - begin.asSeconds() < 0.2)
				pointeur.setFillColor(Color(191, 63, 0, 200));
			else if(chrono.getElapsedTime().asSeconds() - begin.asSeconds() < 0.3)
				pointeur.setFillColor(Color(127, 127, 0, 200));
			else if(chrono.getElapsedTime().asSeconds() - begin.asSeconds() < 0.4)
				pointeur.setFillColor(Color(63, 191, 0, 200));
			else if(chrono.getElapsedTime().asSeconds() - begin.asSeconds() < 0.5)
				pointeur.setFillColor(Color(0, 255, 0, 200));
		// === FIN Couleur du pointeur ===

        Event event;
        while (_window->pollEvent(event)) // Boucle d'event SFML
        {           
			switch(event.type)
			{
				case Event::Closed:
					_window->close();
				break;

				case Event::KeyPressed :
				{
					switch(event.key.code)
					{
						case Keyboard::Escape:
							_window->close();
						break;
					}
				}
				break;
			}
        }

        _window->clear(Color::White);
		_window->draw(background);
		_window->draw(pointeur);

		_window->draw(text);

        _window->display();
    }
}

void HighScore::setScore(int score, float temps)
{
	ofstream fichier("tableau.score", ios::app);	

	if(fichier) // Si le fichier est ouvert correctement
	{
		fichier << "\n" << score << ":" << temps;
	}
}

Text HighScore::getScore(int position)
{
	
}

Text HighScore::getTemps(int position)
{
	
}
