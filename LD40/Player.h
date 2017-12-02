#pragma once
#include "GameObject.h"

class Player : public GameObject
{
public:
	Player();
	~Player();

	void update(float dt);
	void handleInput(sf::Event e);

	const float speed = 500;
	sf::Vector2f velocity = sf::Vector2f(0, 0);
};

