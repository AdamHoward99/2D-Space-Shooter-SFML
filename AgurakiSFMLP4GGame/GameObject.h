#pragma once
#include "GameData.h"
#include "Screens.h"
#include "Game.h"
#include "Sound.h"

class GameObject
{
public:
	GameData gdata;
	~GameObject();
	Screens menuScreens;
	Game game;
	Sound soundMgr;
};