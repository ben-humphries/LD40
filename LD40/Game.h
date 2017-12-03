#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Light.h"
#include "MainMenu.h"

class Game
{
public:

	static void ShowMenu();
	static void ShowDeathScreen();
	static void ShowOptionsMenu();
	static void ShowPauseMenu();


	static void Start();
	static void Update();


	enum GameState {Uninitialized, Running, Paused, Exiting, Menu};

	static GameState gameState;
	static clock_t t;

	static sf::RenderWindow window;
	static sf::View view;

	static std::vector<Light> lights;

};

