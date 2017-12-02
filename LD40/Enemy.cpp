#include "Enemy.h"
#include <math.h>


Enemy::Enemy(std::string dir, sf::Vector2f position, sf::Vector2f scale) : GameObject(dir)
{
	this->setPosition(position);
	this->setScale(scale);
	this->setOrigin(16, 16);

	collider = sprite.getLocalBounds();
}


Enemy::~Enemy()
{
}


void Enemy::followPlayer(Player * player, float dt) {

	//Get unit vector of direction to player
	sf::Vector2f playerDir = player->getPosition() - this->getPosition();
	playerDir = sf::Vector2f(playerDir.x/sqrt(playerDir.x*playerDir.x), playerDir.y/sqrt(playerDir.y*playerDir.y));

	move(playerDir * speed * dt);
}
