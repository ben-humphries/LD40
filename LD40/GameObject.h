#pragma once
#include <string>
#include "SFML/Graphics.hpp"

class GameObject : public sf::Transformable, public sf::Drawable
{
public:
	GameObject();
	GameObject(std::string dir);
	~GameObject();

	sf::Sprite sprite;
	sf::Texture texture;

	sf::FloatRect collider;

	virtual void update();
	virtual sf::Vector2i boundCollision(GameObject * g);

private:

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
};

