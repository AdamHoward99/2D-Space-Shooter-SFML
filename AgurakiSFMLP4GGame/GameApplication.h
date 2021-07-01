#pragma once
#include "GameData.h"
#include "GameObject.h"

class GameApplication
{
public:
	enum states
	{
		IntroMode,
		GOverMode,
		Controls,
		HighScoreTable,
		GameOverScreen,
		Play, 
		Quit
	};
	void init(GameApplication& game);
	void run(GameApplication& game, GameData& gdata, GameObject& gameobj);
	~GameApplication();
private:
	int gameState = IntroMode;
	int lastState;
};