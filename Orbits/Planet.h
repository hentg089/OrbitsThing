#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Planet
{
public:
	double theta;
	double orbitRadius;

	std::vector<sf::RectangleShape> pixels;
	sf::CircleShape planet;
	
	Planet(sf::CircleShape& planet, double mouseX, double mouseY, int screenX, int screenY, int radius);

	void calculateTheta(double mouseX, double mouseY, int screenX, int screenY, int radius);

private:
	void calculateOrbitRadius(double mouseX, double mouseY, int screenX, int screenY);
};