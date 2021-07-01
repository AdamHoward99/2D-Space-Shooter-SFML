#include "Asteroid.h"
#include "assert.h"
#include "SFML/Graphics.hpp"

void Asteroid::init()
{
	if (!asteroidTex.loadFromFile("data/asteroid.png"))	assert(false);
	asteroid.setTexture(asteroidTex);
	asteroid.setScale(sf::Vector2f(0.7f, 0.7f));
	asteroid.setOrigin(sf::Vector2f(100, 0));	//Might need to change once collision is in the game
	active = false;
	time = 0;
}

void Asteroid::Update()
{
	if (time == 10000)	increaseSpeed1 = true;
	else if (time == 1000000) { increaseSpeed2 = true;	increaseSpeed1 = false; }

	if (active)
	{
		//Move the missile
		if(!increaseSpeed1)	asteroid.move(-2, 0);		//Default speed for the asteroids
		if (increaseSpeed1)	asteroid.move(-4, 0);		//Increase speed of asteroids
		if (increaseSpeed2)	asteroid.move(-6, 0);		//Further increase speed the speed of asteroids

		//Make the asteroid inactive when it hits the end of the screen (left)
		if (asteroid.getPosition().x < -10)
		{
			active = false;
		}
	}
	time++;
}

Asteroid::~Asteroid()
{}