//***********************************************
//	USER_globalDef.h
//***********************************************

#ifndef _USER_GLOBALDEF_H_
#define _USER_GLOBALDEF_H_

#include "stm8s.h"

/* ******************************************************************
 *	TYPES
 * ******************************************************************/

typedef unsigned char U8;
typedef unsigned int U16;
typedef unsigned long U32;
typedef unsigned long long U64;

typedef signed char S8;
typedef signed int S16;
typedef signed long S32;
typedef signed long long S64;

// Brief:		General function pointer
typedef bool (*Func_Ptr_GetBool)(void);

#endif /* _USER_GLOBALDEF_H_*/
