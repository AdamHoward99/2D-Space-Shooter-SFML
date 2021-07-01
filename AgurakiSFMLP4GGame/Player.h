#pragma once
#include "SFML/Graphics.hpp"
#include "Bullet.h"

class Player
{
public:
	void init();
	void Update(sf::Vector2f playerPos);
	sf::Sprite mPlayer;
	Bullet mMissile;
	~Player();

private:
	sf::Texture playerTex;
};