#include "Menu.h"

Menu::MenuAction Menu::show(sf::RenderWindow & window)
{
	window.clear();


	if (!texture.loadFromFile("res/mainmenu.png")) {
		printf("could not load Main Menu texture");
	}
	sprite.setTexture(texture);

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
	quitButton.rect.top = 530;
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

Menu::MenuAction Menu::click(int x, int y, sf::RenderWindow & window)
{

	for (MenuItem &item : items) {

		if (item.rect.top < y &&
			item.rect.top + item.rect.height > y &&
			item.rect.left < x &&
			item.rect.left + item.rect.width > x) {
			printf("%d", item.action);
			return item.action;
		}

	}
	
	window.clear();
	window.draw(sprite);
	window.display();

	return Nothing;
}

Menu::MenuAction Menu::getMenuResponse(sf::RenderWindow & window)
{
	sf::Event event;

	while (true) {

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::MouseButtonPressed) {
				return click(event.mouseButton.x, event.mouseButton.y, window);
			}
			else if (event.type == sf::Event::Closed) {
				return Exit;
			}
		}
	}
}
