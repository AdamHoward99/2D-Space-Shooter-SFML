#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
#include "GameData.h"
#include "Score.h"
#include "Player.h"
#include "Asteroid.h"
#include "Enemy.h"
#include "Sound.h"

using namespace std;

class Game
{
public:
	void initBgnd();
	void initPlayer();
	void initAsteroids();
	void initEnemy();

	void updateAsteroids(GameData& gdata);
	void updatePlayer(sf::Vector2f playerPos);
	void updateEnemy(GameData& gdata);

	Asteroid* spawnAsteroid(GameData& gdata);
	Asteroid *checkCollisionAsteroids(Asteroid& me);

	Enemy* spawnEnemy(GameData& gdata);
	Enemy *checkCollisionEnemy(Enemy& me);

	void Render(GameData& gdata);
	float GetRandom(float min, float max);

	void storeScore();
	void restartGame();
	~Game();
	
	//Player class
	Player mPlayer;	
	
	//Asteroid class
	Asteroid mAsteroid;
	bool hasDied = false;

	//Enemy Class
	Enemy mEnemy;
private:
	sf::Sprite mBgnd;
	sf::Texture backgroundTex;

	std::vector<Asteroid> asteroids;
	std::vector<Enemy> enemies;

	//Asteroid spawning stuff
	float SpawnRateSec = 100.f;
	float lastSpawn = 0;
	float currentRate = 200;

	//Enemy spawning stuff
	float spawnrate = 100.f;
	float lastSpawnEnemy = 0;
	float currentRateEnemy = 200;

	//Score class
	Score score;
};