#pragma once
#include <SFML/Graphics.hpp>


class Menu
{
public:
	enum MenuType {MainMenu, PauseMenu, OptionsMenu, DeathMenu};
	enum MenuAction { Nothing, Exit, Play, Options };

	struct MenuItem {
	public:
		sf::Rect<int> rect;
		MenuAction action;
	};

	MenuAction show(sf::RenderWindow &window);

private:

	MenuAction click(int x, int y, sf::RenderWindow & window);
	MenuAction getMenuResponse(sf::RenderWindow &window);

	MenuItem items[3];

	sf::Texture texture;
	sf::Sprite sprite;
};

