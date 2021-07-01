#include "Bullet.h"
#include "assert.h"
#include "SFML/Graphics.hpp"

void Bullet::init()
{
	if (!bulletTex.loadFromFile("data/missile.png"))	assert(false);
	bullet.setTexture(bulletTex);
	bullet.setScale(sf::Vector2f(0.65f, 0.65f));
	bullet.setOrigin(sf::Vector2f(10.f, 15.f));	//Might need changing once collision is in game
	active = false;
}

void Bullet::update()
{
	if (active)
	{
		//Move the missile
		bullet.move(6, 0);
		
		//Make the missile inactive when it hits the rect at the end of the screen
		if (bullet.getPosition().x > 800)
		{
			active = false;
			bullet.setPosition(sf::Vector2f(0, 0));		//TESTING change to players position
		}
	}
}

Bullet::~Bullet()
{}