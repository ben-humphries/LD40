#pragma once
#include <SFML/Graphics.hpp>


class Menu
{
public:

	enum MenuType { MainMenu, PauseMenu, OptionsMenu, DeathMenu };
	MenuType menuType;
	sf::Vector2f offset;

	Menu(MenuType type);
	Menu(MenuType type, sf::Vector2f offset);
	~Menu();


	enum MenuAction { Nothing, Exit, Play, Options, MusicOn, MusicOff, ToMenu};

	struct MenuItem {
	public:
		sf::Rect<int> rect;
		MenuAction action;
	};

	MenuAction show(sf::RenderWindow &window);

private:

	MenuAction click(int x, int y, sf::RenderWindow & window);
	MenuAction getMenuResponse(sf::RenderWindow &window);

	std::vector<MenuItem> items;

	sf::Texture texture;
	sf::Sprite sprite;
};

