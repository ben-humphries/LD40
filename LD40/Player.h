#pragma once
#include "GameObject.h"
#include "Light.h"
#include "Game.h"

class Player : public GameObject
{
public:
	Player();
	~Player();

	void update(float dt);
	void handleInput(sf::Event e);

	const float speed = 300;
	sf::Vector2f velocity = sf::Vector2f(0, 0);

	bool movingRight, movingLeft;
	bool movingUp, movingDown;

	Light light;
	float lightIntensity;
	const float lightScrollSpeed = 0.01;

};

