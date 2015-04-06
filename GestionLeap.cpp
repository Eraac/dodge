#include "GestionLeap.h"

using namespace Leap;
using namespace std;

GestionLeap::GestionLeap(Controller *controller) : _controller(controller)
{	
	oldFrame = _controller->frame();
	currentFrame = oldFrame;
}

void GestionLeap::refresh() {
	
	oldFrame = currentFrame;
	currentFrame = _controller->frame();
}

float GestionLeap::moveX(int id) {
	return currentFrame.fingers()[id].tipVelocity().x;
}

float GestionLeap::moveY(int id) {
	return currentFrame.fingers()[id].tipVelocity().y;
}

float GestionLeap::moveZ(int id) {
	return currentFrame.fingers()[id].tipVelocity().z;
}

int GestionLeap::countFingers() {

	if(currentFrame.fingers().count() > 10) // On évite quand cas d'erreur d'avoir plus de 10 doigts
		return 10;
	else
		return currentFrame.fingers().count();
}