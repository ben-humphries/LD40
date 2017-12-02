#include "Enemy.h"
#include <math.h>


Enemy::Enemy(std::string dir, sf::Vector2f position, sf::Vector2f scale) : GameObject(dir)
{
	this->setPosition(position);
	this->setScale(scale);
	this->setOrigin(16, 16);

	collider = sprite.getLocalBounds();

	srand(time(NULL));
}


Enemy::~Enemy()
{
}


void Enemy::followPlayer(Player * player, float dt) {

	//Get unit vector of direction to player
	float theta = atan2(getPosition().y - player->getPosition().y, getPosition().x - player->getPosition().x);
	theta -= 180;

	float divergence = ((speed / 2 - 0) * ((float)rand() / RAND_MAX)) + 0;

	move(cos(theta) * speed * dt + divergence * dt, sin(theta) * speed * 2 * dt);
}
