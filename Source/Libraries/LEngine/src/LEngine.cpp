//! \file SDLEventLoop.cpp
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Description
//! 
#include "LEngine.h"

#include "SDLMain.h"
#include "SDLEventLoop.h"
#include "LGameBase.h"

#include "debug.h"
#include "eError.h"

//! \brief start point for the SDL loop thread
int SDLLoopThreadStart( void* data );

//! \brief start point for the game thread
int GameThreadStart( void* data );

//! \brief start point for the render thread
int RenderThreadStart(void* data);

//===============================================================
// LEngine::
//===============================================================
LEngine::LEngine()
{

}

//===============================================================
// LEngine::
//===============================================================
LEngine::~LEngine()
{

}

//===============================================================
// LEngine::
//===============================================================
eError LEngine::init()
{
	RUNTIME_LOG("Initialising...")

    //Initialization flag
    eError err = eError::noErr;

    err = SDLMain::Init();

	if (!ERROR_HAS_TYPE_FATAL(err))
	{
		err = m_MainWindow.Create();
	}

	if (!ERROR_HAS_TYPE_FATAL(err))
	{
		// give the SDLThread system the function queue
		err = SDLThread::SetMainThreadQueue(&m_mainThreadQueue);
	}

    return err;
}

//===============================================================
// LEngine::
//===============================================================
eError LEngine::run()
{
	eError err = eError::noErr;

	err |= load();

	if ( eError::noErr == err )
		err |= loop();

	if ( eError::noErr == err )
		err |= unload();

	return err;
}

//===============================================================
// LEngine::
//===============================================================
eError LEngine::quit()
{
	RUNTIME_LOG("Quiting...")

	eError err = eError::noErr;

	err |= m_MainWindow.Destroy();

    //Quit SDL subsystems
    SDLMain::Quit();

    return err;
}

//===============================================================
// LEngine::
//===============================================================
eError LEngine::load()
{
	RUNTIME_LOG("Loading...")
    
	//Loading err flag
    eError err = eError::noErr;

    err |= LGameBase::GetGame()->Create();

    if( eError::noErr == err )
        err |= LGameBase::GetGame()->Initialise();

    return err;
}

//===============================================================
// LEngine::
//===============================================================
eError LEngine::loop()
{
	RUNTIME_LOG("Looping...")

	eError err = eError::noErr;

	// Spawn SDLEventloop thread
	SDLThread::Thread sdlLoopThread;
	sdlLoopThread.name = "SDLEventLoop";

	SDLThread::SpawnThread(sdlLoopThread, SDLLoopThreadStart, NULL);

	// Spawn Game thread
	SDLThread::Thread gameUpdateThread;
	sdlLoopThread.name = "LGameUpdate";

	SDLThread::SpawnThread(gameUpdateThread, GameThreadStart, NULL);

	// Spawn the render thread
	SDLThread::Thread renderThread;
	sdlLoopThread.name = "Render";

	SDLThread::SpawnThread(renderThread, RenderThreadStart, NULL);

	// Run the main thread queue
	err = m_mainThreadQueue.Run();

	// Main thread queue has quit out
	//TODO: Send some kind of message to the other threads that they need to quit

	// Wait for all the threads to close off
	int returnVal;
	SDLThread::WaitForThread(renderThread, &returnVal);

	SDLThread::WaitForThread(gameUpdateThread, &returnVal);

	SDLThread::WaitForThread(sdlLoopThread, &returnVal);


		// These functions bellow MUST now to be farmed off to other threads
		// Removing them for now to ensure no funny business
		/*
        err |= SDLEventLoop::DoLoop(exit_request);

        if ( eError::noErr == err )
            err |= LGameBase::GetGame()->Update();

        if ( eError::noErr == err )
        	err |= m_MainWindow.Update();
		*/

    return err;
}

//===============================================================
// LEngine::
//===============================================================
eError LEngine::unload()
{
	eError err = eError::noErr;

    err |= LGameBase::GetGame()->Destroy();

	return err;
}

//===============================================================
int SDLLoopThreadStart(void* data)
{
	DEBUG_LOG("SDLLoopThread Starting");

	SDLEventLoop::DoLoop();

	DEBUG_LOG("SDLLoopThread Ending");
	return 0;
}

//===============================================================
int GameThreadStart(void* data)
{
	DEBUG_LOG("GameThread Starting");

	LGameBase::GetGame()->Update();

	DEBUG_LOG("GameThread Ending");
	return 0;
}

//===============================================================
int RenderThreadStart(void* data)
{
	DEBUG_LOG("RenderThread Starting");

	//m_MainWindow.Update()

	DEBUG_LOG("RenderThread Ending");
	return 0;
}