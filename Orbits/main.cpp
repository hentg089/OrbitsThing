#include <SFML/Graphics.hpp>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include <iostream>
#include "Clicking.h"
#include "Vector2d.h"
#include "Planet.h"

using namespace vecSpace;

void Draw(sf::RenderWindow& window, std::vector<Planet>& planets, sf::Sprite& sunSprite, sf::Sprite& spaceSprite);
void drawPlanets(sf::RenderWindow& window, std::vector<Planet>& planets);
void Update(std::vector<Planet>& planets);
void drawPlanetPixels(sf::RenderWindow& window, Planet& planet);

//how often the computer refreshes the window per second
int frameRate = 100;

int planetTrailLength = 50;

//how many frame the trail will exist
int trailLifeSpan = 10;

double dTheta = 1 / ((double)frameRate);

std::vector<Planet> planets;

double sunRadius = 50.0;
int planetRadius = 10;

//screen dimensions
int scrX(1200), scrY(800);
Vector2d screenSize;

//constructors of functions present in main to be used later, defined at the end of the code

//-------------------------------------------------MAIN FUNCTION-----------------------------------------------------------//
int main()
{
	screenSize.setXY(scrX, scrY);
	sf::RenderWindow window(sf::VideoMode(screenSize.x, screenSize.y), "Orbits");
	window.setFramerateLimit(frameRate);

	//better sun shape
	sf::Texture texture;
	if (!texture.loadFromFile("assets/sun.png")) 
	{
		std::cout << "could not load bruh";
		return 0;
	}
	sf::Sprite sunSprite;
	sunSprite.setTexture(texture);
	sunSprite.setScale(0.3, 0.3);
	sunSprite.setPosition(scrX / 2 - sunRadius - 7, scrY / 2 - sunRadius - 7);

	//outerspace
	sf::Texture textureSpace;
	if (!textureSpace.loadFromFile("assets/outerspace.jpg"))
	{
		std::cout << "could not load space";
		return 0;
	}
	sf::Sprite spaceSprite;
	spaceSprite.setTexture(textureSpace);
	spaceSprite.setScale(1.579, 1.874);
	

	int holdCount = 0;

	Clicking checkClick;
	while (window.isOpen())
	{
		//SFML stuff. This block just means that if we press escape or hit the close window button on the window, close the window.
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.KeyPressed && event.key.code == sf::Keyboard::Escape)
				window.close();
		}

		if (checkClick.isClicking(event, holdCount))
		{
			double mouseX, mouseY;
			mouseX = sf::Mouse::getPosition(window).x;
			mouseY = sf::Mouse::getPosition(window).y;

			sf::CircleShape circle(planetRadius);
			circle.setFillColor(sf::Color::Blue);
			circle.setPosition(mouseX, mouseY);
			Planet newPlanet(circle, mouseX, mouseY, screenSize.x, screenSize.y, sunRadius);

			planets.push_back(newPlanet);			
		}

		Update(planets);
		Draw(window, planets, sunSprite, spaceSprite);
	}
}

void Update(std::vector<Planet>& planets)
{
	for (Planet& i : planets)
	{
		sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(3, 3));
		rect.setFillColor(sf::Color::Red);
		rect.setPosition(i.planet.getPosition().x, i.planet.getPosition().y);

		i.pixels.push_back(rect);

		if (i.pixels.size() > planetTrailLength)
		{
			i.pixels.erase(i.pixels.begin(), i.pixels.begin() + 1);
		}
	}

	for (Planet& i : planets)
	{
		i.theta += dTheta;
		i.planet.setPosition(
			screenSize.x/2 + cos(i.theta) * i.orbitRadius,
			screenSize.y/2 + sin(i.theta) * i.orbitRadius
		);
	}
}


void Draw(sf::RenderWindow& window, std::vector<Planet>& planets, sf::Sprite& sunSprite, sf::Sprite& spaceSprite)
{
	window.clear();
	window.draw(spaceSprite);
	window.draw(sunSprite);
	drawPlanets(window, planets);
	window.display();
}

void drawPlanets(sf::RenderWindow& window, std::vector<Planet>& planets)
{
	for (Planet i : planets)
	{
		drawPlanetPixels(window, i);
		window.draw(i.planet);
	}
}

void drawPlanetPixels(sf::RenderWindow& window, Planet& planet)
{
	for (sf::RectangleShape rect : planet.pixels)
	{
		window.draw(rect);
	}
}