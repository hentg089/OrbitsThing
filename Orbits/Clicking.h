#pragma once
#include <SFML/Graphics.hpp> //required to pass an event

class Clicking
{
public:
	int holdCount;

	//constructor
	Clicking();

	//function which evaluates weather or not we are holding down the mouse.
	bool isClicking(sf::Event& event, int& holdCount);

};

