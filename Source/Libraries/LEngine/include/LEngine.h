#ifndef _LENGINE_H_
#define _LENGINE_H_

#include "types.h"
#include "SDLWindow.h"

// LEngine delegate class
class LEngine
{
public:

	// Constructor and destructor
	LEngine();
	~LEngine();

	// Init the engine
	eError init();

	// run ( will not return until finished running )
	eError run();

	// quit the engine
	eError quit();	

private:

	// Loads assets
	eError load();

	// calls the event loop	
	eError loop();

	// unloads the assets
	eError unload();

	// Member variables
	SDLWindow myMainWindow;

};

#endif //_LENGINE_H_