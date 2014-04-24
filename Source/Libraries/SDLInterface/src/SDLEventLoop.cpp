//! \file SDLEventLoop.cpp
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Description
//! 
#include "SDLEventLoop.h"

#include "SDL.h"

#include "debug.h"
#include "eError.h"

// Do the event loop
eError SDLEventLoop::DoLoop()
{
	eError err = eError::noErr;

	//Event handler
    SDL_Event event;

	// Boolean to store the end
	bool toEnd = false;

	//Handle events on queue
	while ( !toEnd )
    {
		// Peep into the events. SDL_PeepEvents is thread safe, unlike wait or 
		int sdl_error = SDL_PeepEvents(&event, 1, SDL_GETEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT);

		// If we have an error then break out early
		if (sdl_error < 0)
		{
			DEBUG_LOG(SDL_GetError());
			err = eError::SDL_Fatal;
			break;
		}

    	switch( event.type )
    	{
    		case SDL_QUIT:
				DEBUG_LOG("Quit requested");
				err |= eError::quitRequest;
    			break;

			// Keyboard events
    		case SDL_KEYUP:
    		case SDL_KEYDOWN:
    			err |= HandleKeyboardEvent(&event);
    			break;

			// Text input events
    		case SDL_TEXTEDITING:
    		case SDL_TEXTINPUT:
				DEBUG_LOG("Unhandled SDL Event: SDL_TEXT");
    			break;

			// Mouse events
    		case SDL_MOUSEMOTION:
    		case SDL_MOUSEBUTTONUP:
    		case SDL_MOUSEBUTTONDOWN:
    		case SDL_MOUSEWHEEL:
    			err |= HandleMouseEvent(&event);
    			break;

			// Joystick events
			case SDL_JOYAXISMOTION:
			case SDL_JOYBALLMOTION:
			case SDL_JOYHATMOTION:
			case SDL_JOYBUTTONDOWN:
			case SDL_JOYBUTTONUP:
			case SDL_JOYDEVICEADDED:
			case SDL_JOYDEVICEREMOVED:
    			err |= HandleJoystickEvent(&event);
				break;

			// Controller events
			case SDL_CONTROLLERAXISMOTION:
			case SDL_CONTROLLERBUTTONDOWN:
			case SDL_CONTROLLERBUTTONUP:
			case SDL_CONTROLLERDEVICEADDED:
			case SDL_CONTROLLERDEVICEREMOVED:
			case SDL_CONTROLLERDEVICEREMAPPED:
    			err |= HandleControllerEvent(&event);
				break;

			// Window events
			case SDL_WINDOWEVENT:
				HandleWindowEvent(&event);
				break;

			// SysWM events?
			case SDL_SYSWMEVENT:
				DEBUG_LOG("Unhandled SDL Event: SDL_SYSWMEVENT");
				break;

    		default:
    			DEBUG_LOG("Unhandled SDL Event: type %i",event.type);
    			break;
    	}

		toEnd = ( ERROR_HAS_TYPE_FATAL(err)				// Fatal errors
			|| ERROR_HAS(err, eError::quitRequest));	// Quit requests
    }

    if ( err != eError::noErr )
    	DEBUG_LOG("DoLoop Dropped out with eError %i",err);

    return err;
}

// Handle all keyboard events
eError SDLEventLoop::HandleKeyboardEvent( SDL_Event *event )
{
	eError err = eError::noErr;
	return err;
}

// Handles all mouse events
eError SDLEventLoop::HandleMouseEvent( SDL_Event *event )
{
	eError err = eError::noErr;
	return err;
}

// Handles all Joystick events
eError SDLEventLoop::HandleJoystickEvent( SDL_Event *event )
{
	eError err = eError::noErr;
	return err;
}

// Handles all Controller events
eError SDLEventLoop::HandleControllerEvent( SDL_Event *event )
{
	eError err = eError::noErr;
	return err;
}

// Handles all Controller events
eError SDLEventLoop::HandleWindowEvent(SDL_Event *event)
{
	eError err = eError::noErr;

	switch (event->window.event)
	{
		case SDL_WINDOWEVENT_SHOWN:
			DEBUG_LOG("SDL_WINDOWEVENT_SHOWN");
			break;
		default:
			DEBUG_LOG("Unhandled SDL Event: SDL_WINDOWEVENT %i", event->window.event);
			break;
	}
	return err;
}