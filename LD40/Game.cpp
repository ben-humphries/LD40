#include "Game.h"
#include "GameObject.h"
#include "Player.h"
#include "Level.h"


float width = 1344;
float height = 756;

sf::RenderWindow Game::window;
sf::View Game::view;

Game::GameState Game::gameState;
clock_t Game::t;

Player * player;

std::vector<Light> Game::lights;

std::vector<Tile*> Game::levelTiles;
std::vector<Light*> Game::levelLights;
std::vector<Enemy*> Game::enemies;

int Game::currentLevel = 0;

sf::Texture lightTexture;
sf::Sprite light;

sf::RenderTexture lightMapTexture;
sf::Sprite lightMap;

Level level;

sf::Music music;

sf::Texture bgTexture;
sf::Sprite background;

sf::Font font;
sf::Text text;

sf::SoundBuffer screamBuffer;
sf::Sound scream;

std::vector<std::string> levelText;

void Game::Start() {

	gameState = Uninitialized;

	ShowMenu();

	//create window
	window.create(sf::VideoMode(width, height, 32.0), "LD40", sf::Style::Close);
	window.setKeyRepeatEnabled(false);

	//set window position
	sf::VideoMode desktopSize = sf::VideoMode::getDesktopMode();
	window.setPosition(sf::Vector2i(desktopSize.width / 2 - width / 2, desktopSize.height / 2 - height / 2));

	player = new Player();

	if (!font.loadFromFile("res/courbd.ttf")) {
		printf("Could not load font.");
	}

	levelText.push_back("Use the scroll wheel to expand your light.");
	levelText.push_back("Beware: enemies wake when you shine your light on them.");
	levelText.push_back("Good luck...");
	levelText.push_back("");
	levelText.push_back("");
	levelText.push_back("");
	levelText.push_back("These guys look a little... different...");
	levelText.push_back("");
	levelText.push_back("");
	levelText.push_back("Looks like they don't like the light...");
	levelText.push_back("");
	levelText.push_back("");



	std::string dir = "levels/level" + std::to_string(currentLevel) + ".level";
	LoadLevel(dir);


	text.setFont(font);
	text.setString(levelText[currentLevel]);
	text.setCharacterSize(30);
	text.setOrigin(text.getLocalBounds().width/2, text.getLocalBounds().height/2);
	text.setPosition(sf::Vector2f(width / 2, height - 100));
	text.setFillColor(sf::Color::White);

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
	music.setVolume(50);
	music.play();

	if (!bgTexture.loadFromFile("res/background.png")) {
		printf("Could not load background texture.");
	}
	background.setTexture(bgTexture);
	background.setOrigin(width / 2, height / 2);

	if (!screamBuffer.loadFromFile("res/sound/screamsound.wav")) {
		printf("Could not load scream sound.");
	}
	scream.setBuffer(screamBuffer);

	gameState = MainMenu;
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
			else if (e.type == sf::Event::KeyPressed) {
				if (e.key.code == sf::Keyboard::Escape) {
					gameState = Paused;
					while (gameState == Paused) {
						Menu pauseMenu(Menu::PauseMenu, view.getCenter() - view.getSize() / 2.0f);
						Menu::MenuAction pauseAction = pauseMenu.show(window);

						switch (pauseAction) {
						case Menu::Play:
							gameState = Running;
							break;
						case Menu::ToMenu:
							gameState = MainMenu;
							window.setView(sf::View(sf::FloatRect(0, 0, width, height)));
							LoadLevel("levels/level0.level");
							currentLevel = 0;
							break;
						case Menu::Exit:
							gameState = Exiting;
							break;
						}
					}
				}
			}

		case MainMenu:
			ShowMenu();
			clock();
			break;
		}
	}

	lights.clear();

	levelTiles = level.getTiles();
	levelLights = level.getLights();
	enemies = level.getEnemies();

	player->update(dt);

	view.setCenter(player->getPosition());	
	sf::Vector2f viewMin = sf::Vector2f(width / 2, height / 2);

	if (view.getCenter().x < viewMin.x) { view.setCenter(viewMin.x, view.getCenter().y); }
	if (view.getCenter().y < viewMin.y) { view.setCenter(view.getCenter().x, viewMin.y); }

	background.setPosition(view.getCenter());



	window.setView(view);


	for (int i = 0; i < levelTiles.size(); i++) {
		if (levelTiles[i]->id == 2) {
			sf::Vector2i col = player->boundCollision(levelTiles[i]);
			if (col.x != 0 || col.y != 0) {
				currentLevel++;
				if (currentLevel == numLevels) {
					currentLevel = 0;
				}
				std::string dir = "levels/level" + std::to_string(currentLevel) + ".level";
				LoadLevel(dir);
			}
		}
		player->boundCollision(levelTiles[i]);
	}


	window.clear(sf::Color(150,150,150,255));
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

	window.draw(background);

	window.draw(*player);
	
	for (int i = 0; i < levelTiles.size(); i++) {
		window.draw(*levelTiles[i]);
	}

	for (int i = 0; i < enemies.size(); i++) {
		player->wakeEnemy(enemies[i]);

		if (enemies[i]->getState() == Enemy::AwakeState || enemies[i]->getState() == Enemy::AwakeDarkState) { enemies[i]->followPlayer(player, dt); }
		enemies[i]->update(dt);

		sf::Vector2i col = enemies[i]->boundCollision(player);
		if (col.x != 0 || col.y != 0) {
			
			gameState = Paused;
			while (gameState == Paused) {
				player->footstep.stop();
				scream.play();

				Menu deathMenu(Menu::DeathMenu, view.getCenter() - view.getSize() / 2.0f);
				Menu::MenuAction deathAction = deathMenu.show(window);

				switch (deathAction) {
				case Menu::Play: {
					std::string dir = "levels/level" + std::to_string(currentLevel) + ".level";
					LoadLevel(dir);
					gameState = Running;
					break;
				}
				case Menu::ToMenu:
					gameState = MainMenu;
					window.setView(sf::View(sf::FloatRect(0, 0, width, height)));
					currentLevel = 0;

					LoadLevel("levels/level0.level");
					break;
				case Menu::Exit:
					gameState = Exiting;
					break;
				}
			}
			return;
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

	text.setPosition(sf::Vector2f(width / 2, height - 100) + (view.getCenter() - view.getSize() / 2.0f));
	window.draw(text);

	window.display();

}

void Game::ShowMenu() {

	while (gameState == MainMenu) {
		Menu mainMenu(Menu::MainMenu);
		Menu::MenuAction action = mainMenu.show(window);

		switch (action) {
		case Menu::Nothing:
			continue;

		case Menu::Exit:
			gameState = Exiting;
			break;

		case Menu::Play:
			gameState = Running;
			break;

		case Menu::Options:
			gameState = OptionsMenu;
			while (gameState == OptionsMenu) {
				Menu optionsMenu(Menu::OptionsMenu);
				Menu::MenuAction optionsAction = optionsMenu.show(window);

				switch (optionsAction) {
				case Menu::MusicOn:
					if(music.getStatus() != music.Playing)
						music.play();
					break;
				case Menu::MusicOff:
					music.stop();
					break;
				case Menu::ToMenu:
					gameState = MainMenu;
					break;
				case Menu::Exit:
					gameState = Exiting;
					break;
				}
			}
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

void Game::LoadLevel(std::string dir) {
	level.load(dir);
	player->footstep.stop();

	player = new Player();


	player->lightIntensity = 0;
	/*if (currentLevel == 6) {
		player->lightIntensity = 1;
	}*/
	player->setPosition(level.getPlayerStart());

	text.setString(levelText[currentLevel]);
	text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);

	enemies.clear();
	levelTiles.clear();
	levelLights.clear();
}