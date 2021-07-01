#pragma once
#include "SFML/Graphics.hpp"

struct GameData
{
	sf::RenderWindow window;
	sf::Text text;
	sf::Font font;
	const float width = 800;
	const float height = 600;
	const float borderSize = 12;
	const float margin = 50;
	unsigned int p1Score = 0, p2Score = 0;
	enum
	{
		PRINT_OFFSETX = 100,
		PRINT_OFFSETY = 50,
		PRINT_LINEINC = 50,
		PRINT_FONTSIZE = 30
	};

	enum
	{
		ASCII_ENTER = 13,
		ASCII_ESCAPE = 27,
		ASCII_UP = 24,
		ASCII_DOWN = 25,
		ASCII_S = 115,
		ASCII_C = 67,
		ASCII_H = 72,
		ASCII_B = 66,
		ASCII_DOWNARROW = 40,
		ASCII_UPARROW = 38,
		ASCII_LEFTARROW = 37,
		ASCII_RIGHTARROW = 39,
		ASCII_R = 82
	};
};

struct Vec2f
{
	float x, y;
};