#include "Game.h"
#include "GameObject.h"
#include "Player.h"

float width = 1344;
float height = 756;

sf::RenderWindow Game::window;
Game::GameState Game::gameState;
clock_t Game::t;

Player * player;
GameObject * g2;

std::vector<Light> Game::lights;

sf::Texture lightTexture;
sf::Sprite light;

sf::RenderTexture lightMapTexture;
sf::Sprite lightMap;




void Game::Start() {

	gameState = Uninitialized;

	//create window
	window.create(sf::VideoMode(width, height, 32.0), "LD40", sf::Style::Close);
	window.setKeyRepeatEnabled(false);

	//set window position
	sf::VideoMode desktopSize = sf::VideoMode::getDesktopMode();
	window.setPosition(sf::Vector2i(desktopSize.width / 2 - width / 2, desktopSize.height / 2 - height / 2));

	player = new Player();
	g2 = new GameObject("res/testCharacter.png");

	g2->setPosition(500, 200);

	lightMapTexture.create(width, height);
	lightMap.setTexture(lightMapTexture.getTexture());

	lightTexture.loadFromFile("res/light.png");
	lightTexture.setSmooth(true);

	light.setTexture(lightTexture);
	light.setTextureRect(sf::IntRect(0, 0, 1920, 1920));
	light.setOrigin(960, 960);



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

	player->update(dt);


	player->boundCollision(g2);

	window.clear(sf::Color(200,200,200,255));
	lightMapTexture.clear(sf::Color(5, 5, 5));

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
	window.draw(*g2);
	

	window.draw(lightMap, sf::BlendMultiply);

	window.display();

}

