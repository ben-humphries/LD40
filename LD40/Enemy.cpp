#include "Enemy.h"
#include <math.h>


Enemy::Enemy(std::string dir, sf::Vector2f position, sf::Vector2f scale) : GameObject(dir)
{
	this->setPosition(position);
	this->setScale(scale);
	this->setOrigin(16, 16);

	srand(time(NULL));

	animations.push_back(new Animation("res/enemyAsleep.png", 32));
	animations.push_back(new Animation("res/enemyAwake.png", 32));

	animationState = Asleep;
	Enemy::sprite = *(*animations.at(animationState)).getSprite(3.2, true);

	collider = sf::FloatRect(12, 13, 7, 7);


}


Enemy::~Enemy()
{
}

void Enemy::update() {
	if (awake) {
		animationState = Awake;
	}
	else {
		animationState = Asleep;
	}

	Enemy::sprite = *(*animations.at(animationState)).getSprite(3.2, true);

}


void Enemy::followPlayer(GameObject * player, float dt) {

	//Get unit vector of direction to player
	float theta = atan2(getPosition().y - player->getPosition().y, getPosition().x - player->getPosition().x);
	theta -= 180;

	float divergence = ((speed / 2 - 0) * ((float)rand() / RAND_MAX)) + 0;

	move(cos(theta) * speed * dt + divergence * dt, sin(theta) * speed * 2 * dt);
}
