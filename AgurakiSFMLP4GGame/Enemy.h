#pragma once
#include "SFML/Graphics.hpp"

class Enemy
{
public:
	void init();
	void update();
	~Enemy();
	sf::Sprite enemy;
	bool active = false;
private:
	sf::Texture enemyTex;
};