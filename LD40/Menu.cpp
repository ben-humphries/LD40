#include "Menu.h"

Menu::Menu(MenuType type) {
	this->menuType = type;
}
Menu::Menu(MenuType type, sf::Vector2f offset) {
	this->menuType = type;
	this->offset = offset;
}
Menu::~Menu() {

}

Menu::MenuAction Menu::show(sf::RenderWindow & window)
{
	window.clear();

	if (menuType == MainMenu) {

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

		items.push_back(playButton);
		items.push_back(optionsButton);
		items.push_back(quitButton);
	}
	else if (menuType == OptionsMenu) {
		if (!texture.loadFromFile("res/optionsmenu.png")) {
			printf("could not load Options Menu texture");
		}
		sprite.setTexture(texture);

		//set up button coords
		MenuItem musicOn;
		musicOn.rect.top = 400;
		musicOn.rect.left = 530;
		musicOn.rect.width = 70;
		musicOn.rect.height = 36;
		musicOn.action = MusicOn;

		MenuItem musicOff;
		musicOff.rect.top = 400;
		musicOff.rect.left = 710;
		musicOff.rect.width = 100;
		musicOff.rect.height = 36;
		musicOff.action = MusicOff;

		MenuItem backButton;
		backButton.rect.top = 530;
		backButton.rect.left = 600;
		backButton.rect.width = 130;
		backButton.rect.height = 36;
		backButton.action = ToMenu;

		items.push_back(musicOn);
		items.push_back(musicOff);
		items.push_back(backButton);

	}
	else if (menuType == PauseMenu) {
		if (!texture.loadFromFile("res/pausemenu.png")) {
			printf("could not load Pause Menu texture");
		}
		sprite.setTexture(texture);
		sprite.move(offset);

		//set up button coords
		MenuItem resume;
		resume.rect.top = 300;
		resume.rect.left = 570;
		resume.rect.width = 100;
		resume.rect.height = 36;
		resume.action = Play;

		MenuItem backButton;
		backButton.rect.top = 530;
		backButton.rect.left = 530;
		backButton.rect.width = 290;
		backButton.rect.height = 36;
		backButton.action = ToMenu;

		items.push_back(resume);
		items.push_back(backButton);
	}
	else if (menuType == DeathMenu) {

	}

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
				printf("%d    %d   %d\n", event.mouseButton.x, event.mouseButton.y, menuType);
				return click(event.mouseButton.x, event.mouseButton.y, window);
			}
			else if (event.type == sf::Event::Closed) {
				return Exit;
			}
			else if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					if (menuType == PauseMenu) {
						return Play;
					}
					return ToMenu;
				}
			}
		}
	}
}
