#include "Game.h"
#include "assert.h"
#include "time.h"

#include <iomanip>
#include <sstream>
#include <fstream>

using namespace std;

void Game::initBgnd()
{
	if (!backgroundTex.loadFromFile("data/SpaceBackground.png"))	assert(false);
	mBgnd.setTexture(backgroundTex);
	mBgnd.setPosition(sf::Vector2f(0, 0));
}

void Game::initPlayer()
{
	mPlayer.init();
}

void Game::initAsteroids()
{
	asteroids.insert(asteroids.begin(), 40, mAsteroid);
	for (int i = 0; i < 40; i++)
	{
		asteroids.at(i).init();
	}
}

void Game::restartGame()
{
	hasDied = false;
	score.score = 0;

	//Reset asteroids when restarting
	asteroids.clear();
	initAsteroids();

	//Reset enemies when restarting
	enemies.clear();
	initEnemy();

	mPlayer.mMissile.active = false;
	mPlayer.mPlayer.setPosition(sf::Vector2f(100.f, 200.f));
}

void Game::updateAsteroids(GameData& gdata)
{
	assert(!asteroids.empty());
	float radius = 10;	//Figure out what this does

	for (auto& a : asteroids)
		a.Update();
	
	if ((currentRate - lastSpawn) > SpawnRateSec)
	{
		if (spawnAsteroid(gdata))
		{
			lastSpawn = 30.f;
			currentRate = 100;
		}
	}
	currentRate++;

	size_t i = 0;
	while (i < asteroids.size())
	{
		Asteroid& collider = asteroids.at(i);
		//When a missile collides with an asteroid
		if (collider.active && ((collider.asteroid.getPosition().x - mPlayer.mMissile.bullet.getPosition().x) < 70) && (collider.asteroid.getPosition().y - mPlayer.mMissile.bullet.getPosition().y) < 30 
			&& (collider.asteroid.getPosition().y - mPlayer.mMissile.bullet.getPosition().y) > -40)
		{
			score.addScore();			//Adds 40 to the score
			collider.asteroid.setPosition(sf::Vector2f(100, -100));
			mPlayer.mMissile.bullet.setPosition(sf::Vector2f(100, -200));
			mPlayer.mMissile.active = false;
			collider.active = false;
		}

		//When the player collides with an asteroid
		if (collider.active && (collider.asteroid.getPosition().x - mPlayer.mPlayer.getPosition().x) < 30 && (collider.asteroid.getPosition().x - mPlayer.mPlayer.getPosition().x) > -20 
			&& (collider.asteroid.getPosition().y - mPlayer.mPlayer.getPosition().y) < 40 && (collider.asteroid.getPosition().y - mPlayer.mPlayer.getPosition().y) > -60)
		{
			hasDied = true;
			storeScore();
			collider.asteroid.setPosition(sf::Vector2f(100, -100));
			collider.active = false;
			mPlayer.mPlayer.setPosition(sf::Vector2f(200, -100));
			return;
		}

		i++;
	}
}

void Game::updatePlayer(sf::Vector2f playerPos)
{
	if(!hasDied)
		mPlayer.Update(playerPos);
}

void Game::Render(GameData& gdata)
{
	gdata.window.draw(mBgnd);
	gdata.window.draw(mPlayer.mPlayer);
	if (mPlayer.mMissile.active)	gdata.window.draw(mPlayer.mMissile.bullet);

	for (size_t i = 0; i < asteroids.size(); i++)
	{
		if(asteroids.at(i).active)
			gdata.window.draw(asteroids.at(i).asteroid);
	}

	for (size_t i = 0; i < enemies.size(); i++)
	{
		if (enemies.at(i).active)
			gdata.window.draw(enemies.at(i).enemy);
	}

	std::stringstream scoreText;
	scoreText << "Score  " << score.getScore();
	string scoreTxt = scoreText.str();

	float w = gdata.width, h = gdata.height;
	gdata.text.setFont(gdata.font);
	gdata.text.setString(scoreTxt);
	gdata.text.setPosition(620, 510);
	gdata.window.draw(gdata.text);
}

Asteroid* Game::spawnAsteroid(GameData& gdata)
{
	assert(!asteroids.empty());
	size_t i = 0;
	Asteroid*p = nullptr;
	while (i < asteroids.size() && !p)
	{
		if (!asteroids[i].active)
			p = &asteroids[i];
		i++;
	}

	if (p)
	{
		sf::Vector2f pos = p->asteroid.getPosition();
		pos.y = (float)GetRandom(0, (gdata.height - 50));
		pos.x = (float)GetRandom(gdata.width, (gdata.width + 250));
		p->asteroid.setPosition(sf::Vector2f(pos.x, pos.y));
		bool collision = false;
		if (checkCollisionAsteroids(*p))
			collision = true;
		if (!collision)
			p->active = true;
		else
			p = nullptr;
	} 
		return p;
}

