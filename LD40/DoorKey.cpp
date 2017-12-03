#include "DoorKey.h"



DoorKey::DoorKey(sf::Vector2f position)
{
	this->setPosition(position);

	if (!this->texture.loadFromFile("res/key.png")) {
		printf("Could not load key texture.");
	}
	this->sprite.setTexture(texture);
}


DoorKey::~DoorKey()
{
}
