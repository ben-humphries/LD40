#include "Player.h"



Player::Player()
	: GameObject("res/testCharacter.png")
{

	this->setPosition(200, 200);
}


Player::~Player()
{
}

void Player::update(float dt) {

	this->move(velocity * dt);
}

void Player::handleInput(sf::Event e) {

	if (e.type == sf::Event::KeyPressed) {
		if (e.key.code == sf::Keyboard::W || e.key.code == sf::Keyboard::Up) {
			velocity.y = -speed;
		}
		else if (e.key.code == sf::Keyboard::S || e.key.code == sf::Keyboard::Down) {
			velocity.y = speed;
		}
		else if (e.key.code == sf::Keyboard::A || e.key.code == sf::Keyboard::Left) {
			velocity.x = -speed;
		}
		else if (e.key.code == sf::Keyboard::D || e.key.code == sf::Keyboard::Right) {
			velocity.x = speed;
		}
	}
	else if (e.type = sf::Event::KeyReleased) {
		if (e.key.code == sf::Keyboard::W || e.key.code == sf::Keyboard::Up ||
			e.key.code == sf::Keyboard::S || e.key.code == sf::Keyboard::Down) {
			velocity.y = 0;
		}
		else if (e.key.code == sf::Keyboard::A || e.key.code == sf::Keyboard::Left ||
			e.key.code == sf::Keyboard::D || e.key.code == sf::Keyboard::Right) {
			velocity.x = 0;
		}
	}
}
