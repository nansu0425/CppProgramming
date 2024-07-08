#include <iostream>
#include "Game.h"

int main()
{
	srand((unsigned)time(nullptr));

	Game game;
	game.init();

	while (true)
	{
		game.update();
	}


	return 0;
}