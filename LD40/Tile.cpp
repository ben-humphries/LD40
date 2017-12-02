#include "Tile.h"



Tile::Tile(int id, sf::Vector2f position, sf::Vector2f scale) : GameObject("res/tileSet.png")
{
	this->sprite.setTextureRect(sf::IntRect(id * tileWidth, 0, tileWidth, tileWidth));
	this->setPosition(position);
	this->setScale(scale);
}


Tile::~Tile()
{
}
