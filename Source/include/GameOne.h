//! \file GameOne.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Header for GameOne.cpp
//!
#ifndef _GAMEONE_H_
#define _GAMEONE_H_

#include "LGameBase.h"
#include "LObject.h"
#include "LSprite.h"

#include "Banana.h"

#include "types.h"

#include "LEvents.h"

enum class eGameEventType
{
	GameEvent_pause,
	GameEvent_Num,
};

union uGameEventData
{
	struct
	{
		int pause_level;
	} pause;
};

typedef LEventManager<eGameEventType, uGameEventData> TGameEventManager;

//! \brief an Example game, called "One"
class GameOne
: public LGameBase
{
public:

	// Default ctor and dtor
	GameOne();
	~GameOne();

	// Inherited methods as defined in LObject.h
	virtual LError Create();
	virtual LError Initialise();
	virtual LError PreUpdate();
	virtual LError Update(ms elapsed);
	virtual LError PostUpdate();
	virtual LError Reset();
	virtual LError Destroy();

	LError HandleEvent( const TGameEventManager::TEvent* event );

private:

	Banana m_banana;

	//! \brief The Game Event Manager
	TGameEventManager m_myEventManager;

	//! \brief the event handler for the main game class
	TGameEventManager::THandler m_myEventHandler;
};


#endif //_GAMEONE_H_