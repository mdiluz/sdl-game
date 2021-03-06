//! \file LError.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Header for the engine error type
//!
#ifndef _LERROR_H_
#define _LERROR_H_

//! Great explanation on how this can work is here 
//! http://forum.codecall.net/topic/56591-bit-fields-flags-tutorial-with-example/


//! Warning flag
#define _ERROR_WARNING		(LError)0x1000

//! Fatal flag
#define _ERROR_FATAL		(LError)0x2000


//! \brief generic LError enum for LError handling
enum class LError : int
{
	// 	LError name		  LError bit value for flags
	NoErr		= 0x0000,

	// 	Specific Errors     Last 4 bits for specific errors
	QuitRequest = 0x0001,

	Fatal		= 0x0002,
	Warning		= 0x0004,

	// ALL errors
	All			= 0xFFFF,

};

//! \brief bitwise or operator 
//! returns an enum containing a combination the bits of \a lhs and \a rhs
inline LError operator | (LError lhs, LError rhs)
{
	return (LError)((int)lhs | (int)rhs);
}

//! \brief bitwise & operator
//! returns an enum containing only the shared bits of \a lhs and \a rhs
inline LError operator & (LError lhs, LError rhs)
{
	return (LError)((int)lhs & (int)rhs);
}

//! \brief bitwise ~ operator for const errors
inline LError operator ~ (const LError& err)
{
	return (LError)(~(int)err);
}

//! \brief bitwise | and assignement operator
inline LError& operator |= (LError& lhs, LError rhs)
{
	lhs = lhs | rhs;
	return lhs;
}

//! \brief bitwise | and assignement operator
inline LError& operator += (LError& lhs, LError rhs)
{
	lhs = lhs | rhs;
	return lhs;
}

//! \brief bitwise & and assignement operator
inline LError& operator &= (LError& lhs, LError rhs)
{
	lhs = lhs & rhs;
	return lhs;
}

//! \brief Check if the error contains
#define LERROR_HAS( err , contains )				( (err & (contains) ) == (contains) )

//! \brief Check if LError is fatal
#define LERROR_HAS_FATAL( err ) 			( LERROR_HAS( err , (LError)_ERROR_FATAL)			) 

//! \brief Check if LError is warning
#define LERROR_HAS_WARNING( err ) 			( LERROR_HAS( err , (LError)_ERROR_WARNING )		)

//! \brief Check if LError is an SDL LError
#define REMOVE_ERR( err , toremove )			( err &= ( ~(toremove) ) )


#endif //_LERROR_H_
