#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()
#include <map>
#include <iostream>

#include "GameEngine.hpp"
#include "IntroState.hpp"

int main ()
{
    srand(time(0));

	// initialize the engine
	GameEngine game( "TileGame" );
	game.run( game.build<IntroState>( true ) );

	// main loop
	while( game.running() )
	{
		game.nextState();
		game.update();
		game.draw();
	}

	// leaving the scope of 'game' will cleanup the engine
    return 0;
}

