#include "stdafx.h"
#include "Game.h"

int main()
{
	//Creating random seed
	srand(static_cast<unsigned>(time(0)));

	//Creating Game object
	Game game;

	//Game loop
	while (game.getWindow().isOpen())
	{
		game.updatePollEvents();
		game.update();
		game.render();
	}

	//End of application
	return 0;
}