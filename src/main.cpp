#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()
#include <map>
#include <iostream>
#include <cstring>

#include "GameEngine.hpp"
#include "IntroState.hpp"

int main ( int argc, char *argv[] ){
	srand(time(0));

	// initialize the engine
	GameEngine game( "TileGame" );

    if(argc > 1) {
        if (std::strncmp(argv[1], "--dev", 5) == 0) {
            game.toggleDevMode();
        }
    }

	game.run( game.build<IntroState>( true ) );

	// main loop
	while( game.running() ){
		game.nextState();
		game.update();
		game.draw();
	}

	// leaving the scope of 'game' will cleanup the engine
	return 0;
}

