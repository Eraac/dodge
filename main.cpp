#include <SFML/Graphics.hpp>
#include <time.h>

#include "Leap.h"
#include "SampleListener.h"
#include "GestionLeap.h"

#include "Menu.h"
#include "Jeux.h"
#include "HighScore.h"
#include "const.h"

using namespace sf;
using namespace Leap;

int main()
{
	srand(time(NULL));

	// === LEAPMOTION ===
		// Create a sample listener, controller and gestion
		SampleListener listener;
		Controller *controller = new Controller;
			controller->addListener(listener);
		GestionLeap *leap = new GestionLeap(controller);
	// === FIN LEAPMOTION ===

		RenderWindow *window = new RenderWindow(sf::VideoMode(WIDTH_WINDOWS, HEIGHT_WINDOWS), "Dodge");
			window->setVerticalSyncEnabled(true);

	// Favicon
		Image ic = Image();
			if(ic.loadFromFile("image/icone.png"))
				window->setIcon(117, 162, ic.getPixelsPtr());

	Menu mainMenu(window, leap);	

	while(window->isOpen())
	{
		int choixMenu = mainMenu.run();

		switch(choixMenu)
		{
			case Menu::FACILE :
			{
				Jeux jeux(window, leap, Menu::FACILE);
				if(jeux.run() == Jeux::QUITTER)
					window->close();
			}
			break;

			case Menu::MOYEN :
			{
				Jeux jeux(window, leap, Menu::MOYEN);
				if(jeux.run() == Jeux::QUITTER)
					window->close();
			}
			break;

			case Menu::DIFFICLE :
			{
				Jeux jeux(window, leap, Menu::DIFFICLE);
				if(jeux.run() == Jeux::QUITTER)
					window->close();
			}
			break;

			case Menu::HIGHSCORE :
			{
				HighScore highScore(window, leap);
				highScore.run();
			}
			break;

			case Menu::QUITTER :
				window->close();
			break;
		}
	}

	controller->removeListener(listener);
	
	delete controller;
	delete window;

    return 0;
}