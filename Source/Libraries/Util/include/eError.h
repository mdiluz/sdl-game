//! \file eError.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Contains eError handling types and methods
#ifndef _ERROR_H_
#define _ERROR_H_

//! Great explanation on how this can work is here 
//! http://forum.codecall.net/topic/56591-bit-fields-flags-tutorial-with-example/

//! \brief generic eError enum for eError handling
enum class eError : int
{
// 	eError name		  eError bit value for flags
	NoErr			= 0x00000000,

	// 	eError types         First two bytes for erro types
	Type_Fatal		= 0x10000000, 	// Fatal flag
	Type_Warning	= 0x20000000, 	// Warning flag

	// 	Specific Errors     Last 4 bits for specific errors
	QuitRequest		= 0x00000001,

	// ALL errors
	All = 0x11111111,

};

//! \brief bitwise or operator 
//! returns an enum containing a combination the bits of \a lhs and \a rhs
inline eError operator | (eError lhs, eError rhs)
{
	return (eError)((int)lhs | (int)rhs);
}

//! \brief bitwise & operator
//! returns an enum containing only the shared bits of \a lhs and \a rhs
inline eError operator & (eError lhs, eError rhs)
{
	return (eError)((int)lhs & (int)rhs);
}

//! \brief bitwise ~ operator for const errors
inline eError operator ~ (const eError& err)
{
	return (eError)(~(int)err);
}

//! \brief bitwise | and assignement operator
inline eError& operator |= (eError& lhs, eError rhs)
{
	lhs = lhs | rhs;
	return lhs;
}

//! \brief bitwise | and assignement operator
inline eError& operator += (eError& lhs, eError rhs)
{
	lhs = lhs | rhs;
	return lhs;
}

//! \brief bitwise & and assignement operator
inline eError& operator &= (eError& lhs, eError rhs)
{
	lhs = lhs & rhs;
	return lhs;
}

//! \brief Check if the error contains
#define ERROR_HAS( err , contains )				( (err & (contains) ) == (contains) )

//! \brief Check if eError is fatal
#define ERROR_HAS_TYPE_FATAL( err ) 			( ERROR_HAS( err , eError::Type_Fatal )			) 

//! \brief Check if eError is warning
#define ERROR_HAS_TYPE_WARNING( err ) 			( ERROR_HAS( err , eError::Type_Warning )		)

//! \brief Check if eError is an SDL eError
#define REMOVE_ERR( err , toremove )			( err &= ( ~(toremove) ) )


#endif //_ERROR_H_
