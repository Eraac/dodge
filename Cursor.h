/*
 * Class qui permet de gèrer un pointeur avec le LeapMotion
 * Elle gère aussi les menus via les méthodes addMenu (pour ajouter un champs), removeMenu (pour supprimer tout les champs), menu (qui return le menu selectionner)
 * Pour selectionner un menu il faut rester dessus 0.5sec. (un degrader rouge -> vert va se faire)
 * Il ne faut pas oublier de lui donner les bonnes informations de taille pour la fenetre, pour eviter que le curseur sorte de la fenetre ou alors ne parcours pas toute la fenetre
 * Via le constructeur ou les méthode setHeight, setWidth pour lui donner la taille de la fenetre
 */

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Cursor
{
	public :
		// Constructeur
		Cursor();
		Cursor(int width, int height, float radius = 5.f, sf::Color color = sf::Color(255, 0, 0, 200), float positionX = 0, float positionY = 0);
		// Destructeur
		~Cursor();

		void move(float const x, float const y);		// Déplace le curseur
		void checkPosition();							// Vérifie la position du pointeur par rapport au bords
		void addMenu(sf::Text const &menu);				// Ajoute un champs au menu
		void removeMenu();								// Supprime le menu
		int menu();										// Return le champs selectionné dans le menu
		sf::CircleShape getCircleShape() const;			// Return le pointeur pour l'affiche
		
		// Accesseurs - Mutateurs
		void setPosition(float const x, float const y);	// Position le curseur à une position
		void setHeight(int const height);				// Regle l'hauteur de la fenetre
		void setWidth(int const width);					// Regle la largeur de la fenetre
		void setRadius(float const radius);				// Regle le rayon du curseur		
		sf::Vector2f getPosition() const;				// Return position curseur
		int getHeight() const;							// Return hauteur de la fenetre
		int getWidth() const;							// Return largeur de la fenetre
		float getRadius() const;						// Return rayon curseur

	private :
		sf::CircleShape *_cursor;		
		int _height, _width;							// Permet de limiter le curseur dans son environnement
		// Attribut menu
		std::vector<sf::Text> _menu;					// Contient tous les sf::Text
		int _lastMenuTouch;
		bool _out;
		sf::Clock _chrono;
		sf::Time _begin;

};