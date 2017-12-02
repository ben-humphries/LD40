#include "Light.h"



Light::Light(sf::Vector2f pos, sf::Vector2f scale, sf::Color color)
{
	Light::pos = pos;
	Light::scale = scale;
	Light::color = color;

}
Light::Light() {
	Light::pos = sf::Vector2f(0, 0);
	Light::scale = sf::Vector2f(0.5, 0.5);
	Light::color = sf::Color(255,255,255, 150);
}


Light::~Light()
{
}

void Light::setPosition(float x, float y) {
	Light::pos = sf::Vector2f(x, y);
}
void Light::setScale(float x, float y) {
	Light::scale = sf::Vector2f(x, y);
}
void Light::setColor(sf::Color color) {
	Light::color = color;
}
