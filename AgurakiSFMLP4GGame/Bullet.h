#pragma once
#include "SFML/Graphics.hpp"

class Bullet
{
public:
	void init();
	void update();
	~Bullet();

	bool active = false;
	sf::Sprite bullet;
private:
	sf::Texture bulletTex;
};