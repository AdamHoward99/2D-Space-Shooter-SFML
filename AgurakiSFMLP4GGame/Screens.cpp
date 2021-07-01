#include "Screens.h"
#include "assert.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>

using namespace std;

void Screens::initIntroMode(GameData& gdata)
{
	if (!introTex.loadFromFile("data/Intro.png")) assert(false);
	intro.setTexture(introTex);
	intro.setScale(sf::Vector2f(0.5f, 0.5f));
	intro.setPosition(sf::Vector2f(0, 0));
	
	if (!introTitleTex.loadFromFile("data/TitleImage.png")) assert(false);
	title.setTexture(introTitleTex);
	title.setScale(sf::Vector2f(0.75f, 0.75f));
	title.setPosition(sf::Vector2f(200.f, 120.f));

	if (!gdata.font.loadFromFile("data/arcadeclassic.ttf"))	assert(false);
}

void Screens::introRender(GameData& gdata)
{
	gdata.window.draw(intro);
	gdata.window.draw(title);
	string txt = " Press S to start the game\n\n Press H to view highscore table\n\n Press C to view the controls\n\n Press Escape to exit the game";
	float w = gdata.width, h = gdata.height;
	gdata.text.setFont(gdata.font);
	gdata.text.setString(txt);
	gdata.text.setPosition(w / 4.f, h / 3.f);
	gdata.window.draw(gdata.text);
}

void Screens::controlRender(GameData& gdata)
{
	gdata.window.draw(intro);
	string txt = "Use the arrow keys to move the ship around\n the screen\n\nUse the space key to fire a missile towards\n the enemies\n\nPress B to go back";
	float w = gdata.width, h = gdata.height;
	gdata.text.setFont(gdata.font);
	gdata.text.setString(txt);
	gdata.text.setPosition(100, h / 3.f);
	gdata.window.draw(gdata.text);
}

void Screens::highScoreRender(GameData& gdata)
{
	gdata.window.draw(intro);
	stringstream highScoreTb;

	//Get scores from scores.txt
	ifstream fin;
	vector<int> scores(5);
	fin.open("scores.txt", ios::out);
	if (fin.fail())	assert(false);
	else
		fin >> scores.at(0) >> scores.at(1) >> scores.at(2) >> scores.at(3) >> scores.at(4);
	fin.close();

	highScoreTb << "High Score Table\n\n" 
				<< "1st  " << scores.at(0)
				<< "\n2nd  " << scores.at(1)
				<< "\n3rd  " << scores.at(2)
				<< "\n4th  " << scores.at(3)
				<< "\n5th  " << scores.at(4)
				<< "\n\nPress B to go back";

	string hsTable = highScoreTb.str();
	gdata.text.setFont(gdata.font);
	gdata.text.setString(hsTable);
	gdata.text.setPosition(300.f, 200.f);
	gdata.window.draw(gdata.text);
}

void Screens::gameOverMode(GameData& gdata)
{
	if (!goverTex.loadFromFile("data/gameOver.png"))	assert(false);
	gameover.setTexture(goverTex);
	gameover.setScale(sf::Vector2f(1.3f, 1.3f));
	gameover.setPosition(sf::Vector2f(0.f, 0.f));

	if (!goverTitleTex.loadFromFile("data/GameOverTitle.png"))	assert(false);
	gameoverTitle.setTexture(goverTitleTex);
	gameoverTitle.setScale(sf::Vector2f(0.75f, 0.75f));
	gameoverTitle.setPosition(sf::Vector2f(150.f, 100.f));
}

void Screens::gameOverRender(GameData& gdata)
{
	gdata.window.draw(gameover);
	gdata.window.draw(gameoverTitle);
	string s = " Press R to restart the game\n\nPress H to view the highscore table";
	gdata.text.setPosition(sf::Vector2f(150.f, 200.f));
	float w = gdata.width, h = gdata.height;
	gdata.text.setFont(gdata.font);
	gdata.text.setString(s);
	gdata.window.draw(gdata.text);
}

Screens::~Screens()
{}