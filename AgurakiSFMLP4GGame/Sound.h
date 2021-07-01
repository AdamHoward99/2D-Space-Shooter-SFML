#pragma once
#include "SFML/Audio.hpp"

class Sound
{
public:
	void setupSounds();
	sf::Music introMusic;
	sf::Music gameMusic;
	sf::Music gameoverMusic;
};
