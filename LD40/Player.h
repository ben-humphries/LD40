#pragma once
#include "GameObject.h"
#include "Light.h"
#include "Game.h"
#include "SFML\Audio.hpp"

class Player : public GameObject
{
public:
	Player();
	~Player();

	void update(float dt);
	void handleInput(sf::Event e);

	const float speed = 200;
	sf::Vector2f velocity = sf::Vector2f(0, 0);

	bool movingRight, movingLeft;
	bool movingUp, movingDown;

	Light light;
	float lightIntensity;
	const float lightScrollSpeed = 0.01;

	float currentTime;

	sf::SoundBuffer footstepBuffer;
	sf::Sound footstep;


};

