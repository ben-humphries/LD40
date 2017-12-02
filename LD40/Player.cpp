#include "Player.h"



Player::Player()
	: light(sf::Vector2f(0, 0), sf::Vector2f(0, 0), sf::Color::White)
	, GameObject("res/testCharacter.png")
{

	this->setPosition(200, 200);
	this->setScale(2.5, 2.5);
	this->setOrigin(16, 16);

	light.setPosition(this->getPosition().x, this->getPosition().y);
}


Player::~Player()
{
}

void Player::update(float dt) {

	this->move(velocity * dt);

	light.setScale(1, 1);

	Game::lights.push_back(Light(sf::Vector2f(getPosition()), sf::Vector2f(lightIntensity,lightIntensity), sf::Color(255,255,255,255)));
}

void Player::handleInput(sf::Event e) {

	if (e.type == sf::Event::KeyPressed) {
		if (e.key.code == sf::Keyboard::W || e.key.code == sf::Keyboard::Up) {
			movingUp = true;
			velocity.y = -speed;
		}
		else if (e.key.code == sf::Keyboard::S || e.key.code == sf::Keyboard::Down) {
			movingDown = true;
			velocity.y = speed;
		}
		else if (e.key.code == sf::Keyboard::A || e.key.code == sf::Keyboard::Left) {
			movingLeft = true;
			velocity.x = -speed;
		}
		else if (e.key.code == sf::Keyboard::D || e.key.code == sf::Keyboard::Right) {
			movingRight = true;
			velocity.x = speed;
		}
	}
	else if (e.type == sf::Event::KeyReleased) {
		if (e.key.code == sf::Keyboard::W || e.key.code == sf::Keyboard::Up) {
			movingUp = false;
			if (movingDown) {
				velocity.y = speed;
			}
			else {
				velocity.y = 0;
			}
		}
		else if(e.key.code == sf::Keyboard::S || e.key.code == sf::Keyboard::Down) {
			movingDown = false;
			if (movingUp) {
				velocity.y = -speed;
			}
			else {
				velocity.y = 0;
			}
		}
		else if (e.key.code == sf::Keyboard::A || e.key.code == sf::Keyboard::Left) {
			movingLeft = false;
			if (movingRight) {
				velocity.x = speed;
			}
			else {
				velocity.x = 0;
			}
		}
		else if(e.key.code == sf::Keyboard::D || e.key.code == sf::Keyboard::Right) {
			movingRight = false;
			if (movingLeft) {
				velocity.x = -speed;
			}
			else {
				velocity.x = 0;
			}
		}
	}
	else if (e.type == sf::Event::MouseWheelScrolled) {

		lightIntensity += e.mouseWheelScroll.delta * lightScrollSpeed;
		printf("here");
	}
}
