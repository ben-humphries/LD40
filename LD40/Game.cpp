#include "Game.h"
#include "GameObject.h"
#include "Player.h"
#include "Level.h"
#include "Tile.h"

float width = 1344;
float height = 756;

sf::RenderWindow Game::window;
Game::GameState Game::gameState;
clock_t Game::t;

Player * player;

std::vector<Light> Game::lights;

sf::Texture lightTexture;
sf::Sprite light;

sf::RenderTexture lightMapTexture;
sf::Sprite lightMap;

Level level;


void Game::Start() {

	gameState = Uninitialized;

	//create window
	window.create(sf::VideoMode(width, height, 32.0), "LD40", sf::Style::Close);
	window.setKeyRepeatEnabled(false);

	//set window position
	sf::VideoMode desktopSize = sf::VideoMode::getDesktopMode();
	window.setPosition(sf::Vector2i(desktopSize.width / 2 - width / 2, desktopSize.height / 2 - height / 2));

	player = new Player();

	lightMapTexture.create(width, height);
	lightMap.setTexture(lightMapTexture.getTexture());

	lightTexture.loadFromFile("res/light.png");
	lightTexture.setSmooth(true);

	light.setTexture(lightTexture);
	light.setTextureRect(sf::IntRect(0, 0, 1920, 1920));
	light.setOrigin(960, 960);

	level.load("levels/testLevel.level");

	gameState = Running;
	while (gameState != Exiting) {
		Game::Update();
	}
}

void Game::Update() {

	float dt = ((float)(clock() - t)) / CLOCKS_PER_SEC;
	t = clock();

	sf::Event e;
	while (window.pollEvent(e)) {

		switch (gameState) {

		case Running:

			player->handleInput(e);


			if (e.type == sf::Event::Closed) {

				gameState = Exiting;
			}

			break;

		}
	}

	lights.clear();

	std::vector<Tile*> levelTiles = level.getTiles();
	std::vector<Light*> levelLights = level.getLights();

	for (int i = 0; i < levelTiles.size(); i++) {
		player->boundCollision(levelTiles[i]);
	}

	player->update(dt);


	window.clear(sf::Color(200,200,200,255));
	lightMapTexture.clear(sf::Color(5, 5, 5));

	for (int i = 0; i < levelLights.size(); i++) {

		lights.push_back(Light(levelLights[i]->pos, levelLights[i]->scale, levelLights[i]->color));
	}

	for (int i = 0; i < Game::lights.size(); i++) {

		light.setScale(lights[i].scale);
		light.setPosition(lights[i].pos);
		light.setColor(lights[i].color);

		lightMapTexture.draw(light, sf::BlendAdd);

	}
	lightMapTexture.display();
	lightMap.setTextureRect(sf::IntRect(0, 0, width, height));
	lightMap.setPosition(0, 0);

	window.draw(*player);
	
	for (int i = 0; i < levelTiles.size(); i++) {
		window.draw(*levelTiles[i]);
	}

	window.draw(lightMap, sf::BlendMultiply);

	window.display();

}

