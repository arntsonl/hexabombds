#include "game.h"

int main(void) {
	Game * newGame = new Game();
	newGame->Run();
	// Cleanup goodness
	delete newGame;
	return 0;
}
