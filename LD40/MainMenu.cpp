#include "MainMenu.h"

MainMenu::MenuAction MainMenu::show(sf::RenderWindow & window)
{

	sf::Texture texture;
	if (!texture.loadFromFile("res/mainmenu.png")) {
		printf("could not load Main Menu texture");
	}
	sf::Sprite sprite(texture);

	//set up button coords
	MenuItem playButton;
	playButton.rect.top = 300;
	playButton.rect.left = 610;
	playButton.rect.width = 120;
	playButton.rect.height = 36;
	playButton.action = Play;

	MenuItem optionsButton;
	optionsButton.rect.top = 410;
	optionsButton.rect.left = 560;
	optionsButton.rect.width = 220;
	optionsButton.rect.height = 36;
	optionsButton.action = Options;

	MenuItem quitButton;
	quitButton.rect.top = 735;
	quitButton.rect.left = 600;
	quitButton.rect.width = 130;
	quitButton.rect.height = 36;
	quitButton.action = Exit;

	items[0] = playButton;
	items[1] = optionsButton;
	items[2] = quitButton;

	window.draw(sprite);
	window.display();

	return getMenuResponse(window);

}

MainMenu::MenuAction MainMenu::click(int x, int y)
{
	for (MenuItem &item : items) {

		if (item.rect.top < y &&
			item.rect.top + item.rect.height > y &&
			item.rect.left < x &&
			item.rect.left + item.rect.width > x) {

			return item.action;
		}

	}

	return Nothing;
}

MainMenu::MenuAction MainMenu::getMenuResponse(sf::RenderWindow & window)
{
	sf::Event event;

	while (true) {

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::MouseButtonPressed) {
				return click(event.mouseButton.x, event.mouseButton.y);
			}
			else if (event.type == sf::Event::Closed) {
				return Exit;
			}
		}
	}
}
