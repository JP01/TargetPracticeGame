#include "Actor.h"
#include <iostream>
#include <utility>

Actor::Actor()
{
	Actor(sf::Vector2f(400, 0), "ActorDefault");
}


Actor::Actor(sf::Vector2f startingPosition, std::string textureFilePath)
	: mPosition(sf::Vector2f(400,0))
	, mStartingPosition(startingPosition)
	, mSpeed(400.0f)
{
	if (!mTexture.loadFromFile(textureFilePath)) {
		std::cerr << "Error loading actor texture" << std::endl;
		// Handle the error in some way
	}
	
	mSprite.setTexture(mTexture);
	mSprite.setOrigin(mTexture.getSize().x / 2, mTexture.getSize().y / 2);
	mPosition = mStartingPosition;
}


sf::Sprite Actor::getSprite()
{
	return mSprite;
}


void Actor::setSpriteOrigin(sf::Vector2f origin)
{
	mSprite.setOrigin(origin);
}

void Actor::moveLeft()
{
	mMovingLeft = true;
}


void Actor::moveRight()
{
	mMovingRight = true;
}


void Actor::moveUp()
{
	mMovingUp = true;
}


void Actor::moveDown()
{
	mMovingDown = true;
}


sf::Vector2f Actor::getPosition()
{
	return mPosition;
}


void Actor::resetPosition()
{
	mResetPosition = true;
}


void Actor::setSpeed(float newSpeed)
{
	mSpeed = newSpeed;
}


void Actor::aimAt(sf::Vector2f aimPosition)
{
	float dx = mPosition.x - aimPosition.x;
	float dy = mPosition.y - aimPosition.y;
	float rotation = (atan2f(dy, dx)) * 180 / PI;
	mSprite.setRotation(rotation);
}


void Actor::update(float elapsedTime)
{
	mMovementBinding[MoveLeft] = sf::Vector2f(-mSpeed, 0);
	mMovementBinding[MoveRight] = sf::Vector2f(mSpeed, 0);
	mMovementBinding[MoveUp] = sf::Vector2f(0, -mSpeed);
	mMovementBinding[MoveDown] = sf::Vector2f(0, mSpeed);
	// Loop over the movement mapping
	if (mMovingLeft) {
		mPosition += mMovementBinding[MoveLeft] * elapsedTime;
		mMovingLeft = false;
	}
	if (mMovingRight) {
		mPosition += mMovementBinding[MoveRight] * elapsedTime;
		mMovingRight = false;
	}
	if (mMovingUp) {
		mPosition += mMovementBinding[MoveUp] * elapsedTime;
		mMovingUp = false;
	}
	if (mMovingDown) {
		mPosition += mMovementBinding[MoveDown] * elapsedTime;
		mMovingDown = false;
	}
	if (mResetPosition) {
		mPosition = mStartingPosition;
		mResetPosition = false;
	}
	mSprite.setPosition(mPosition);
}


sf::FloatRect Actor::getBoundingBox()
{
	return mSprite.getGlobalBounds();
}


Actor::~Actor()
{
}