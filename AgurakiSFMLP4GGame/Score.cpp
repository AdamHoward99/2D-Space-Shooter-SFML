#include "Score.h"

int Score::getScore()
{
	return score;
}

void Score::addScore()
{
	score += 40;
}

Score::~Score()
{}