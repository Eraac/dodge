#include "Cursor.h"

using namespace sf;

Cursor::Cursor()
{
	_cursor = new CircleShape(5.f);
		_cursor->setFillColor(Color(255, 0, 0, 200));
	_height = 600;
	_width = 800;
	_lastMenuTouch = -1;
	_out = true;
}

Cursor::Cursor(int width, int height, float radius, sf::Color color, float positionX, float positionY) : _height(height), _width(width)
{
	_cursor = new CircleShape(radius);
		_cursor->setFillColor(color);
		_cursor->setPosition(positionX, positionY);

	_lastMenuTouch = -1;
	_out = true;
}

Cursor::~Cursor() {
	delete _cursor;
}

void Cursor::move(float const x, float const y) {
	_cursor->move(x, y);

	checkPosition();
}

void Cursor::checkPosition() {
		
	if(_cursor->getPosition().x <= 0) // Si la phrase touche le haut
		_cursor->setPosition(0, _cursor->getPosition().y); // On l'empêche de sortir
	if(_cursor->getPosition().x + _cursor->getRadius() * 2 >= _width) // Si la phrase touche bas
		_cursor->setPosition(_width - _cursor->getRadius() * 2, _cursor->getPosition().y); // On l'empêche de sortir
	if(_cursor->getPosition().y <= 0) // Si la phrase touche la gauche
		_cursor->setPosition(_cursor->getPosition().x, 0); // On l'empêche de sortir		 
	if(_cursor->getPosition().y + _cursor->getRadius() * 2 >= _height) // Si la phrase touche droite
		_cursor->setPosition(_cursor->getPosition().x, _height - _cursor->getRadius() * 2); // On l'empêche de sortir	
}

void Cursor::addMenu(Text const &menu) {
	_menu.push_back(menu);		
}

void Cursor::removeMenu() {
	_menu.swap(std::vector<Text>());
}

int Cursor::menu() {

	if(_menu.size() == 0)
		return -1;

	// === Couleur du pointeur ===
		if(_chrono.getElapsedTime().asSeconds() - _begin.asSeconds() < 0.1)
			_cursor->setFillColor(Color(255, 0, 0, 200));
		else if(_chrono.getElapsedTime().asSeconds() - _begin.asSeconds() < 0.2)
			_cursor->setFillColor(Color(191, 63, 0, 200));
		else if(_chrono.getElapsedTime().asSeconds() - _begin.asSeconds() < 0.3)
			_cursor->setFillColor(Color(127, 127, 0, 200));
		else if(_chrono.getElapsedTime().asSeconds() - _begin.asSeconds() < 0.4)
			_cursor->setFillColor(Color(63, 191, 0, 200));
		else if(_chrono.getElapsedTime().asSeconds() - _begin.asSeconds() < 0.5)
			_cursor->setFillColor(Color(0, 255, 0, 200));
	// === FIN Couleur du pointeur ===

	for(unsigned int i = 0; i < _menu.size(); i++) {
		if( _cursor->getPosition().x + _cursor->getRadius() > _menu[i].getGlobalBounds().left &&
			_cursor->getPosition().x + _cursor->getRadius() < _menu[i].getGlobalBounds().left + _menu[i].getGlobalBounds().width &&
			_cursor->getPosition().y + _cursor->getRadius() > _menu[i].getGlobalBounds().top &&
			_cursor->getPosition().y + _cursor->getRadius() < _menu[i].getGlobalBounds().top + _menu[i].getGlobalBounds().height ) // Si on le touche le menu
		{
			_out = false;
			
			if(_lastMenuTouch == i && _chrono.getElapsedTime().asSeconds() - _begin.asSeconds() > 0.5) // Si on touche tjrs le même champs depuis 0.5sec.
				return i;
			else if(_lastMenuTouch != i) { // Si on touche un nouveau champs dans le menu
				_lastMenuTouch = i;
				_begin = _chrono.getElapsedTime();
			}
		}
		else if(i == _menu.size() - 1 && _out) // Si on touche pas le menu
		{
			_chrono.restart();
			_begin = _chrono.getElapsedTime();
		}
		else if(i == _menu.size() - 1) // Si on sort du menu
			_out = true;		
	}

	return -1; // Si on valide aucun champs on return -1
}

CircleShape Cursor::getCircleShape() const {
	return *_cursor;
}

// Accesseurs - Mutateurs

void Cursor::setPosition(float const x, float const y) {

	_cursor->setPosition(x, y);
	
	checkPosition();
}

void Cursor::setHeight(int const height) {
	_height = height;
}

void Cursor::setWidth(int const width) {
	_width = width;
}

void Cursor::setRadius(float const radius) {
	_cursor->setRadius(radius);
}

Vector2f Cursor::getPosition() const {
	return _cursor->getPosition();
}

int Cursor::getHeight() const {
	return _height;
}

int Cursor::getWidth() const {
	return _width;
}

float Cursor::getRadius() const {
	return _cursor->getRadius();
}