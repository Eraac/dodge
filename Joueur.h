#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "const.h"
#include "sstream"

class Joueur
{
	public:
		Joueur(int niveau);
		sf::Text getScore();
		int getScoreFinal();
		float getTempsFinal();
		int getNiveau();
		void setDegats();		
		void addScore(int pointSup);		
		bool isVivant();		

	private:
		sf::Text _scoreText;
		sf::Clock _time; // Chrono du jeux (temps en vie)
		sf::Music *_hit;
		float _tempsFinal;
		int _score;
		int _nbVie;
		int _niveau;
};