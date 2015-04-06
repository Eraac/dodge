#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "GestionLeap.h"
#include "Joueur.h"
#include "Brique.h"
#include "const.h"

class Jeux
{
	public:
		Jeux(sf::RenderWindow*, GestionLeap*, int niveau);
		int run();
		int gameOver();
		sf::Color getBackground();
		enum niveau{FACILE, MOYEN, DIFFICILE, REJOUER, QUITTER};

	private:
		sf::RenderWindow *_window;
		sf::Color _colorBackground;
		sf::CircleShape _pointeur;
		sf::Music *_musicGame;
		GestionLeap *_leap;
		Joueur _joueur;
		int nbBriques;
};