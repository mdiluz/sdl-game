//! \file LRenderer.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Header for LRenderer.cpp
//!
#ifndef _LRENDERER_H_
#define _LRENDERER_H_

#include "types.h"

#include "SDLRenderer.h"

#include <vector>

//! \brief The renderable base class
class LRendereable2D
{
public:

	//! \brief default ctor
	LRendereable2D();

	//! \brief default dtor
	~LRendereable2D();

	//! \brief the pure virtual render method
	//! Overload this to perform the render
	virtual eError Render( SDLInterface::Renderer& renderer ) = 0;

	//! \brief inline set for the Z value
	inline void SetZ( int Z )
	{
		m_zValue = Z;
	}

	//! \brief inline get for the Z value
	inline int GetZ() const 
	{
		return m_zValue;
	}

private:

	//! \brief the internal Z value
	int m_zValue;
	
};



//! \brief A 2D Renderer
//! Allows registering a set of renderables, that it can then choose what to do with
class LRenderer2D
{
public:

	//! \brief default ctor
	LRenderer2D();

	//! \brief default dtor
	~LRenderer2D();

	//! \brief create the renderer
	eError Create();

	//! \brief Add a renderable
	eError AddRenderable(LRendereable2D* toAdd);

	//! \brief Remove a renderable
	eError RemoveRenderable(LRendereable2D* toAdd);

	//! \brief perform the render
	eError Render();

	//! \brief destroy the renderer
	eError Destroy();

private:

	//! \brief the full list of renderables
	std::vector<LRendereable2D*> m_vecRenderables;

	//! \brief The underlying renderer
	SDLInterface::Renderer m_Renderer;

};

#endif //_LRENDERER_H_