#include "Game.h"
#include "GameObject.h"

float width = 1344;
float height = 756;

sf::RenderWindow Game::window;
Game::GameState Game::gameState;
clock_t Game::t;

GameObject * g1;
GameObject * g2;


void Game::Start() {

	gameState = Uninitialized;

	//create window
	window.create(sf::VideoMode(width, height, 32.0), "LD40", sf::Style::Close);
	window.setKeyRepeatEnabled(false);

	//set window position
	sf::VideoMode desktopSize = sf::VideoMode::getDesktopMode();
	window.setPosition(sf::Vector2i(desktopSize.width / 2 - width / 2, desktopSize.height / 2 - height / 2));

	g1 = new GameObject("res/testCharacter.png");
	g2 = new GameObject("res/testCharacter.png");

	g1->setPosition(100, 200);
	g2->setPosition(500, 200);


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

			if (e.type == sf::Event::Closed) {

				gameState = Exiting;
			}

			break;

		}
	}

	g1->boundCollision(g2);

	g1->move(50 * dt, 0);

	window.clear(sf::Color(255,255,255,255));
	window.draw(*g1);
	window.draw(*g2);
	window.display();

}

