#pragma once
#include <string>
#include "Tile.h"
#include "Light.h"
//#include "Enemy.h"

class Level
{
public:
	Level();
	~Level();

	void load(std::string dir);
	std::vector<Tile> * getTiles();
	//std::vector<Enemy> * getEnemies();
	std::vector<Light> * getLights();

	sf::Vector2f getPlayerStart();

	std::vector<Tile> tiles;
	//std::vector<Enemy> enemies;
	std::vector<Light> lights;
};

