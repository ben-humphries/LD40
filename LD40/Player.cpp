#include "Player.h"
#include <math.h>




Player::Player()
	: GameObject("res/playerIdleDown.png")
{

	this->setPosition(200, 200);
	this->setScale(2, 2);
	this->setOrigin(13, 16);
	sprite.setColor(sf::Color::Red);

	if (!footstepBuffer.loadFromFile("res/sound/footstep.wav")) {
		printf("Could not load footstep sound");
	}
	footstep.setBuffer(footstepBuffer);
	footstep.setLoop(true);
	footstep.setVolume(10);

	if (footstep.getStatus() == footstep.Playing) {
		footstep.stop();
	}

	animations.push_back(new Animation("res/playerIdleUp.png", 32));
	animations.push_back(new Animation("res/playerIdleDown.png", 32));
	animations.push_back(new Animation("res/playerIdleRight.png", 32));
	animations.push_back(new Animation("res/playerIdleLeft.png", 32));
	animations.push_back(new Animation("res/playerWalkUp.png", 32));
	animations.push_back(new Animation("res/playerWalkDown.png", 32));
	animations.push_back(new Animation("res/playerWalkRight.png", 32));
	animations.push_back(new Animation("res/playerWalkLeft.png", 32));


	animationState = IdleDown;
	Player::sprite = *(*animations.at(animationState)).getSprite(3.2, true);
	collider = sf::FloatRect(8, 3, 10, 29);

	if (!screamBuffer.loadFromFile("res/sound/screamsound.wav")) {
		printf("Could not load scream sound.");
	}
	scream.setBuffer(screamBuffer);
	scream.setVolume(10);
}


Player::~Player()
{
}

void Player::update(float dt) {


	if ((velocity.x != 0 || velocity.y != 0) && footstep.getStatus() != footstep.Playing) {
		footstep.play();
	}
	else if (velocity.x == 0 && velocity.y == 0 && footstep.getStatus() == footstep.Playing) {
		footstep.stop();
	}

	
	this->move(velocity * dt);

	Player::sprite = *(*animations.at(animationState)).getSprite(3.2, true);

	Game::lights.push_back(Light(sf::Vector2f(getPosition()), sf::Vector2f(lightIntensity,lightIntensity), sf::Color(200,200,200,255)));
}

void Player::handleInput(sf::Event e) {

	if (e.type == sf::Event::KeyPressed) {
		if (e.key.code == sf::Keyboard::W || e.key.code == sf::Keyboard::Up) {
			movingUp = true;
			velocity.y = -speed;
			animationState = WalkUp;
		}
		else if (e.key.code == sf::Keyboard::S || e.key.code == sf::Keyboard::Down) {
			movingDown = true;
			velocity.y = speed;
			animationState = WalkDown;
		}
		else if (e.key.code == sf::Keyboard::A || e.key.code == sf::Keyboard::Left) {
			movingLeft = true;
			velocity.x = -speed;
			animationState = WalkLeft;

			if (movingUp) {
				animationState = WalkUp;
			}
		}
		else if (e.key.code == sf::Keyboard::D || e.key.code == sf::Keyboard::Right) {
			movingRight = true;
			velocity.x = speed;
			animationState = WalkRight;

			if (movingUp) {
				animationState = WalkUp;
			}
		}
		else if (e.key.code == sf::Keyboard::N) {
			lightIntensity -= 2 * lightScrollSpeed;

			if (lightIntensity < 0) {
				lightIntensity = 0;
			}
		}
		else if (e.key.code == sf::Keyboard::M) {
			lightIntensity += 2 * lightScrollSpeed;

			 if (lightIntensity > 0.35) {
				lightIntensity = 0.35;
			}
		}
	}
	else if (e.type == sf::Event::KeyReleased) {
		if (e.key.code == sf::Keyboard::W || e.key.code == sf::Keyboard::Up) {
			movingUp = false;
			if (movingDown) {
				velocity.y = speed;
				animationState = WalkDown;
			}
			else {
				velocity.y = 0;
				animationState = IdleUp;

				if (movingLeft) {
					animationState = WalkLeft;
				}
				else if (movingRight) {
					animationState = WalkRight;
				}
			}
		}
		else if(e.key.code == sf::Keyboard::S || e.key.code == sf::Keyboard::Down) {
			movingDown = false;
			if (movingUp) {
				velocity.y = -speed;
				animationState = WalkUp;
			}
			else {
				velocity.y = 0;
				animationState = IdleDown;

				if (movingLeft) {
					animationState = WalkLeft;
				}
				else if (movingRight) {
					animationState = WalkRight;
				}
			}
		}
		else if (e.key.code == sf::Keyboard::A || e.key.code == sf::Keyboard::Left) {
			movingLeft = false;
			if (movingRight) {
				velocity.x = speed;
				animationState = WalkRight;

				if (movingUp) {
					animationState = WalkUp;
				}
			}
			else {
				velocity.x = 0;
				animationState = IdleLeft;

				if (movingUp) {
					animationState = WalkUp;
				}
				else if (movingDown) {
					animationState = WalkDown;
				}
			}

		}
		else if(e.key.code == sf::Keyboard::D || e.key.code == sf::Keyboard::Right) {
			movingRight = false;
			if (movingLeft) {
				velocity.x = -speed;
				animationState = WalkLeft;

				if (movingUp) {
					animationState = WalkUp;
				}
			}
			else {
				velocity.x = 0;
				animationState = IdleRight;

				if (movingUp) {
					animationState = WalkUp;
				}
				else if (movingDown) {
					animationState = WalkDown;
				}
			}
		}
	}
	else if (e.type == sf::Event::MouseWheelScrolled) {

		lightIntensity += e.mouseWheelScroll.delta * lightScrollSpeed;

		if (lightIntensity < 0) {
			lightIntensity = 0;
		}
		else if (lightIntensity > 0.35) {
			lightIntensity = 0.35;
		}
	}
}

void Player::wakeEnemy(Enemy * enemy) {
	sf::Vector2f delta = enemy->getPosition() - this->getPosition();

	float distance = sqrt(delta.x*delta.x + delta.y*delta.y);

	if (distance < 10.0) {
		scream.play();
	}

	if (enemy->id == 0 || enemy->id == 1) {
		if (distance <= lightRadius * lightIntensity) {
			enemy->setState(Enemy::AwakeState);
		}
		else if (enemy->getState() == Enemy::AwakeState) {
			enemy->setState(Enemy::AwakeDarkState);
		}
	}
	else {
		if (distance >= lightRadius * lightIntensity) {
			enemy->setState(Enemy::AwakeState);
		}
		else {
			enemy->setState(Enemy::AsleepState);
		}
	}
}
