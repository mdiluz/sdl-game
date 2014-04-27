//! \file SDLMutex.cpp
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Wrapper for various SDL_mutex functions
//!	Found at https://wiki.libsdl.org/CategoryMutex
#include "SDLMutex.h"

#include "debug.h"
#include "eError.h"

#include "SDL.h"

//========================================================
SDLInterface::Mutex::Mutex()
: my_sdl_mutex( nullptr )
{

}

//========================================================
SDLInterface::Mutex::~Mutex()
{
	// Sanity check that destroy has been called
	DEBUG_ASSERT(my_sdl_mutex == nullptr);
}

//========================================================
eError SDLInterface::Mutex::Create()
{
	DEBUG_ASSERT(my_sdl_mutex == nullptr);

	my_sdl_mutex = SDL_CreateMutex();

	return eError::NoErr;
}

//========================================================
eError SDLInterface::Mutex::Destroy()
{
	DEBUG_ASSERT(my_sdl_mutex != nullptr);

	SDL_DestroyMutex(my_sdl_mutex);
	my_sdl_mutex = nullptr;

	return eError::NoErr;
}

//========================================================
eError SDLInterface::Mutex::Lock()
{
	DEBUG_ASSERT(my_sdl_mutex != nullptr);

	SDL_LockMutex(my_sdl_mutex);

	return eError::NoErr;
}

//========================================================
eError SDLInterface::Mutex::Unlock()
{
	DEBUG_ASSERT(my_sdl_mutex != nullptr);

	SDL_UnlockMutex(my_sdl_mutex);

	return eError::NoErr;
}

//========================================================
SDLInterface::Semaphore::Semaphore()
: m_mySem(nullptr)
{

}

//========================================================
SDLInterface::Semaphore::~Semaphore()
{
	// Sanity check that destroy has been called
	DEBUG_ASSERT(m_mySem == nullptr);
}

//========================================================
eError SDLInterface::Semaphore::Create()
{
	DEBUG_ASSERT(m_mySem == nullptr);

	m_mySem = SDL_CreateSemaphore(0);

	return eError::NoErr;
}

//========================================================
eError SDLInterface::Semaphore::Destroy()
{
	DEBUG_ASSERT(m_mySem != nullptr);

	SDL_DestroySemaphore(m_mySem);
	m_mySem = nullptr;

	return eError::NoErr;
}

//========================================================
eError SDLInterface::Semaphore::Post()
{
	DEBUG_ASSERT(m_mySem != nullptr);

	SDL_SemPost(m_mySem);

	return eError::NoErr;
}

//========================================================
eError SDLInterface::Semaphore::Wait()
{
	DEBUG_ASSERT(m_mySem != nullptr);

	SDL_SemWait(m_mySem);

	return eError::NoErr;
}
