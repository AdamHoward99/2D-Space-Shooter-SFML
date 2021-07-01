#include "Player.h"
#include "assert.h"

void Player::init()
{
	if (!playerTex.loadFromFile("data/ship.png"))	assert(false);
	mPlayer.setTexture(playerTex);
	mPlayer.setScale(sf::Vector2f(0.05f, 0.05f));
	mPlayer.setPosition(sf::Vector2f(100.f, 200.f));
	mPlayer.setOrigin(sf::Vector2f(800, 400));	//might need changing based on collision
	mPlayer.setRotation(90);
}

void Player::Update(sf::Vector2f playerPos)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))	playerPos = sf::Vector2f(0, -8.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))	playerPos = sf::Vector2f(0, 8.f);

	mPlayer.move(playerPos);

	if (mPlayer.getPosition().y < 30)			//Keeping player in the upper boundary of the play area
		mPlayer.setPosition(sf::Vector2f(mPlayer.getPosition().x, 30));

	if (mPlayer.getPosition().y > 580)
		mPlayer.setPosition(sf::Vector2f(mPlayer.getPosition().x, 580));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !mMissile.active)
	{	
		mMissile.active = true;
		mMissile.bullet.setPosition(sf::Vector2f(mPlayer.getPosition().x + 10, mPlayer.getPosition().y + 2));
	}
}

Player::~Player()
{}