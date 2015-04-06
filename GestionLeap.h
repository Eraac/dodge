#pragma once

#include "Leap.h"

class GestionLeap
{
	public:	
		GestionLeap(Leap::Controller*);
		void refresh(); // Place la currentFrame dans la old et recupere la derniere frame

		// Move speed
		float moveX(int id = 0);
		float moveY(int id = 0);
		float moveZ(int id = 0);

		// Finger
		int countFingers();

	private:
		Leap::Controller *_controller; 
		Leap::Frame oldFrame;
		Leap::Frame currentFrame;

};