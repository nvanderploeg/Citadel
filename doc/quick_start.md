# Getting Started

Create a new xcode Project and add engine source dir to the include path
then in your main.cpp file use the following. It's really that simple!
```
#include "citadel/citadel.h"

using namespace Citadel; 
int main()
{
	//Automatically looks for game.config and builds from there
	//You can instead pass in a path to the main game config file, or pass in a GameBuilder Object
	CitadelGame game(); 

	//Run the game
	return game.run(); 
}
```