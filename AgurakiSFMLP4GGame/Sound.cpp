#include "Sound.h"
#include "SFML/Audio.hpp"
#include "assert.h"

void Sound::setupSounds()
{
	if (!introMusic.openFromFile("music/intro.ogg"))	assert(false);
	if (!gameMusic.openFromFile("music/play.ogg"))	assert(false);
	if (!gameoverMusic.openFromFile("music/gameover.ogg"))	assert(false);
}