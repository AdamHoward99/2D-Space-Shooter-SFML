#include "GameApplication.h"
#include "GameObject.h"
#include "GameData.h"

void GameApplication::init(GameApplication& game)
{
	GameObject gameObj;
	GameData gdata;
	gdata.window.create(sf::VideoMode((int)gdata.width, (int)gdata.height), "Aguraki SFML");
	gdata.text.setCharacterSize(GameData::PRINT_FONTSIZE);
	gameState = IntroMode;
	
	//Initialise stuff here
	gameObj.soundMgr.setupSounds();
	gameObj.menuScreens.initIntroMode(gdata);		//Initialise the intro background and title
	gameObj.menuScreens.gameOverMode(gdata);		//Initialise the gameover background and title
	gameObj.game.initBgnd();
	gameObj.game.initPlayer();
	gameObj.game.mPlayer.mMissile.init();
	gameObj.game.initAsteroids();
	gameObj.game.initEnemy();
	gameObj.soundMgr.introMusic.play();
	gameObj.soundMgr.introMusic.setVolume(50.f);
	gameObj.soundMgr.introMusic.setLoop(true);
	game.run(game, gdata, gameObj);
}

void GameApplication::run(GameApplication& game, GameData& gdata, GameObject& gameObj)
{

	while (gdata.window.isOpen())
	{
		char command = 0;
		bool enter = false;
		sf::Vector2f playerPos(0, 0);
		sf::Event event;

		gdata.window.setFramerateLimit(60);
		while (gdata.window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)	gameState = game.Quit;
			if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode == GameData::ASCII_ESCAPE)	gameState = game.Quit;
				else if (isalpha(event.text.unicode))	command = toupper(event.text.unicode);
				else if (isdigit(event.text.unicode))	command = toupper(event.text.unicode);
				else if (event.text.unicode == GameData::ASCII_ENTER)	enter = true;

				if (toupper(event.text.unicode) == GameData::ASCII_C && gameState == states::IntroMode) { gameState = game.Controls; lastState = game.IntroMode; }		//Going to the control menu from the intro menu
				if (toupper(event.text.unicode) == GameData::ASCII_B && (gameState != states::IntroMode && gameState != states::Play && gameState != states::GameOverScreen))	gameState = lastState;			//Goes back to the previous screen when not on the intro screen
				if (toupper(event.text.unicode) == GameData::ASCII_H && (gameState == states::IntroMode)) { gameState = game.HighScoreTable; lastState = game.IntroMode; }	//Going to the highscore menu from the intro menu
				if (toupper(event.text.unicode) == GameData::ASCII_H && (gameState == states::GameOverScreen)) { gameState = game.HighScoreTable; lastState = game.GameOverScreen;}		//Going to the highscore menu from the gameover menu
				if (toupper(event.text.unicode == GameData::ASCII_S && gameState == states::IntroMode))		//Starts the game when pressing 'S' on the intro mode
				{
					gameObj.soundMgr.introMusic.stop();
					gameObj.soundMgr.gameMusic.play();
					gameObj.soundMgr.gameMusic.setLoop(true);
					gameObj.soundMgr.gameMusic.setVolume(50.f);
					gameState = game.Play;			
				}
				if (toupper(event.text.unicode) == GameData::ASCII_R && gameState == states::GameOverScreen) { gameState = game.IntroMode; gameObj.game.restartGame(); gameObj.soundMgr.gameoverMusic.stop(); gameObj.soundMgr.introMusic.play(); gameObj.soundMgr.introMusic.setVolume(50.f); }

			}
		}
		gdata.window.clear();
		gdata.text.setFont(gdata.font);

		//Switch statement for switching states of the game
		switch (gameState)
		{
		case game.IntroMode:
			gameObj.menuScreens.introRender(gdata);
			break;
		case game.Play:
			gameObj.game.mPlayer.Update(playerPos);	//Updates the players movement each frame
			if (gameObj.game.mPlayer.mMissile.active)	gameObj.game.mPlayer.mMissile.update();
			gameObj.game.updateAsteroids(gdata);
			gameObj.game.updateEnemy(gdata);
			gameObj.game.Render(gdata);
			if (gameObj.game.hasDied)
			{
				gameState = game.GameOverScreen;
				gameObj.soundMgr.gameMusic.stop();
				gameObj.soundMgr.gameoverMusic.play();
				gameObj.soundMgr.gameoverMusic.setLoop(true);
				gameObj.soundMgr.gameoverMusic.setVolume(50.f);
			}
			break;
		case game.Controls:
			gameObj.menuScreens.controlRender(gdata);
			break;
		case game.HighScoreTable:
			gameObj.menuScreens.highScoreRender(gdata);
			break;
		case game.GameOverScreen:
			gameObj.menuScreens.gameOverRender(gdata);
			break;
		case game.Quit:
			gdata.window.close();
			break;
		}

    gdata.window.display();
	}
}

GameApplication::~GameApplication()
{}
