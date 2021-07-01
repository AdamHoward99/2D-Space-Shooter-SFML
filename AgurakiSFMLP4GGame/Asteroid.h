#pragma once
#include "SFML/Graphics.hpp"

class Asteroid
{
public:
	void init();
	void Update();
	~Asteroid();

	sf::Sprite asteroid;
	bool active = false;
	bool increaseSpeed1 = false;
	bool increaseSpeed2 = false;
	float time = 0;
private:
	sf::Texture asteroidTex;
};