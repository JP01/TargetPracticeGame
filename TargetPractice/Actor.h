#pragma once
#include <math.h>
#include <memory>
#include <SFML/Graphics.hpp>


class Actor
{
public:
	// Constants
	const float PI = 3.14159265;

	// Construction
	Actor();
	Actor(sf::Vector2f startingPosition, std::string textureFilePath);
	~Actor();

	// Return a copy of the actor sprite
	sf::Sprite getSprite();

	// Sets the origin point around which rotation should be applied
	void setSpriteOrigin(sf::Vector2f origin);

	void moveLeft(); // Move the actor left
	void moveRight(); // Move the actor right
	void moveUp(); // Move the actor up
	void moveDown(); // Move the actor down
	
	// Get the position of the actor
	sf::Vector2f getPosition();

	// Reset the position of the actor to its starting position
	void resetPosition();

	// Set the speed of the actor in pixels per second
	void setSpeed(float newSpeed);


	void aimAt(sf::Vector2f aimPosition); // Aim the actor towards a location

	// Called every frame to update logic
	void update(float elapsedTime);

	// Bounding box of the actor, for collision detection
	sf::FloatRect getBoundingBox();

private:
	// Current position of the Actor
	sf::Vector2f mPosition;

	// Actor movement mapping
	enum MovementAction
	{
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown,
	};
	bool mMovingLeft;
	bool mMovingRight;
	bool mMovingUp;
	bool mMovingDown;
	bool mResetPosition;
	std::map<MovementAction, sf::Vector2f> mMovementBinding;

	// Speed of the actor in pixels/second
	float mSpeed;

	// Sprite for the actor
	sf::Sprite mSprite;

	// Texture for the sprite
	sf::Texture mTexture;

protected:
	// Starting position of the actor
	sf::Vector2f mStartingPosition;
};

