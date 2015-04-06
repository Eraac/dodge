#pragma once

#include <iostream>
#include "SFML\Graphics.hpp"
#include "const.h"

class Brique
{
	public:
		Brique();
		Brique(int niveau);
		sf::RectangleShape getShape();
		void moveY();
		bool isOut();

	private:
		sf::RectangleShape _shape;		
		int _speed;

};