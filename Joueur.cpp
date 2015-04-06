#include "Joueur.h"

using namespace std;
using namespace sf;


Joueur::Joueur(int niveau)
{	
	_niveau = ++niveau; // ++ Pour faire score x1 en facile, x2 en normal et x3 en difficile
	_nbVie = 3;
	_score = 0;
	_time = Clock(); // On démarre le chrono (depuis le début de la game)

	// === Music ===
	_hit = new Music();

	if (!_hit->openFromFile("music/hit.ogg"))
			std::cerr << "Erreur chargement music/hit.ogg" << std::endl;
	else
		_hit->setPitch(1.2);
		
	// === FIN music ===

	// === Permet d'affiche les int/float/etc... dans les sf::Text ===
		ostringstream score;
			score << _score;
		ostringstream temps;
			temps << _time.getElapsedTime().asSeconds();
		ostringstream vie;
			vie << _nbVie;
	// === FIN Permet d'affiche les int/float/etc... dans les sf::Text ===

	_scoreText = Text("Votre score : " + score.str() + " / Vie : " + vie.str() + " / Temps : " + temps.str());
		if(_niveau == 3)
			_scoreText.setColor(Color::Blue);
		else
			_scoreText.setColor(Color::Black);
		_scoreText.setPosition(5, 0);
}

void Joueur::setDegats() {
	_nbVie--;
	//if(_hit->
	_hit->play();
}

int Joueur::getNiveau() {
	return _niveau;
}

Text Joueur::getScore()
{
	ostringstream score;
    score << _score;

	ostringstream temps;
    temps << _time.getElapsedTime().asSeconds();

	ostringstream vie;
	vie << _nbVie;

	_scoreText.setString("Votre score : " + score.str() + " / Vie : " + vie.str() + " / Temps : " + temps.str());

	return _scoreText;
}

void Joueur::addScore(int pointSup) {
	_score += pointSup * _niveau;
}

bool Joueur::isVivant()
{
	if(_nbVie>0)
		return true;
	else {	 
		_tempsFinal =  _time.getElapsedTime().asSeconds();

		return false;
	}
}

int Joueur::getScoreFinal() {
	return _score;
}

float Joueur::getTempsFinal() {
	return _tempsFinal;
}