Asteroid *Game::checkCollisionAsteroids(Asteroid& me)
{
	assert(!asteroids.empty());
	size_t i = 0;
	Asteroid *pColl = nullptr;
	while (i < asteroids.size() && !pColl)
	{
		Asteroid& collider = asteroids.at(i);
		if ((&me != &collider) && collider.active && (collider.asteroid.getPosition().x - me.asteroid.getPosition().x) < 55 && (collider.asteroid.getPosition().x - me.asteroid.getPosition().x) > -55
			&& (collider.asteroid.getPosition().y - me.asteroid.getPosition().y) < 55 && (collider.asteroid.getPosition().y - me.asteroid.getPosition().y) > -55)
			pColl = &asteroids.at(i);
		i++;
	}
	return pColl;
}

void Game::storeScore()
{
	vector<int> scores(5);
	ifstream fin;
	fin.open("scores.txt", ios::out);
	if (fin.fail())
	{
		ofstream fout("scores.txt");
		if (fout.fail())	assert(false);
		else
		{
			fout << score.score;
			fout.close();
		}
	}
	else
	{
		int previousScore;
		fin >> scores.at(0) >> scores.at(1) >> scores.at(2) >> scores.at(3) >> scores.at(4);
		ofstream fout("scores.txt", ios::out);
		if (fout.fail())	assert(false);
		else
		{
			for (int i = 4; i > -1; i--)
			{
				if (score.score >= scores.at(i))
				{
					previousScore = scores.at(i);
					scores.at(i) = score.score;
					if (i < 4)
						scores.at(i + 1) = previousScore;
				}
			}

			fout << scores.at(0) << "\n" << scores.at(1) << "\n" << scores.at(2) << "\n" << scores.at(3) << "\n" << scores.at(4) << "\n";
			fout.close();
		}
	}
}

void Game::initEnemy()
{
	enemies.insert(enemies.begin(), 20, mEnemy);
	for (int i = 0; i < 20; i++)
	{
		enemies.at(i).init();
	}
}

void Game::updateEnemy(GameData& gdata)
{
	assert(!enemies.empty());
	for (auto& e : enemies)
		e.update();

	if ((currentRateEnemy - lastSpawnEnemy) > spawnrate)
	{
		if (spawnEnemy(gdata))
		{
			lastSpawnEnemy = 100.f;
			currentRateEnemy = 100;
		}
	}
	currentRateEnemy++;

	size_t i = 0;
	while (i < enemies.size())
	{
		Enemy& collider = enemies.at(i);

		//When a missile collides with an enemy
		if (collider.active && ((collider.enemy.getPosition().x - mPlayer.mMissile.bullet.getPosition().x) < 50) && (collider.enemy.getPosition().y - mPlayer.mMissile.bullet.getPosition().y) < 20
			&& (collider.enemy.getPosition().y - mPlayer.mMissile.bullet.getPosition().y) > -60)
		{
			score.addScore();
			collider.enemy.setPosition(sf::Vector2f(100, -100));
			mPlayer.mMissile.bullet.setPosition(sf::Vector2f(100, -200));
			mPlayer.mMissile.active = false;
			collider.active = false;
		}

		//When the player collides with an enemy
		if (collider.active && (collider.enemy.getPosition().x - mPlayer.mPlayer.getPosition().x) < 20 && (collider.enemy.getPosition().x - mPlayer.mPlayer.getPosition().x) > -20
			&& (collider.enemy.getPosition().y - mPlayer.mPlayer.getPosition().y) < 10 && (collider.enemy.getPosition().y - mPlayer.mPlayer.getPosition().y) > -60)
		{
			hasDied = true;
			storeScore();
			collider.enemy.setPosition(sf::Vector2f(100, -100));
			collider.active = false;
			mPlayer.mPlayer.setPosition(sf::Vector2f(200, -100));
			return;
		}
		i++;
	}
}

Enemy* Game::spawnEnemy(GameData& gdata)
{
	assert(!enemies.empty());
	size_t i = 0;
	Enemy*e = nullptr;
	while (i < enemies.size() && !e)
	{
		if (!enemies.at(i).active)
			e = &enemies.at(i);
		i++;
	}

	if (e)
	{
		sf::Vector2f pos = e->enemy.getPosition();
		pos.y = (float)GetRandom(0, (gdata.height - 50));
		pos.x = (float)GetRandom(gdata.width, (gdata.width + 250));
		e->enemy.setPosition(sf::Vector2f(pos.x, pos.y));
		bool collision = false;
		if (checkCollisionEnemy(*e))
			collision = true;
		if (!collision)
			e->active = true;
		else
			e = nullptr;
	}
	return e;
}

Enemy *Game::checkCollisionEnemy(Enemy& me)
{
	assert(!enemies.empty());
	size_t i = 0;
	Enemy *eColl = nullptr;
	while (i < enemies.size() && !eColl)
	{
		Enemy& collider = enemies.at(i);
		if ((&me != &collider) && collider.active && (collider.enemy.getPosition().x - me.enemy.getPosition().x) < 55 && (collider.enemy.getPosition().x - me.enemy.getPosition().x) > -55
			&& (collider.enemy.getPosition().y - me.enemy.getPosition().y) < 55 && (collider.enemy.getPosition().y - me.enemy.getPosition().y) > -55)
			eColl = &enemies.at(i);
		i++;
	}
	return eColl;
}

float Game::GetRandom(float min, float max)
{
	float res = (float)rand() / RAND_MAX;
	res = min + res * (max - min);
	return res;
}

Game::~Game()
{}
