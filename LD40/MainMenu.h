#pragma once
#include <SFML/Graphics.hpp>


class MainMenu
{
public:
	enum MenuAction { Nothing, Exit, Play, Options };

	struct MenuItem {
	public:
		sf::Rect<int> rect;
		MenuAction action;
	};

	MenuAction show(sf::RenderWindow &window);

private:

	MenuAction click(int x, int y);
	MenuAction getMenuResponse(sf::RenderWindow &window);

	MenuItem items[3];
};

