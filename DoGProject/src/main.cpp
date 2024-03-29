//============================================================================
// Name        : DoG Project 1
// Author      : DOG
// Version     : 1.0
// Description : Spaceships vs Zombies
//============================================================================

#include "base/SDL.h"
#include "gamescenes/DebugScene.h"


int main( int argc , char* argv[] ) {
	//return SDL::exec();

	SDL::initialize();

	DebugScene *teste = new DebugScene;

	teste->run();

	SDL::close();
	
	delete teste;
	
	return 0;
}
