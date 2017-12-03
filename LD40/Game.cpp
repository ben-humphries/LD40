#include "Game.h"
#include "GameObject.h"
#include "Player.h"
#include "Level.h"
#include "Tile.h"


float width = 1344;
float height = 756;

sf::RenderWindow Game::window;
sf::View Game::view;

Game::GameState Game::gameState;
clock_t Game::t;

Player * player;

std::vector<Light> Game::lights;

sf::Texture lightTexture;
sf::Sprite light;

sf::RenderTexture lightMapTexture;
sf::Sprite lightMap;

Level level;

sf::Music music;



void Game::Start() {

	gameState = Uninitialized;

	ShowMenu();

	//create window
	window.create(sf::VideoMode(width, height, 32.0), "LD40", sf::Style::Close);
	window.setKeyRepeatEnabled(false);

	//set window position
	sf::VideoMode desktopSize = sf::VideoMode::getDesktopMode();
	window.setPosition(sf::Vector2i(desktopSize.width / 2 - width / 2, desktopSize.height / 2 - height / 2));

	level.load("levels/testLevel.level");

	player = new Player();
	player->setPosition(level.getPlayerStart());

	view.setCenter(player->getPosition());
	view.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));

	lightMapTexture.create(width, height);
	lightMap.setTexture(lightMapTexture.getTexture());
	lightMap.setOrigin(width / 2, height / 2);

	lightTexture.loadFromFile("res/light.png");
	lightTexture.setSmooth(true);

	light.setTexture(lightTexture);
	light.setTextureRect(sf::IntRect(0, 0, 1920, 1920));
	light.setOrigin(960, 960);

	if (!music.openFromFile("res/music/song.wav")) {
		printf("Could not load music.");
	}

	music.setLoop(true);
	music.play();

	gameState = Menu;
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

		case Menu:
			ShowMenu();
			break;
		}
	}

	lights.clear();

	std::vector<Tile*> levelTiles = level.getTiles();
	std::vector<Light*> levelLights = level.getLights();
	std::vector<Enemy*> enemies = level.getEnemies();

	player->update(dt);

	view.setCenter(player->getPosition());
	
	sf::Vector2f viewMin = sf::Vector2f(width / 2, height / 2);

	if (view.getCenter().x < viewMin.x) { view.setCenter(viewMin.x, view.getCenter().y); }
	if (view.getCenter().y < viewMin.y) { view.setCenter(view.getCenter().x, viewMin.y); }


	window.setView(view);


	for (int i = 0; i < levelTiles.size(); i++) {
		player->boundCollision(levelTiles[i]);
	}


	window.clear(sf::Color(200,200,200,255));
	lightMapTexture.clear(sf::Color(0, 0, 0));

	for (int i = 0; i < levelLights.size(); i++) {

		lights.push_back(Light(levelLights[i]->pos, levelLights[i]->scale, levelLights[i]->color));
	}

	for (int i = 0; i < Game::lights.size(); i++) {

		light.setScale(lights[i].scale);
		light.setPosition(lights[i].pos - lightMap.getPosition() + lightMap.getOrigin());
		light.setColor(lights[i].color);

		lightMapTexture.draw(light, sf::BlendAdd);

	}
	lightMapTexture.display();
	lightMap.setTextureRect(sf::IntRect(0, 0, width, height));
	lightMap.setPosition(view.getCenter());

	window.draw(*player);
	
	for (int i = 0; i < levelTiles.size(); i++) {
		window.draw(*levelTiles[i]);
	}

	for (int i = 0; i < enemies.size(); i++) {
		player->wakeEnemy(enemies[i]);

		if (enemies[i]->awake) { enemies[i]->followPlayer(player, dt); }
		enemies[i]->update();

		sf::Vector2i col = enemies[i]->boundCollision(player);
		if (col.x != 0 || col.y != 0) {
			level.load("levels/testLevel.level");

			player = new Player();
			player->setPosition(level.getPlayerStart());
		}

		window.draw(*enemies[i]);
	}

	window.draw(lightMap, sf::BlendMultiply);

	sf::CircleShape circle;
	circle.setRadius(player->lightRadius * player->lightIntensity);
	circle.setOutlineColor(sf::Color(200,200,200,50));
	circle.setFillColor(sf::Color(0, 0, 0, 0));
	circle.setOutlineThickness(1);
	circle.setOrigin(circle.getRadius(), circle.getRadius());
	circle.setPosition(player->getPosition());
	window.draw(circle);

	window.display();

}

void Game::ShowMenu() {

	while (gameState == Menu) {
		MainMenu mainMenu;
		MainMenu::MenuAction action = mainMenu.show(window);

		switch (action) {
		case MainMenu::Nothing:
			continue;

		case MainMenu::Exit:
			gameState = Exiting;
			break;

		case MainMenu::Play:
			gameState = Running;
			break;

		case MainMenu::Options:
			//showOptionsMenu();
			break;
		}
	}
}

void Game::ShowDeathScreen() {

}

void Game::ShowOptionsMenu() {

}

void Game::ShowPauseMenu() {

}