//! \file SDLEventLoop.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Header for SDLEventLoop.cpp
//!
#pragma once

#include "types.h"

//! \brief Namespace that contains any of the main SDL functions
//!
//! Used for intialising and tearing down SDL
//!
namespace SDLMain
{
	//! \brief Initialise SDL
	//!
	//! Initialises the needed SDL subsystems
	//!
	//! \return Any error produced
	//! \sa Quit() for the yang to this ying
	//! \warning Do not call this twice
	eError Init();

	//! \brief Quit SDL
	//!
	//! Quits SDL
	//!
	//! \return Any error produced
	//! \sa Init() for the ying to this yang
	//! \warning Do not call this twice
	eError Quit();
}