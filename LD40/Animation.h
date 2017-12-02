#pragma once
#include "SFML/Graphics.hpp"

//Animation class taken from Playground: https://github.com/ben-humphries/Playground
class Animation
{
public:
	Animation(std::string dir, int tileSize);
	~Animation();

	sf::Texture texture;
	std::vector<sf::Sprite> sprites;

	clock_t t;
	float currentTime;
	float currentFrame;


	void setTexture(sf::Texture texture);
	sf::Sprite * getSprite(float speed, bool loop);
};

