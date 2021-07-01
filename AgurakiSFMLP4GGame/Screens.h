#pragma once
#include "SFML/Graphics.hpp"
#include "GameData.h"

class Screens
{
public:
	void initIntroMode(GameData& gdata);
	void introRender(GameData& gdata);
	void controlRender(GameData& gdata);
	void highScoreRender(GameData& gdata);
	void gameOverMode(GameData& gdata);
	void gameOverRender(GameData& gdata);
	~Screens();
private:
	sf::Sprite intro;
	sf::Sprite gameover;
	sf::Sprite title;
	sf::Sprite gameoverTitle;
	sf::Sprite endTitle;

	//Intro mode textures
	sf::Texture introTitleTex;
	sf::Texture introTex;
	sf::Texture goverTitleTex;
	sf::Texture goverTex;
};