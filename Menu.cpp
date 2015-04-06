#include "Menu.h"

using namespace sf;
	

Menu::Menu(RenderWindow *window, GestionLeap *leap) : _window(window), _leap(leap)
{
	_text[Menu::FACILE] = Text("Facile");
		_text[Menu::FACILE].setPosition(100, 250);
	_text[Menu::MOYEN] = Text("Moyen");
		_text[Menu::MOYEN].setPosition(200, 250);
	_text[Menu::DIFFICLE] = Text("Difficile");
		_text[Menu::DIFFICLE].setPosition(300, 250);
	_text[HIGHSCORE] = Text("High Score");
		_text[Menu::HIGHSCORE].setPosition(625, 10);		
	_text[Menu::QUITTER] = Text("Quitter");
		_text[Menu::QUITTER].setPosition(700, 550);		

	for(int i = 0; i < NB_CHOIX_MENU; i++)
		_text[i].setColor(Color::Black);
}

int Menu::run()
{
	// === BACKGROUND ===
		Texture image;
		Sprite background;

		if (!image.loadFromFile("image/Logo.png"))
			std::cerr << "Erreur chargement image/Logo.png" << std::endl;
		else
			background.setTexture(image);
	// === FIN BACKGROUND ===

	// === Music ===
		Music *musicMenu = new Music();
			if (!musicMenu->openFromFile("music/menu.ogg"))
				std::cerr << "Erreur chargement music/menu.ogg" << std::endl;
			else {
				musicMenu->play();
				musicMenu->setLoop(true);
			}
	// === FIN Music ===

	int lastMenuTouch = -1;
	bool out = true;
	Clock chrono; //Pour savoir si on reste plus de 0.5sec. sur le menu
	sf::Time begin;

	CircleShape pointeur(10.f);

	// === Element du Menu ===		
		Brique brique[NB_CARRE_MENU];

		for(int i = 0; i < NB_CARRE_MENU; i++)
			brique[i] = Brique();
	// === FIN Element du jeux ===	

	while (_window->isOpen())
    {		
		_leap->refresh();

		// Déplacement de la sphere
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

		// === Déplacement des sprites et check touche le bord si oui on en créer une nouvelle ===
			for(int i = 0; i < NB_CARRE_MENU; i++) {
				brique[i].moveY();

				if(brique[i].isOut()) {
					brique[i] = Brique();
				}				
			}
		// === FIN Déplacement des sprites et check touche le bord si oui on en créer une nouvelle ===

		// === Contrôle du menu ===
			for(int i = 0; i < NB_CHOIX_MENU; i++)
			{
				if( pointeur.getPosition().x + pointeur.getRadius() > _text[i].getGlobalBounds().left &&
					pointeur.getPosition().x + pointeur.getRadius() < _text[i].getGlobalBounds().left + _text[i].getGlobalBounds().width &&
					pointeur.getPosition().y + pointeur.getRadius() > _text[i].getGlobalBounds().top &&
					pointeur.getPosition().y + pointeur.getRadius() < _text[i].getGlobalBounds().top + _text[i].getGlobalBounds().height) // Si on touche le menu
				{
					out = false;

					if(lastMenuTouch == i) 
					{
						if(chrono.getElapsedTime().asSeconds() - begin.asSeconds() > 0.5) { // Si on est dessus depuis plus de 0.5sec. alors on valide
							delete musicMenu;
							return i;
						}
					}
					else { // Si on touche un nouveau choix dans le menu on démarre recupere le temps pour comparer
						lastMenuTouch = i;
						begin = chrono.getElapsedTime();
					}
				}
				else if(i == NB_CHOIX_MENU - 1 && out) // Si on touche pas le menu
				{
					chrono.restart();
					begin = chrono.getElapsedTime();
				}
				else if(i == NB_CHOIX_MENU - 1)
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

		// === On affiche les sprites des rectangles === 
			for(int i = 0; i < NB_CARRE_MENU; i++)
				_window->draw(brique[i].getShape());
		// === FIN On affiche les sprites des rectangles === 

		for(int i = 0; i < NB_CHOIX_MENU; i++)
			_window->draw(_text[i]);		
		_window->draw(background);
		_window->draw(pointeur);
        _window->display();
    }

	delete musicMenu;
	return Menu::QUITTER; 
}