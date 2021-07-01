#include "Enemy.h"
#include "assert.h"

void Enemy::init()
{
	if (!enemyTex.loadFromFile("data/enemyShip.png"))	assert(false);
	enemy.setTexture(enemyTex);
	enemy.setScale(sf::Vector2f(0.15f, 0.15f));
	enemy.setOrigin(sf::Vector2f(100.f, 0.f));
	active = false;
}

void Enemy::update()
{
	if (active)
	{
		enemy.move(-3, 0);

		if (enemy.getPosition().x < -10)
			active = false;
	}
}

Enemy::~Enemy()
{}