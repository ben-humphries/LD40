#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "SFML/Audio.hpp"

class Enemy :
	public GameObject
{
public:
	Enemy(std::string dir, sf::Vector2f position, sf::Vector2f scale, int id);
	~Enemy();

	virtual void update(float dt);
	void followPlayer(GameObject * player, float dt);

	float speed = 150;

	enum State {AsleepState, AwakeState, AwakeDarkState};
	State state;

	sf::Color color;

	int id;

	State getState();
	void setState(State state);

	float darkTimer = 0;
	float darkTime = 1;

	std::vector<Animation*> animations;

	enum AnimationState { Asleep, Awake };
	AnimationState animationState;

	sf::SoundBuffer soundBuffer;
	sf::Sound sound;
};

