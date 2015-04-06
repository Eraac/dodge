#include "Jeux.h"

using namespace sf;
using namespace std;

Jeux::Jeux(RenderWindow *window, GestionLeap *leap, int niveau) : _window(window), _leap(leap), _joueur(niveau)
{
	// === DIFFICULTE ===
		nbBriques = (niveau == Jeux::FACILE) ? 10 : (niveau == Jeux::MOYEN) ? 12 : 14; // OMFG Double conditions ternaire : facile = 10 moyen = 12 difficile = 14
	// === FIN DIFFICULTE ===		

	if(niveau == Jeux::DIFFICILE) //Difficile couleur de fond = noir sinon blanc
		_colorBackground = Color::Black;
	else
		_colorBackground = Color::White;

	// === Music ===
		_musicGame = new Music();
			if (niveau == Jeux::FACILE && !_musicGame->openFromFile("music/level-1.ogg"))
				std::cerr << "Erreur chargement music/level-1.ogg" << std::endl;
			else if (niveau == Jeux::MOYEN && !_musicGame->openFromFile("music/level-2.ogg"))
				std::cerr << "Erreur chargement music/level-2.ogg" << std::endl;
			else if (niveau == Jeux::DIFFICILE && !_musicGame->openFromFile("music/level-3.ogg"))
				std::cerr << "Erreur chargement music/level-3.ogg" << std::endl;
			else {
				_musicGame->play();
				_musicGame->setLoop(true);
				_musicGame->setVolume(50);
			}


	// === FIN Music ===
}

Color Jeux::getBackground() {
	return _colorBackground;
}

int Jeux::run()
{	
	// === Pointeur ===
		_pointeur = CircleShape(10.f);
			_pointeur.setFillColor(Color::Cyan);
			_pointeur.setPosition(WIDTH_WINDOWS / 2 - _pointeur.getRadius(), HEIGHT_WINDOWS / 2 - _pointeur.getRadius());
	// === FIN Pointeur ===

	// === Element du jeux ===		
		Brique brique[14];

		for(int i = 0; i < nbBriques; i++)
			brique[i] = Brique(_joueur.getNiveau());
	// === FIN Element du jeux ===	

	while (_window->isOpen() && _joueur.isVivant())
    {		
		_leap->refresh(); // Refresh de la frame
		_joueur.addScore((_pointeur.getPosition().y - HEIGHT_WINDOWS ) * -1 / 100); // score++ selon la hauteur 

		// Déplacement du pointeur
			_pointeur.move(_leap->moveX() / 10, _leap->moveY() * -1 / 10);

		// === Contrôle des bords ===
			if(_pointeur.getPosition().x <= 0) // Si la phrase touche le haut
				_pointeur.setPosition(0, _pointeur.getPosition().y); // On l'empêche de sortir
			if(_pointeur.getPosition().x + _pointeur.getRadius() * 2 >= WIDTH_WINDOWS) // Si la phrase touche bas
				_pointeur.setPosition(WIDTH_WINDOWS - _pointeur.getRadius() * 2, _pointeur.getPosition().y); // On l'empêche de sortir
			if(_pointeur.getPosition().y <= 0) // Si la phrase touche la gauche
				_pointeur.setPosition(_pointeur.getPosition().x, 0); // On l'empêche de sortir		 
			if(_pointeur.getPosition().y + _pointeur.getRadius() * 2 >= HEIGHT_WINDOWS) // Si la phrase touche droite
				_pointeur.setPosition(_pointeur.getPosition().x, HEIGHT_WINDOWS - _pointeur.getRadius() * 2); // On l'empêche de sortir
		// === FIN Contrôle des bords ===

		// === Déplacement des sprites et check touche le bord si oui on en créer une nouvelle ===
			for(int i = 0; i < nbBriques; i++) {
				brique[i].moveY();

				if(brique[i].isOut()) {
					brique[i] = Brique(_joueur.getNiveau());
				}				
			}
		// === FIN Déplacement des sprites et check touche le bord si oui on en créer une nouvelle ===

		// === Gestion collision rectangle ===
			for(int i = 0; i < nbBriques; i++) {
				if( brique[i].getShape().getGlobalBounds().left < _pointeur.getGlobalBounds().left + _pointeur.getGlobalBounds().width &&
					brique[i].getShape().getGlobalBounds().left + brique[i].getShape().getGlobalBounds().width > _pointeur.getGlobalBounds().left &&
					brique[i].getShape().getGlobalBounds().top < _pointeur.getGlobalBounds().top + _pointeur.getGlobalBounds().height &&
					brique[i].getShape().getGlobalBounds().top + brique[i].getShape().getGlobalBounds().height > _pointeur.getGlobalBounds().top) 
				{					
					_joueur.setDegats();

					for(int i = 0; i < nbBriques; i++) // On supprime tous les rectangles et on les relances
						brique[i] = Brique(_joueur.getNiveau());

					if(!_joueur.isVivant()) {						
						return gameOver(); // On affiche le score et on propose de refaire une partie ou de quitter
					}
				}
			}
		// === FIN Gestion collision rectangle ===

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

		
		_window->clear(getBackground());

		// === On affiche les sprites des rectangles === 
			_window->draw(_pointeur);		
			for(int i = 0; i < nbBriques; i++)
				_window->draw(brique[i].getShape());
			_window->draw(_joueur.getScore());
		// === FIN On affiche les sprites des rectangles ===

        _window->display();
    }
}

