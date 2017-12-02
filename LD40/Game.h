#pragma once
#include <SFML/Graphics.hpp>
#include "Light.h"

class Game
{
public:

	static void Start();
	static void Update();


	enum GameState {Uninitialized, Running, Paused, Exiting};

	static GameState gameState;
	static clock_t t;

	static sf::RenderWindow window;

	static std::vector<Light> lights;


};

