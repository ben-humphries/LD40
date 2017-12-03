#include "Level.h"

#define EMPTY sf::Color(0,0,0,255)
#define PLAYER sf::Color(0,0,255,255)
#define TILE_WALL sf::Color(255,255,255,255)
#define TILE_DOOR sf::Color(139, 69, 19, 255)
#define ENEMY sf::Color(255,0,0,255)
#define ENEMY_PINK sf::Color(255, 111, 255, 255)
#define ENEMY_YELLOW sf::Color(255, 130, 0, 255)
#define LIGHT sf::Color(255,255,0,255)

float scale = 2;

Level::Level()
{
}


Level::~Level()
{
}

void Level::load(std::string dir) {

	tiles.clear();
	enemies.clear();
	lights.clear();

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
			float id = ((float)rand() / RAND_MAX);
			tiles.push_back(new Tile(id > 0.5 ? 0 : 1, sf::Vector2f(i % height, i / height), sf::Vector2f(scale, scale)));
		}
		else if (currentPixel == TILE_DOOR) {
			tiles.push_back(new Tile(2, sf::Vector2f(i % height, i / height), sf::Vector2f(scale, scale)));
		}
		else if (currentPixel == ENEMY) {
			enemies.push_back(new Enemy("res/enemyAsleep.png", sf::Vector2f(i % height * 32 * scale + 32, i / height * 32 * scale + 32), sf::Vector2f(scale, scale), 0));
		}
		else if (currentPixel == ENEMY_PINK) {
			enemies.push_back(new Enemy("res/enemyAsleep.png", sf::Vector2f(i % height * 32 * scale + 32, i / height * 32 * scale + 32), sf::Vector2f(scale, scale), 1));
		}
		else if (currentPixel == ENEMY_YELLOW) {
			enemies.push_back(new Enemy("res/enemyAsleep.png", sf::Vector2f(i % height * 32 * scale + 32, i / height * 32 * scale + 32), sf::Vector2f(scale, scale), 2));
		}
		else if (currentPixel == LIGHT) {
			lights.push_back(new Light(sf::Vector2f(i % height * 32 * scale, i / height * 32 * scale), sf::Vector2f(.1, .1) * scale, sf::Color(250,50,50,250)));
		}
		else if (currentPixel == PLAYER) {
			playerStart = sf::Vector2f(i % height * 32 * scale, i / height * 32 * scale);
		}
		else {
			printf("Unrecognized level object. Skipping tile. Coordinates: %d, %d\n", i %height, i / height);
			continue;
		}
	}
}

sf::Vector2f Level::getPlayerStart() { return playerStart; }

std::vector<Tile*> Level::getTiles() { return tiles; }

std::vector<Enemy*> Level::getEnemies() { return enemies; }

std::vector<Light*> Level::getLights() { return lights; }