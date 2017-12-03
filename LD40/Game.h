#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Light.h"
#include "Menu.h"
#include "Tile.h"
#include "Enemy.h"

class Game
{
public:

	static void ShowMenu();
	static void ShowDeathScreen();
	static void ShowOptionsMenu();
	static void ShowPauseMenu();
	static void LoadLevel(std::string dir);


	static void Start();
	static void Update();


	enum GameState {Uninitialized, Running, Paused, Exiting, MainMenu, OptionsMenu};

	static GameState gameState;
	static clock_t t;

	static sf::RenderWindow window;
	static sf::View view;

	static std::vector<Light> lights;

	static std::vector<Tile*> levelTiles;
	static std::vector<Light*> levelLights;
	static std::vector<Enemy*> enemies;

};