int Jeux::gameOver()
{
	Texture image;
	Sprite background;

	if (!image.loadFromFile("image/GameOver.png"))
		std::cerr << "Erreur chargement image/GameOver.png" << std::endl;
	else
		background.setTexture(image);	

	// === Music ====
	if (!_musicGame->openFromFile("music/GameOver.ogg") && Jeux::FACILE)
				std::cerr << "Erreur chargement music/GameOver.ogg" << std::endl;
	else {
		_musicGame->play();
		_musicGame->setLoop(true);
	}
	// === FIN Music ===

	Text text[2];
		text[0] = Text("Rejouer");
			text[0].setPosition(550, 550);
			text[0].setColor(Color(0, 153, 51));
		text[1] = Text("Quitter");
			text[1].setPosition(700, 550);
			text[1].setColor(Color::Black);

	// === Recup score ===
		ostringstream score;
		score << _joueur.getScoreFinal();

		ostringstream temps;
		temps << _joueur.getTempsFinal();
	// === FIN Recup score ===

	Text scoreInfo[2];
		scoreInfo[0] = Text(score.str() + " dodges");
			scoreInfo[0].setPosition(200, 450);
			scoreInfo[0].setColor(Color(51, 129, 199));
		scoreInfo[1] = Text(temps.str() + "s");
			scoreInfo[1].setPosition(500, 450);
			scoreInfo[1].setColor(Color(51, 129, 199));

	bool out = true;
	int lastMenuTouch = -1;
	Clock chrono;
	Time begin;

	while (_window->isOpen())
    {		
		_leap->refresh(); // Refresh de la frame		

		// Déplacement du pointeur
			_pointeur.move(_leap->moveX() / 10, _leap->moveY() * -1 / 10);

		// === Contrôle des bords ===
			if(_pointeur.getPosition().x <= 0) // Si la phrase touche le haut
				_pointeur.setPosition(0, _pointeur.getPosition().y); // On l'empêche de sortir
			if(_pointeur.getPosition().x + _pointeur.getRadius() * 2 >= WIDTH_WINDOWS) // Si la phrase touche bas
				_pointeur.setPosition(WIDTH_WINDOWS - _pointeur.getRadius() * 2, _pointeur.getPosition().y); // On l'empêche de sortir
			if(_pointeur.getPosition().y <= 0) // Si la phrase touche la gauche
				_pointeur.setPosition(_pointeur.getPosition().x, 0); // On l'empêche de sortir		 
			if(_pointeur.getPosition().y + _pointeur.getRadius() * 2 >= HEIGHT_WINDOWS) // Si la phrase touche droite
				_pointeur.setPosition(_pointeur.getPosition().x, HEIGHT_WINDOWS - _pointeur.getRadius() * 2); // On l'empêche de sortir
		// === FIN Contrôle des bords ===

		// === Contrôle du menu ===
			for(int i = 0; i < 2; i++)
			{
				if( _pointeur.getPosition().x + _pointeur.getRadius() > text[i].getGlobalBounds().left &&
					_pointeur.getPosition().x + _pointeur.getRadius() < text[i].getGlobalBounds().left + text[i].getGlobalBounds().width &&
					_pointeur.getPosition().y + _pointeur.getRadius() > text[i].getGlobalBounds().top &&
					_pointeur.getPosition().y + _pointeur.getRadius() < text[i].getGlobalBounds().top + text[i].getGlobalBounds().height) // Si on touche le menu
				{
					out = false;

					if(lastMenuTouch == i) 
					{						
						if(chrono.getElapsedTime().asSeconds() - begin.asSeconds() > 0.5) { // Si on est dessus depuis plus de 0.5sec. alors on valide
							delete _musicGame;
							return i+3; // +3 pour passer facile, moyen et difficile
						}
					}
					else { // Si on touche un nouveau choix dans le menu on démarre recupere le temps pour comparer
						lastMenuTouch = i;
						begin = chrono.getElapsedTime();
					}
				}
				else if(i == 2 - 1 && out) // Si on touche pas le menu
				{
					chrono.restart();
					begin = chrono.getElapsedTime();
				}
				else if(i == 1)
					out = true;				
			}			
		// === FIN Contrôle du menu ===

		// === Couleur du pointeur ===
			if(chrono.getElapsedTime().asSeconds() - begin.asSeconds() < 0.1)
				_pointeur.setFillColor(Color(255, 0, 0, 200));
			else if(chrono.getElapsedTime().asSeconds() - begin.asSeconds() < 0.2)
				_pointeur.setFillColor(Color(191, 63, 0, 200));
			else if(chrono.getElapsedTime().asSeconds() - begin.asSeconds() < 0.3)
				_pointeur.setFillColor(Color(127, 127, 0, 200));
			else if(chrono.getElapsedTime().asSeconds() - begin.asSeconds() < 0.4)
				_pointeur.setFillColor(Color(63, 191, 0, 200));
			else if(chrono.getElapsedTime().asSeconds() - begin.asSeconds() < 0.5)
				_pointeur.setFillColor(Color(0, 255, 0, 200));
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
		_window->draw(_pointeur);
		// === Affiche menu ===
			for(int i = 0; i < 2; i++)
				_window->draw(text[i]);
		// === FIN Affiche menu ===
		// === Affiche score ===
			for(int i = 0; i < 2; i++)
				_window->draw(scoreInfo[i]);
		// === FIN Affiche score ===
        _window->display();
    }

	return Jeux::QUITTER;
}