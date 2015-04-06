#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "GestionLeap.h"
#include "Brique.h"
#include "const.h"

class Menu
{
	public:
		Menu(sf::RenderWindow*, GestionLeap*);
		int run(); // Retourne le choix du menu (Menu::JOUER / Menu::QUITTER)

		// Enumération menu
		enum choix{FACILE, MOYEN, DIFFICLE, HIGHSCORE, QUITTER};

	private:
		sf::Text _text[NB_CHOIX_MENU];
		sf::RenderWindow *_window;
		GestionLeap *_leap;			
};