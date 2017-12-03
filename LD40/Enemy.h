#pragma once
#include "GameObject.h"
class Enemy :
	public GameObject
{
public:
	Enemy(std::string dir, sf::Vector2f position, sf::Vector2f scale);
	~Enemy();

	void followPlayer(GameObject * player, float dt);

	float speed = 100;

	bool awake = false;
};

