#include "Enemy.h"
#include <math.h>


Enemy::Enemy(std::string dir, sf::Vector2f position, sf::Vector2f scale, int id) : GameObject(dir)
{
	this->setPosition(position);
	this->setScale(scale);
	this->setOrigin(16, 16);

	srand(time(NULL));

	animations.push_back(new Animation("res/enemyAsleep.png", 32));
	animations.push_back(new Animation("res/enemyAwake.png", 32));

	state = AsleepState;
	animationState = Asleep;
	Enemy::sprite = *(*animations.at(animationState)).getSprite(3.2, true);

	collider = sf::FloatRect(12, 13, 7, 7);

	this->id = id;

	if (id == 1) {
		color = sf::Color(0, 255, 0, 255);
		sprite.setColor(color);
	}
	else if (id == 2) {
		color = sf::Color(255, 255, 0, 255);
		sprite.setColor(color);
	}

}


Enemy::~Enemy()
{
}

Enemy::State Enemy::getState() {
	return state;
}

void Enemy::setState(Enemy::State state) {
	this->state = state;
}

void Enemy::update(float dt) {
	if (state == AwakeState) {
		animationState = Awake;
	}
	else if (state == AwakeDarkState && id == 1) {
		darkTimer += dt;
		if (darkTimer >= darkTime) {
			darkTimer = 0;
			state = AsleepState;
			animationState = Asleep;
		}
	}
	else {
		state = AsleepState;
		animationState = Asleep;
	}

	Enemy::sprite = *(*animations.at(animationState)).getSprite(3.2, true);

	if (id != 0) {
		sprite.setColor(color);
	}

}


void Enemy::followPlayer(GameObject * player, float dt) {

	//Get unit vector of direction to player
	float theta = atan2(getPosition().y - player->getPosition().y, getPosition().x - player->getPosition().x);
	theta -= 180;

	float divergence = ((speed / 2 - 0) * ((float)rand() / RAND_MAX)) + 0;

	move(cos(theta) * speed * dt + divergence * dt, sin(theta) * speed * 2 * dt);
}
