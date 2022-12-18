#include "Planet.h"
#include <iostream>
#include <cmath>

Planet::Planet(sf::CircleShape& planet, double mouseX, double mouseY, int screenX, int screenY, int radius)
{
	this->planet = planet;
	
	calculateTheta(mouseX, mouseY, screenX, screenY, radius);
	calculateOrbitRadius(mouseX, mouseY, screenX, screenY);
}

void Planet::calculateTheta(double mouseX, double mouseY, int screenX, int screenY, int radius)
{	

	theta = atan((mouseY-screenY/2)/(mouseX-screenX/2));
}

void Planet::calculateOrbitRadius(double mouseX, double mouseY, int screenX, int screenY)
{
	orbitRadius = pow(pow(mouseX-screenX/2,2) + pow(mouseY-screenY/2,2), 0.5);
}