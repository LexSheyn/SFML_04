#pragma once

#include "Player.h"

class Game
{
private:

	//Window
	sf::RenderWindow window;
	sf::Event ev;

	//Player
	Player* player;

	//Private functions
	void initWindow();
	void initPlayer();

public:

	//Constructors and Distructors
	Game();
	virtual ~Game();

	//Accessors
	const sf::RenderWindow& getWindow() const;

	//Modifiers


	//Functons
	void updatePollEvents();
	void updatePlayer();
	void updateCollision();

	void update();

	void renderPlayer();

	void render();
};

