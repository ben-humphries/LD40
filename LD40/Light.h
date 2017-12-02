#pragma once
#include "SFML/Graphics.hpp"


class Light
{
public:
	Light(sf::Vector2f pos, sf::Vector2f scale, sf::Color color);
	Light();
	~Light();

	sf::Vector2f pos;
	sf::Vector2f scale;
	sf::Color color;

	void setPosition(float x, float y);
	void setScale(float x, float y);
	void setColor(sf::Color color);
};

