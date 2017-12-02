#pragma once
#include "GameObject.h"

class Tile : public GameObject
{
public:
	Tile(int id, sf::Vector2f position, sf::Vector2f scale);
	~Tile();

	int id;
	/*
	1 -- Wall
	2 -- Door
	*/
	int tileWidth = 32;

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

