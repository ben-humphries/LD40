#pragma once
#include "GameObject.h"
#include "Player.h"
class Enemy :
	public GameObject
{
public:
	Enemy(std::string dir, sf::Vector2f position, sf::Vector2f scale);
	~Enemy();

	void followPlayer(Player * player, float dt);

	float speed = 30;
};

