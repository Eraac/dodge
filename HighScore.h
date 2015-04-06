#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include "SFML\Graphics.hpp"
#include "GestionLeap.h"
#include "const.h"

class HighScore
{
	public:
		HighScore(sf::RenderWindow*, GestionLeap*);
		void run();
		void setScore(int score, float temps);
		sf::Text getScore(int position);
		sf::Text getTemps(int position);

	private:
		sf::RenderWindow *_window;
		GestionLeap *_leap;
};