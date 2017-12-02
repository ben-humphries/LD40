#include "Level.h"

#define EMPTY sf::Color(0,0,0,255)
#define PLAYER sf::Color(0,0,255,255)
#define TILE_WALL sf::Color(255,255,255,255)
#define TILE_DOOR sf::Color(139, 69, 19, 255)
#define ENEMY sf::Color(255,0,0,255)
#define LIGHT sf::Color(255,255,0,255)

Level::Level()
{
}


Level::~Level()
{
}

void Level::load(std::string dir) {

	sf::Image levelImage;
	if (!levelImage.loadFromFile(dir)) {
		printf("Could not load level");
	}

	int width = levelImage.getSize().x;
	int height = levelImage.getSize().y;

	for (int i = 0; i < width * height; i++) {
		sf::Color currentPixel = levelImage.getPixel(i % height, i / height);

		if (currentPixel == EMPTY) {
			continue;
		}
		else if (currentPixel == TILE_WALL) {
			tiles.push_back(Tile(0, sf::Vector2f(i % height, i / height), sf::Vector2f(1.5, 1.5)));
		}
		else if (currentPixel == TILE_DOOR) {
			tiles.push_back(Tile(1, sf::Vector2f(i % height, i / height), sf::Vector2f(1.5, 1.5)));
		}
		else if (currentPixel == ENEMY) {
			//enemies.push_back(Enemy(id, pos, scale));
		}
		else if (currentPixel == LIGHT) {
			lights.push_back(Light(sf::Vector2f(i % height, i / height), sf::Vector2f(0.1, 0.1), sf::Color(255,0,0,150)));
		}
		else {
			printf("Unrecognized level object. Skipping tile.");
			continue;
		}
	}
}

std::vector<Tile> * Level::getTiles() { return &tiles; }

//std::vector<Enemy> * Level::getEnemies() { }

std::vector<Light> * Level::getLights() { return &lights; }