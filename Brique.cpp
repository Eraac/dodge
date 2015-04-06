#include "Brique.h"

using namespace sf;

Brique::Brique() {
	_shape = RectangleShape(Vector2f(rand() % 150 + 1, rand() % 200 + 50));
		_shape.setPosition(rand() % WIDTH_WINDOWS - _shape.getSize().x + 1, 0 - _shape.getSize().y);
		_shape.setFillColor(Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1));
		_shape.setOutlineColor(Color::Black);
		_shape.setOutlineThickness(1);

		_speed = rand() % 10 + 3; // Vitesse entre 3 et 13
}

Brique::Brique(int niveau)
{
	_shape = RectangleShape(Vector2f(rand() % 150 + 1, rand() % 200 + 50));
		_shape.setPosition(rand() % WIDTH_WINDOWS - _shape.getSize().x + 1, 0 - _shape.getSize().y);
		if(niveau != 3) // Niveau difficile couleur des rectangles = blanc
			_shape.setFillColor(Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1));
		else
			_shape.setFillColor(Color::White);
		_shape.setOutlineColor(Color::Black);
		_shape.setOutlineThickness(1);

		_speed = rand() % 10 + 3; // Vitesse entre 3 et 13
}

RectangleShape Brique::getShape() {	
	return _shape;
}

void Brique::moveY() {	
	_shape.move(0, _speed);
}

bool Brique::isOut() {
	if(_shape.getPosition().y > HEIGHT_WINDOWS)
		return true;
	else
		return false;
}