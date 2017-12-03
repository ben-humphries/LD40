#pragma once
#include "GameObject.h"
#include "Light.h"
#include "Game.h"
#include "SFML\Audio.hpp"
#include "Animation.h"
#include "Enemy.h"

class Player : public GameObject
{
public:
	Player();
	~Player();

	void update(float dt);
	void handleInput(sf::Event e);
	void wakeEnemy(Enemy * enemy);

	const float speed = 100;
	sf::Vector2f velocity = sf::Vector2f(0, 0);

	bool movingRight, movingLeft;
	bool movingUp, movingDown;

	float lightIntensity;
	const float lightScrollSpeed = 0.03;

	sf::SoundBuffer footstepBuffer;
	sf::Sound footstep;

	std::vector<Animation*> animations;

	enum AnimationState {IdleUp, IdleDown, IdleRight, IdleLeft, WalkUp, WalkDown, WalkRight, WalkLeft };
	AnimationState animationState;

	const int lightRadius = 1920 - 900;

};

