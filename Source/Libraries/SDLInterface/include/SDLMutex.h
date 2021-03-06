//! \file SDLMutex.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Header for Mutex.cpp
//!	
#ifndef _SDLMUTEX_H_
#define _SDLMUTEX_H_

#include "SDLCommon.h"

// Forward declare SDL structs
struct SDL_semaphore;
struct SDL_mutex;

// Start the SDLInterface Namespace
namespace SDLInterface
{

	//! \brief a Mutex class
	//! A mutex is used to allow a function to stop progress until some other concurrent progress is finished
	//! In short: a mutex prevents concurrent access of data
	//! ie. Thread1 locks the mutex, does some stuff. Thread2 meanwhile needs to do things but when 
	//! it tries to lock the mutex, it must wait untill Thread1 has unlocked and let it continue.
	class Mutex
	{
	public:

		// Constructor and destructor
		Mutex();
		~Mutex();

		//! \brief Create the mutex (must be called)
		Error Create();

		//! \brief Destroy the mutex (must be called before destruction)
		Error Destroy();

		//! \brief Lock the mutex
		//! \warning will not return untill mutex has been locked, ie. all other locks have unlocked
		Error Lock();

		//! \brief Unlock the mutex
		//! MUST be called if Lock() was called
		Error Unlock();

	private:

		//! \brief the sdl mutex
		SDL_mutex* my_sdl_mutex;
	};


	//! \brief Semaphore class. Allows one thread to wait on another thread completing a function
	class Semaphore
	{
	public:

		// Constructor and destructor
		Semaphore();
		~Semaphore();

		//! \brief Create the semaphore (must be called) 
		Error Create();

		//! \brief Destroy the semaphore (must be called before destruction)
		Error Destroy();

		//! \brief Post the semaphore
		Error Post();

		//! \brief Waits for the semaphore
		//! \warning will block until Post is called
		Error Wait();

	private:

		//! \brief the internal SDL semaphore
		SDL_semaphore* m_mySem;

	};

}

#endif //_SDLMUTEX_H_
