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
			tiles.push_back(new Tile(0, sf::Vector2f(i % height, i / height), sf::Vector2f(1.5, 1.5)));
		}
		else if (currentPixel == TILE_DOOR) {
			tiles.push_back(new Tile(1, sf::Vector2f(i % height, i / height), sf::Vector2f(1.5, 1.5)));
		}
		else if (currentPixel == ENEMY) {
			enemies.push_back(new Enemy("res/testCharacter.png", sf::Vector2f(i % height * 32, i / height * 32), sf::Vector2f(1.5,1.5)));
		}
		else if (currentPixel == LIGHT) {
			lights.push_back(new Light(sf::Vector2f(i % height * 32, i / height * 32), sf::Vector2f(0.1, 0.1), sf::Color(255,0,0,150)));
		}
		else if (currentPixel == PLAYER) {
			playerStart = sf::Vector2f(i % height, i / height);
		}
		else {
			printf("Unrecognized level object. Skipping tile. Coordinates: %d, %d\n", i %height, i / height);
			continue;
		}
	}
}

std::vector<Tile*> Level::getTiles() { return tiles; }

std::vector<Enemy*> Level::getEnemies() { return enemies; }

std::vector<Light*> Level::getLights() { return lights; }