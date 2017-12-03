#pragma once
#include "GameObject.h"
#include "Animation.h"

class Enemy :
	public GameObject
{
public:
	Enemy(std::string dir, sf::Vector2f position, sf::Vector2f scale);
	~Enemy();

	virtual void update();
	void followPlayer(GameObject * player, float dt);

	float speed = 100;

	bool awake = false;

	std::vector<Animation*> animations;

	enum AnimationState { Asleep, Awake };
	AnimationState animationState;
};

