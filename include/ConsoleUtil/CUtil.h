/* UTF-8 encoding
* Project URL: https://github.com/BH2WFR/ConsoleUtil
  Author:		BH2WFR
  Updated:		2 JAN 2025
  License:		MIT License
* You can include this header in header files.
*/
#ifndef CONSOLEUTIL_C_UTIL_H__
#define CONSOLEUTIL_C_UTIL_H__
#include <ConsoleUtil/Base.h>

//* warning: do not use macros with name starting with underscore `_` externally.






//===================== Basic Macros =========================
#define CUTIL_EMPTY()										// empty macro function
#define CUTIL_DEFAULT										// empty macro
// #define CUTIL_DEFER(_x)			_x CUTIL_EMPTY
#define CUTIL_EXPAND(...)			__VA_ARGS__ 			// expand `__VA_ARGS__` in MSVC without `/Zc:preprocessor`
#define CUTIL_SELF(_x)				_x						// expand
#define CUTIL_ZERO()				0						// do not delete `()`
#define CUTIL_COMMA					,						// a comma that can avoid recognizing as seperator of arguments
#define CUTIL_CAT_RAW(_1, _2)		_1 ## _2 				// do not merge with `_CUTIL_CAT_2()`
#define CUTIL_CAT_TOKENS(_1, _2)	CUTIL_CAT_RAW(_1, _2) 	// for enable unwrapping after `##` concatenation


#define _CUTIL_GET_1ST_ARG(_1, ...)		_1
#define _CUTIL_CHK_1ST_ARG(...)			CUTIL_EXPAND(_CUTIL_GET_1ST_ARG(__VA_ARGS__, 0)) // if 1st param dosen't exist, returns 0
#define _CUTIL_GET_2ND_ARG(_1, _2, ...)	_2
#define _CUTIL_CHK_2ND_ARG(...)			CUTIL_EXPAND(_CUTIL_GET_2ND_ARG(__VA_ARGS__, 0, 0)) // if 2nd param dosen't exist, returns 0
#define _CUTIL_GET_63TH_ARG(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z, \
							A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,_63,...)  _63


// #define _CUTIL_PARAMS_SINCE_2ND(_1, ...)	 CUTIL_EXPAND(__VA_ARGS__) // retrive all params since 2nd, and drop 1st param
// #define _CUTIL_PARAMS_SINCE_3RD(_1, _2, ...) CUTIL_EXPAND(__VA_ARGS__)


//* string conversion support
#define CUTIL_STR(_1)				#_1
#define CUTIL_LSTR(_1)				CUTIL_CAT_RAW(L, #_1)	// wchar_t
#define CUTIL_U8STR(_1)				CUTIL_CAT_RAW(u8, #_1) 	// C++17, char8_t
#define CUTIL_U16STR(_1)			CUTIL_CAT_RAW(u, #_1) 	// C++11, char16_t
#define CUTIL_U32STR(_1)			CUTIL_CAT_RAW(U, #_1) 	// C++11, char32_t



//* detect whether build mode is in Debug or Release
#if (!defined(NDEBUG)) || defined(_DEBUG)
	#define CUTIL_DEBUG_BUILD 	 1 	// Debug
#else
	#define CUTIL_DEBUG_BUILD 	 0 	// Release RelWithDebInfo MinSizeRel
#endif
/*
	in MSVC, macro `_DEBUG` is defined under debug build;
	in GCC, macro `NDEBUG` is defined under release build, also for projects configured by CMake.
	you can add `add_compile_definitions("$<IF:$<CONFIG:Debug>,_DEBUG,NDEBUG>")` in CMake.
	
Usage Example:
	#if CUTIL_DEBUG_BUILD // Debug
		//...
	#else // Release RelWithDebInfo MinSizeRel
		//...
	#endif
*/


//* BOOL statement
#define CUTIL_NOT(_x)				_CUTIL_CHK_2ND_ARG(CUTIL_CAT_TOKENS(_CUTIL_NOT_, _x))
#define _CUTIL_NOT_0				~, 1
#define _CUTIL_NOT_false			~, 1
#define _CUTIL_NOT_FALSE			~, 1
#define _CUTIL_NOT_nullptr			~, 1
#define _CUTIL_NOT_NULL				~, 1
#define _CUTIL_NOT_00				~, 1
#define _CUTIL_NOT_000				~, 1
#define _CUTIL_NOT_0000				~, 1
#define _CUTIL_NOT_00000			~, 1
#define _CUTIL_NOT_000000			~, 1
#define _CUTIL_NOT_0000000			~, 1
#define _CUTIL_NOT_00000000			~, 1
#define _CUTIL_NOT_0b0				~, 1
#define _CUTIL_NOT_0b00				~, 1
#define _CUTIL_NOT_0b000			~, 1
#define _CUTIL_NOT_0b0000			~, 1
#define _CUTIL_NOT_0b00000			~, 1
#define _CUTIL_NOT_0b000000			~, 1
#define _CUTIL_NOT_0b0000000		~, 1
#define _CUTIL_NOT_0b00000000		~, 1
#define _CUTIL_NOT_0x0				~, 1
#define _CUTIL_NOT_0x00				~, 1
#define _CUTIL_NOT_0x000			~, 1
#define _CUTIL_NOT_0x0000			~, 1
#define _CUTIL_NOT_0x00000			~, 1
#define _CUTIL_NOT_0x000000			~, 1
#define _CUTIL_NOT_0x0000000		~, 1
#define _CUTIL_NOT_0x00000000		~, 1


#define CUTIL_BOOL(_x)				CUTIL_NOT(CUTIL_NOT(_x))

#define CUTIL_OR(_x, _y)			CUTIL_CAT_TOKENS(_CUTIL_OR_, CUTIL_BOOL(_x))(CUTIL_BOOL(_y))
#define _CUTIL_OR_0(_x)				_x
#define _CUTIL_OR_1(_x)				1

#define CUTIL_AND(_x, _y)			CUTIL_CAT_TOKENS(_CUTIL_AND_, CUTIL_BOOL(_x))(CUTIL_BOOL(_y))
#define _CUTIL_AND_0(_x)			0
#define _CUTIL_AND_1(_x)			_x

#define CUTIL_XOR(_x, _y)			CUTIL_CAT_TOKENS(_CUTIL_XOR_, CUTIL_BOOL(_x))(CUTIL_BOOL(_y))
#define _CUTIL_XOR_0(_x)			_x
#define _CUTIL_XOR_1(_x)			CUTIL_NOT(_x)

#define CUTIL_NOR(_x, _y)			CUTIL_NOT(CUTIL_OR(_x, _y))
/*
	CUTIL_BOOL(abcd);	// -> 1
	CUTIL_BOOL(345);	// -> 1
	CUTIL_BOOL(1);		// -> 1
	CUTIL_BOOL(0);		// -> 0
	CUTIL_BOOL();		// ERROR: you must provide an argument, or it will be evaluated to 1.
*/



//* IF statement
#define CUTIL_IF(_condition, _trueVal, _falseVal) CUTIL_CAT_TOKENS(_CUTIL_IF_, CUTIL_BOOL(_condition))((_trueVal), _falseVal)
#define _CUTIL_IF_0(_trueVal, _falseVal) 		_falseVal
#define _CUTIL_IF_1(_trueVal, _falseVal) 		_trueVal
/*
	CUTIL_IF(1, a, b)		-> a
	CUTIL_IF(0, a, b)		-> b
	CUTIL_IF(666, a, b)		-> a
*/



//* get count of arguments, up to 35 params
#define CUTIL_VA_EXISTS(...) 	CUTIL_EXPAND(CUTIL_BOOL(_CUTIL_GET_1ST_ARG(CUTIL_ZERO __VA_ARGS__)()))
// #define CUTIL_COMMA_OPT(...)	CUTIL_EXPAND(CUTIL_CAT_TOKENS(_CUTIL_IF_, CUTIL_VA_EXISTS(__VA_ARGS__))(CUTIL_COMMA, CUTIL_EMPTY()))

#define _CUTIL_VA_CNT_0(...)	0	// for compilers that do not support `##__VA_ARGS__` to eliminate leading comma if empty
#define _CUTIL_VA_CNT_1(...)	CUTIL_EXPAND(_CUTIL_GET_63TH_ARG("ignored", __VA_ARGS__, \
			Z,Y,X,W,V,U,T,S,R,Q,P,O,N,M,L,K,J,I,H,G,F,E,D,C,B,A,35,34,33,32,31,30,29,28,27, \
			26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0))
#define CUTIL_VA_CNT(...)		CUTIL_OVERLOAD_IDX(_CUTIL_VA_CNT_, CUTIL_VA_EXISTS(__VA_ARGS__))(__VA_ARGS__)
// #define CUTIL_VA_CNT(...)		CUTIL_EXPAND(_CUTIL_GET_63TH_ARG("ignored", ##__VA_ARGS__, \
// 			Z,Y,X,W,V,U,T,S,R,Q,P,O,N,M,L,K,J,I,H,G,F,E,D,C,B,A,35,34,33,32,31,30,29,28,27, \
// 			26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0))
/*
 Examples:
	int a = CUTIL_VA_CNT(); 			// -> 0
	int b = CUTIL_VA_CNT(b1); 			// -> 1
	int c = CUTIL_VA_CNT(c1, c2); 		// -> 2
	int d = CUTIL_VA_CNT(c1, c2, c3); 	// -> 3
	...
	int a = CUTIL_VA_EXISTS(); 			// -> 0
	int b = CUTIL_VA_EXISTS(b1); 		// -> 1
	int c = CUTIL_VA_EXISTS(c1, c2); 	// -> 1
	int d = CUTIL_VA_EXISTS(c1, c2, c3);// -> 1
*/


//* macro function overloading support
#define CUTIL_OVERLOAD_IDX(_func, _idx)		CUTIL_CAT_RAW(_func, _idx)
#define CUTIL_OVERLOAD_AMOUNT(_func, ...) 	CUTIL_OVERLOAD_IDX(_func, CUTIL_VA_CNT(__VA_ARGS__))
/* example:
	CUTIL_OVERLOAD_IDX(MyFunc, 2)(); 	// MyFunc2();
	CUTIL_OVERLOAD_IDX(var_, 3) = 10; 	// var_3 = 10;
	
	// Deduce suffix by amount of arguments within the macro
	CUTIL_OVERLOAD_AMOUNT(MyFunc, 2, 4, 6)(2, 4, 6); // MyFunc3(2, 4, 6);
*/


//* token concatenation support, up to 25 tokens
#define CUTIL_CAT(...)        		CUTIL_EXPAND(CUTIL_OVERLOAD_AMOUNT(_CUTIL_CAT_, __VA_ARGS__)(__VA_ARGS__))
	// The following macro definitions are private, DO NOT call them EXTERNALLY.
#define _CUTIL_CAT_2(_1, _2)		CUTIL_CAT_TOKENS(_1, _2)
#define _CUTIL_CAT_3(_1, ...)		CUTIL_EXPAND(CUTIL_CAT_TOKENS(_1, _CUTIL_CAT_2(__VA_ARGS__)))
#define _CUTIL_CAT_4(_1, ...)		CUTIL_EXPAND(CUTIL_CAT_TOKENS(_1, _CUTIL_CAT_3(__VA_ARGS__)))
#define _CUTIL_CAT_5(_1, ...)		CUTIL_EXPAND(CUTIL_CAT_TOKENS(_1, _CUTIL_CAT_4(__VA_ARGS__)))
#define _CUTIL_CAT_6(_1, ...)		CUTIL_EXPAND(CUTIL_CAT_TOKENS(_1, _CUTIL_CAT_5(__VA_ARGS__)))
#define _CUTIL_CAT_7(_1, ...)		CUTIL_EXPAND(CUTIL_CAT_TOKENS(_1, _CUTIL_CAT_6(__VA_ARGS__)))
#define _CUTIL_CAT_8(_1, ...)		CUTIL_EXPAND(CUTIL_CAT_TOKENS(_1, _CUTIL_CAT_7(__VA_ARGS__)))
#define _CUTIL_CAT_9(_1, ...)		CUTIL_EXPAND(CUTIL_CAT_TOKENS(_1, _CUTIL_CAT_8(__VA_ARGS__)))
#define _CUTIL_CAT_10(_1, ...)		CUTIL_EXPAND(CUTIL_CAT_TOKENS(_1, _CUTIL_CAT_9(__VA_ARGS__)))
#define _CUTIL_CAT_11(_1, ...)		CUTIL_EXPAND(CUTIL_CAT_TOKENS(_1, _CUTIL_CAT_10(__VA_ARGS__)))
#define _CUTIL_CAT_12(_1, ...)		CUTIL_EXPAND(CUTIL_CAT_TOKENS(_1, _CUTIL_CAT_11(__VA_ARGS__)))
#define _CUTIL_CAT_13(_1, ...)		CUTIL_EXPAND(CUTIL_CAT_TOKENS(_1, _CUTIL_CAT_12(__VA_ARGS__)))
#define _CUTIL_CAT_14(_1, ...)		CUTIL_EXPAND(CUTIL_CAT_TOKENS(_1, _CUTIL_CAT_13(__VA_ARGS__)))
#define _CUTIL_CAT_15(_1, ...)		CUTIL_EXPAND(CUTIL_CAT_TOKENS(_1, _CUTIL_CAT_14(__VA_ARGS__)))
#define _CUTIL_CAT_16(_1, ...)		CUTIL_EXPAND(CUTIL_CAT_TOKENS(_1, _CUTIL_CAT_15(__VA_ARGS__)))
#define _CUTIL_CAT_17(_1, ...)		CUTIL_EXPAND(CUTIL_CAT_TOKENS(_1, _CUTIL_CAT_16(__VA_ARGS__)))
#define _CUTIL_CAT_18(_1, ...)		CUTIL_EXPAND(CUTIL_CAT_TOKENS(_1, _CUTIL_CAT_17(__VA_ARGS__)))
#define _CUTIL_CAT_19(_1, ...)		CUTIL_EXPAND(CUTIL_CAT_TOKENS(_1, _CUTIL_CAT_18(__VA_ARGS__)))
#define _CUTIL_CAT_20(_1, ...)		CUTIL_EXPAND(CUTIL_CAT_TOKENS(_1, _CUTIL_CAT_19(__VA_ARGS__)))
#define _CUTIL_CAT_21(_1, ...)		CUTIL_EXPAND(CUTIL_CAT_TOKENS(_1, _CUTIL_CAT_20(__VA_ARGS__)))
#define _CUTIL_CAT_22(_1, ...)		CUTIL_EXPAND(CUTIL_CAT_TOKENS(_1, _CUTIL_CAT_21(__VA_ARGS__)))
#define _CUTIL_CAT_23(_1, ...)		CUTIL_EXPAND(CUTIL_CAT_TOKENS(_1, _CUTIL_CAT_22(__VA_ARGS__)))
#define _CUTIL_CAT_24(_1, ...)		CUTIL_EXPAND(CUTIL_CAT_TOKENS(_1, _CUTIL_CAT_23(__VA_ARGS__)))
#define _CUTIL_CAT_25(_1, ...)		CUTIL_EXPAND(CUTIL_CAT_TOKENS(_1, _CUTIL_CAT_24(__VA_ARGS__))) // recurse upwards
/* Instruction:
	int a1 = CUTIL_CAT(11, 22); 			// a1 = 1122
	int a2 = CUTIL_CAT(10, 11, 12, 13); 	// a2 = 10111213
	std::cout << CUTIL_CAT(a, 1) << "\n"; 	// print variable `a1`
*/



//===================== Bool Statements =========================

//* to generate the code like `(var == 1 || var == 2 || var == 3 || ...)`, up to 25 compared params
#define CUTIL_EQUAL_ANY(_var, ...) 			(CUTIL_EXPAND(CUTIL_OVERLOAD_AMOUNT(_CUTIL_EQUAL_ANY_, __VA_ARGS__)(_var, __VA_ARGS__)))
	// The following macro definitions are private, DO NOT call them EXTERNALLY.
#define _CUTIL_EQUAL_ANY_1(_var, _1) 		(_var) == (_1)
#define _CUTIL_EQUAL_ANY_2(_var, _1, _2) 	(_var) == (_1) || _CUTIL_EQUAL_ANY_1(_var, _2)
#define _CUTIL_EQUAL_ANY_3(_var, _1, ...) 	CUTIL_EXPAND((_var) == (_1) || _CUTIL_EQUAL_ANY_2(_var, __VA_ARGS__))
#define _CUTIL_EQUAL_ANY_4(_var, _1, ...) 	CUTIL_EXPAND((_var) == (_1) || _CUTIL_EQUAL_ANY_3(_var, __VA_ARGS__))
#define _CUTIL_EQUAL_ANY_5(_var, _1, ...) 	CUTIL_EXPAND((_var) == (_1) || _CUTIL_EQUAL_ANY_4(_var, __VA_ARGS__))
#define _CUTIL_EQUAL_ANY_6(_var, _1, ...) 	CUTIL_EXPAND((_var) == (_1) || _CUTIL_EQUAL_ANY_5(_var, __VA_ARGS__))
#define _CUTIL_EQUAL_ANY_7(_var, _1, ...) 	CUTIL_EXPAND((_var) == (_1) || _CUTIL_EQUAL_ANY_6(_var, __VA_ARGS__))
#define _CUTIL_EQUAL_ANY_8(_var, _1, ...) 	CUTIL_EXPAND((_var) == (_1) || _CUTIL_EQUAL_ANY_7(_var, __VA_ARGS__))
#define _CUTIL_EQUAL_ANY_9(_var, _1, ...) 	CUTIL_EXPAND((_var) == (_1) || _CUTIL_EQUAL_ANY_8(_var, __VA_ARGS__))
#define _CUTIL_EQUAL_ANY_10(_var, _1, ...) 	CUTIL_EXPAND((_var) == (_1) || _CUTIL_EQUAL_ANY_9(_var, __VA_ARGS__))
#define _CUTIL_EQUAL_ANY_11(_var, _1, ...) 	CUTIL_EXPAND((_var) == (_1) || _CUTIL_EQUAL_ANY_10(_var, __VA_ARGS__))
#define _CUTIL_EQUAL_ANY_12(_var, _1, ...) 	CUTIL_EXPAND((_var) == (_1) || _CUTIL_EQUAL_ANY_11(_var, __VA_ARGS__))
#define _CUTIL_EQUAL_ANY_13(_var, _1, ...) 	CUTIL_EXPAND((_var) == (_1) || _CUTIL_EQUAL_ANY_12(_var, __VA_ARGS__))
#define _CUTIL_EQUAL_ANY_14(_var, _1, ...) 	CUTIL_EXPAND((_var) == (_1) || _CUTIL_EQUAL_ANY_13(_var, __VA_ARGS__))
#define _CUTIL_EQUAL_ANY_15(_var, _1, ...) 	CUTIL_EXPAND((_var) == (_1) || _CUTIL_EQUAL_ANY_14(_var, __VA_ARGS__))
#define _CUTIL_EQUAL_ANY_16(_var, _1, ...) 	CUTIL_EXPAND((_var) == (_1) || _CUTIL_EQUAL_ANY_15(_var, __VA_ARGS__))
#define _CUTIL_EQUAL_ANY_17(_var, _1, ...) 	CUTIL_EXPAND((_var) == (_1) || _CUTIL_EQUAL_ANY_16(_var, __VA_ARGS__))
#define _CUTIL_EQUAL_ANY_18(_var, _1, ...) 	CUTIL_EXPAND((_var) == (_1) || _CUTIL_EQUAL_ANY_17(_var, __VA_ARGS__))
#define _CUTIL_EQUAL_ANY_19(_var, _1, ...) 	CUTIL_EXPAND((_var) == (_1) || _CUTIL_EQUAL_ANY_18(_var, __VA_ARGS__))
#define _CUTIL_EQUAL_ANY_20(_var, _1, ...) 	CUTIL_EXPAND((_var) == (_1) || _CUTIL_EQUAL_ANY_19(_var, __VA_ARGS__))
#define _CUTIL_EQUAL_ANY_21(_var, _1, ...) 	CUTIL_EXPAND((_var) == (_1) || _CUTIL_EQUAL_ANY_20(_var, __VA_ARGS__))
#define _CUTIL_EQUAL_ANY_22(_var, _1, ...) 	CUTIL_EXPAND((_var) == (_1) || _CUTIL_EQUAL_ANY_21(_var, __VA_ARGS__))
#define _CUTIL_EQUAL_ANY_23(_var, _1, ...) 	CUTIL_EXPAND((_var) == (_1) || _CUTIL_EQUAL_ANY_22(_var, __VA_ARGS__))
#define _CUTIL_EQUAL_ANY_24(_var, _1, ...) 	CUTIL_EXPAND((_var) == (_1) || _CUTIL_EQUAL_ANY_23(_var, __VA_ARGS__))
#define _CUTIL_EQUAL_ANY_25(_var, _1, ...) 	CUTIL_EXPAND((_var) == (_1) || _CUTIL_EQUAL_ANY_24(_var, __VA_ARGS__)) // recurse upwards

//* to generate the code like `(var == 1 && var == 2 && var == 3 && ...)`, up to 25 compared params
#define CUTIL_EQUAL_ALL(_var, ...) 			(CUTIL_EXPAND(CUTIL_OVERLOAD_AMOUNT(_CUTIL_EQUAL_ALL_, __VA_ARGS__)(_var, __VA_ARGS__)))
	// The following macro definitions are private, DO NOT call them EXTERNALLY.
#define _CUTIL_EQUAL_ALL_1(_var, _1) 		(_var) == (_1)
#define _CUTIL_EQUAL_ALL_2(_var, _1, _2) 	(_var) == (_1) && _CUTIL_EQUAL_ALL_1(_var, _2)
#define _CUTIL_EQUAL_ALL_3(_var, _1, ...) 	CUTIL_EXPAND((_var) == (_1) && _CUTIL_EQUAL_ALL_2(_var, __VA_ARGS__))
#define _CUTIL_EQUAL_ALL_4(_var, _1, ...) 	CUTIL_EXPAND((_var) == (_1) && _CUTIL_EQUAL_ALL_3(_var, __VA_ARGS__))
#define _CUTIL_EQUAL_ALL_5(_var, _1, ...) 	CUTIL_EXPAND((_var) == (_1) && _CUTIL_EQUAL_ALL_4(_var, __VA_ARGS__))
#define _CUTIL_EQUAL_ALL_6(_var, _1, ...) 	CUTIL_EXPAND((_var) == (_1) && _CUTIL_EQUAL_ALL_5(_var, __VA_ARGS__))
#define _CUTIL_EQUAL_ALL_7(_var, _1, ...) 	CUTIL_EXPAND((_var) == (_1) && _CUTIL_EQUAL_ALL_6(_var, __VA_ARGS__))
#define _CUTIL_EQUAL_ALL_8(_var, _1, ...) 	CUTIL_EXPAND((_var) == (_1) && _CUTIL_EQUAL_ALL_7(_var, __VA_ARGS__))
#define _CUTIL_EQUAL_ALL_9(_var, _1, ...) 	CUTIL_EXPAND((_var) == (_1) && _CUTIL_EQUAL_ALL_8(_var, __VA_ARGS__))
#define _CUTIL_EQUAL_ALL_10(_var, _1, ...) 	CUTIL_EXPAND((_var) == (_1) && _CUTIL_EQUAL_ALL_9(_var, __VA_ARGS__))
#define _CUTIL_EQUAL_ALL_11(_var, _1, ...) 	CUTIL_EXPAND((_var) == (_1) && _CUTIL_EQUAL_ALL_10(_var, __VA_ARGS__))
#define _CUTIL_EQUAL_ALL_12(_var, _1, ...) 	CUTIL_EXPAND((_var) == (_1) && _CUTIL_EQUAL_ALL_11(_var, __VA_ARGS__))
#define _CUTIL_EQUAL_ALL_13(_var, _1, ...) 	CUTIL_EXPAND((_var) == (_1) && _CUTIL_EQUAL_ALL_12(_var, __VA_ARGS__))
#define _CUTIL_EQUAL_ALL_14(_var, _1, ...) 	CUTIL_EXPAND((_var) == (_1) && _CUTIL_EQUAL_ALL_13(_var, __VA_ARGS__))
#define _CUTIL_EQUAL_ALL_15(_var, _1, ...) 	CUTIL_EXPAND((_var) == (_1) && _CUTIL_EQUAL_ALL_14(_var, __VA_ARGS__))
#define _CUTIL_EQUAL_ALL_16(_var, _1, ...) 	CUTIL_EXPAND((_var) == (_1) && _CUTIL_EQUAL_ALL_15(_var, __VA_ARGS__))
#define _CUTIL_EQUAL_ALL_17(_var, _1, ...) 	CUTIL_EXPAND((_var) == (_1) && _CUTIL_EQUAL_ALL_16(_var, __VA_ARGS__))
#define _CUTIL_EQUAL_ALL_18(_var, _1, ...) 	CUTIL_EXPAND((_var) == (_1) && _CUTIL_EQUAL_ALL_17(_var, __VA_ARGS__))
#define _CUTIL_EQUAL_ALL_19(_var, _1, ...) 	CUTIL_EXPAND((_var) == (_1) && _CUTIL_EQUAL_ALL_18(_var, __VA_ARGS__))
#define _CUTIL_EQUAL_ALL_20(_var, _1, ...) 	CUTIL_EXPAND((_var) == (_1) && _CUTIL_EQUAL_ALL_19(_var, __VA_ARGS__))
#define _CUTIL_EQUAL_ALL_21(_var, _1, ...) 	CUTIL_EXPAND((_var) == (_1) && _CUTIL_EQUAL_ALL_20(_var, __VA_ARGS__))
#define _CUTIL_EQUAL_ALL_22(_var, _1, ...) 	CUTIL_EXPAND((_var) == (_1) && _CUTIL_EQUAL_ALL_21(_var, __VA_ARGS__))
#define _CUTIL_EQUAL_ALL_23(_var, _1, ...) 	CUTIL_EXPAND((_var) == (_1) && _CUTIL_EQUAL_ALL_22(_var, __VA_ARGS__))
#define _CUTIL_EQUAL_ALL_24(_var, _1, ...) 	CUTIL_EXPAND((_var) == (_1) && _CUTIL_EQUAL_ALL_23(_var, __VA_ARGS__))
#define _CUTIL_EQUAL_ALL_25(_var, _1, ...) 	CUTIL_EXPAND((_var) == (_1) && _CUTIL_EQUAL_ALL_24(_var, __VA_ARGS__)) // recurse upwards

//* to generate the code like `(var != 1 || var != 2 || var != 3 || ...)`, up to 25 compared params
#define CUTIL_UNEQUAL_ANY(_var, ...) 		  (CUTIL_EXPAND(CUTIL_OVERLOAD_AMOUNT(_CUTIL_UNEQUAL_ANY_, __VA_ARGS__)(_var, __VA_ARGS__)))
	// The following macro definitions are private, DO NOT call them EXTERNALLY.
#define _CUTIL_UNEQUAL_ANY_1(_var, _1) 		  (_var) != (_1)
#define _CUTIL_UNEQUAL_ANY_2(_var, _1, _2) 	  (_var) != (_1) || _CUTIL_UNEQUAL_ANY_1(_var, _2)
#define _CUTIL_UNEQUAL_ANY_3(_var, _1, ...)   CUTIL_EXPAND((_var) != (_1) || _CUTIL_UNEQUAL_ANY_2(_var, __VA_ARGS__))
#define _CUTIL_UNEQUAL_ANY_4(_var, _1, ...)   CUTIL_EXPAND((_var) != (_1) || _CUTIL_UNEQUAL_ANY_3(_var, __VA_ARGS__))
#define _CUTIL_UNEQUAL_ANY_5(_var, _1, ...)   CUTIL_EXPAND((_var) != (_1) || _CUTIL_UNEQUAL_ANY_4(_var, __VA_ARGS__))
#define _CUTIL_UNEQUAL_ANY_6(_var, _1, ...)   CUTIL_EXPAND((_var) != (_1) || _CUTIL_UNEQUAL_ANY_5(_var, __VA_ARGS__))
#define _CUTIL_UNEQUAL_ANY_7(_var, _1, ...)   CUTIL_EXPAND((_var) != (_1) || _CUTIL_UNEQUAL_ANY_6(_var, __VA_ARGS__))
#define _CUTIL_UNEQUAL_ANY_8(_var, _1, ...)   CUTIL_EXPAND((_var) != (_1) || _CUTIL_UNEQUAL_ANY_7(_var, __VA_ARGS__))
#define _CUTIL_UNEQUAL_ANY_9(_var, _1, ...)   CUTIL_EXPAND((_var) != (_1) || _CUTIL_UNEQUAL_ANY_8(_var, __VA_ARGS__))
#define _CUTIL_UNEQUAL_ANY_10(_var, _1, ...)  CUTIL_EXPAND((_var) != (_1) || _CUTIL_UNEQUAL_ANY_9(_var, __VA_ARGS__))
#define _CUTIL_UNEQUAL_ANY_11(_var, _1, ...)  CUTIL_EXPAND((_var) != (_1) || _CUTIL_UNEQUAL_ANY_10(_var, __VA_ARGS__))
#define _CUTIL_UNEQUAL_ANY_12(_var, _1, ...)  CUTIL_EXPAND((_var) != (_1) || _CUTIL_UNEQUAL_ANY_11(_var, __VA_ARGS__))
#define _CUTIL_UNEQUAL_ANY_13(_var, _1, ...)  CUTIL_EXPAND((_var) != (_1) || _CUTIL_UNEQUAL_ANY_12(_var, __VA_ARGS__))
#define _CUTIL_UNEQUAL_ANY_14(_var, _1, ...)  CUTIL_EXPAND((_var) != (_1) || _CUTIL_UNEQUAL_ANY_13(_var, __VA_ARGS__))
#define _CUTIL_UNEQUAL_ANY_15(_var, _1, ...)  CUTIL_EXPAND((_var) != (_1) || _CUTIL_UNEQUAL_ANY_14(_var, __VA_ARGS__))
#define _CUTIL_UNEQUAL_ANY_16(_var, _1, ...)  CUTIL_EXPAND((_var) != (_1) || _CUTIL_UNEQUAL_ANY_15(_var, __VA_ARGS__))
#define _CUTIL_UNEQUAL_ANY_17(_var, _1, ...)  CUTIL_EXPAND((_var) != (_1) || _CUTIL_UNEQUAL_ANY_16(_var, __VA_ARGS__))
#define _CUTIL_UNEQUAL_ANY_18(_var, _1, ...)  CUTIL_EXPAND((_var) != (_1) || _CUTIL_UNEQUAL_ANY_17(_var, __VA_ARGS__))
#define _CUTIL_UNEQUAL_ANY_19(_var, _1, ...)  CUTIL_EXPAND((_var) != (_1) || _CUTIL_UNEQUAL_ANY_18(_var, __VA_ARGS__))
#define _CUTIL_UNEQUAL_ANY_20(_var, _1, ...)  CUTIL_EXPAND((_var) != (_1) || _CUTIL_UNEQUAL_ANY_19(_var, __VA_ARGS__))
#define _CUTIL_UNEQUAL_ANY_21(_var, _1, ...)  CUTIL_EXPAND((_var) != (_1) || _CUTIL_UNEQUAL_ANY_20(_var, __VA_ARGS__))
#define _CUTIL_UNEQUAL_ANY_22(_var, _1, ...)  CUTIL_EXPAND((_var) != (_1) || _CUTIL_UNEQUAL_ANY_21(_var, __VA_ARGS__))
#define _CUTIL_UNEQUAL_ANY_23(_var, _1, ...)  CUTIL_EXPAND((_var) != (_1) || _CUTIL_UNEQUAL_ANY_22(_var, __VA_ARGS__))
#define _CUTIL_UNEQUAL_ANY_24(_var, _1, ...)  CUTIL_EXPAND((_var) != (_1) || _CUTIL_UNEQUAL_ANY_23(_var, __VA_ARGS__))
#define _CUTIL_UNEQUAL_ANY_25(_var, _1, ...)  CUTIL_EXPAND((_var) != (_1) || _CUTIL_UNEQUAL_ANY_24(_var, __VA_ARGS__)) // recurse upwards

//* to generate the code like `(var != 1 && var != 2 && var != 3 && ...)`, up to 25 compared params
#define CUTIL_UNEQUAL_ALL(_var, ...) 		  (CUTIL_EXPAND(CUTIL_OVERLOAD_AMOUNT(_CUTIL_UNEQUAL_ALL_, __VA_ARGS__)(_var, __VA_ARGS__)))
	// The following macro definitions are private, DO NOT call them EXTERNALLY.
#define _CUTIL_UNEQUAL_ALL_1(_var, _1) 		  (_var) != (_1)
#define _CUTIL_UNEQUAL_ALL_2(_var, _1, _2) 	  (_var) != (_1) && _CUTIL_UNEQUAL_ALL_1(_var, _2)
#define _CUTIL_UNEQUAL_ALL_3(_var, _1, ...)	  CUTIL_EXPAND((_var) != (_1) && _CUTIL_UNEQUAL_ALL_2(_var, __VA_ARGS__))
#define _CUTIL_UNEQUAL_ALL_4(_var, _1, ...)	  CUTIL_EXPAND((_var) != (_1) && _CUTIL_UNEQUAL_ALL_3(_var, __VA_ARGS__))
#define _CUTIL_UNEQUAL_ALL_5(_var, _1, ...)	  CUTIL_EXPAND((_var) != (_1) && _CUTIL_UNEQUAL_ALL_4(_var, __VA_ARGS__))
#define _CUTIL_UNEQUAL_ALL_6(_var, _1, ...)	  CUTIL_EXPAND((_var) != (_1) && _CUTIL_UNEQUAL_ALL_5(_var, __VA_ARGS__))
#define _CUTIL_UNEQUAL_ALL_7(_var, _1, ...)	  CUTIL_EXPAND((_var) != (_1) && _CUTIL_UNEQUAL_ALL_6(_var, __VA_ARGS__))
#define _CUTIL_UNEQUAL_ALL_8(_var, _1, ...)	  CUTIL_EXPAND((_var) != (_1) && _CUTIL_UNEQUAL_ALL_7(_var, __VA_ARGS__))
#define _CUTIL_UNEQUAL_ALL_9(_var, _1, ...)	  CUTIL_EXPAND((_var) != (_1) && _CUTIL_UNEQUAL_ALL_8(_var, __VA_ARGS__))
#define _CUTIL_UNEQUAL_ALL_10(_var, _1, ...)  CUTIL_EXPAND((_var) != (_1) && _CUTIL_UNEQUAL_ALL_9(_var, __VA_ARGS__))
#define _CUTIL_UNEQUAL_ALL_11(_var, _1, ...)  CUTIL_EXPAND((_var) != (_1) && _CUTIL_UNEQUAL_ALL_10(_var, __VA_ARGS__))
#define _CUTIL_UNEQUAL_ALL_12(_var, _1, ...)  CUTIL_EXPAND((_var) != (_1) && _CUTIL_UNEQUAL_ALL_11(_var, __VA_ARGS__))
#define _CUTIL_UNEQUAL_ALL_13(_var, _1, ...)  CUTIL_EXPAND((_var) != (_1) && _CUTIL_UNEQUAL_ALL_12(_var, __VA_ARGS__))
#define _CUTIL_UNEQUAL_ALL_14(_var, _1, ...)  CUTIL_EXPAND((_var) != (_1) && _CUTIL_UNEQUAL_ALL_13(_var, __VA_ARGS__))
#define _CUTIL_UNEQUAL_ALL_15(_var, _1, ...)  CUTIL_EXPAND((_var) != (_1) && _CUTIL_UNEQUAL_ALL_14(_var, __VA_ARGS__))
#define _CUTIL_UNEQUAL_ALL_16(_var, _1, ...)  CUTIL_EXPAND((_var) != (_1) && _CUTIL_UNEQUAL_ALL_15(_var, __VA_ARGS__))
#define _CUTIL_UNEQUAL_ALL_17(_var, _1, ...)  CUTIL_EXPAND((_var) != (_1) && _CUTIL_UNEQUAL_ALL_16(_var, __VA_ARGS__))
#define _CUTIL_UNEQUAL_ALL_18(_var, _1, ...)  CUTIL_EXPAND((_var) != (_1) && _CUTIL_UNEQUAL_ALL_17(_var, __VA_ARGS__))
#define _CUTIL_UNEQUAL_ALL_19(_var, _1, ...)  CUTIL_EXPAND((_var) != (_1) && _CUTIL_UNEQUAL_ALL_18(_var, __VA_ARGS__))
#define _CUTIL_UNEQUAL_ALL_20(_var, _1, ...)  CUTIL_EXPAND((_var) != (_1) && _CUTIL_UNEQUAL_ALL_19(_var, __VA_ARGS__))
#define _CUTIL_UNEQUAL_ALL_21(_var, _1, ...)  CUTIL_EXPAND((_var) != (_1) && _CUTIL_UNEQUAL_ALL_20(_var, __VA_ARGS__))
#define _CUTIL_UNEQUAL_ALL_22(_var, _1, ...)  CUTIL_EXPAND((_var) != (_1) && _CUTIL_UNEQUAL_ALL_21(_var, __VA_ARGS__))
#define _CUTIL_UNEQUAL_ALL_23(_var, _1, ...)  CUTIL_EXPAND((_var) != (_1) && _CUTIL_UNEQUAL_ALL_22(_var, __VA_ARGS__))
#define _CUTIL_UNEQUAL_ALL_24(_var, _1, ...)  CUTIL_EXPAND((_var) != (_1) && _CUTIL_UNEQUAL_ALL_23(_var, __VA_ARGS__))
#define _CUTIL_UNEQUAL_ALL_25(_var, _1, ...)  CUTIL_EXPAND((_var) != (_1) && _CUTIL_UNEQUAL_ALL_24(_var, __VA_ARGS__)) // recurse upwards

//* generate codes for checkingif all of the params are mutually equal, up to 25 params
#define CUTIL_EQUAL_MUTUALLY(...)			CUTIL_EXPAND(CUTIL_EQUAL_ALL(__VA_ARGS__))

//* generate codes for checking if all of the params are mutually nonequal, up to 25 params
	// CUTIL_UNEQUAL_MUTUALLY(a1, a2, a3, a4)
	//   -> (a1 != a2) && (a1 != a3) && (a1 != a4) && (a2 != a3) && (a2 != a4) && (a3 != a4)
#define CUTIL_UNEQUAL_MUTUALLY(...)			CUTIL_EXPAND(CUTIL_OVERLOAD_IDX(_CUTIL_UNEQUAL_MUTUALLY_, CUTIL_VA_CNT(__VA_ARGS__))(__VA_ARGS__))
#define _CUTIL_UNEQUAL_MUTUALLY_2(a1, a2)		CUTIL_UNEQUAL_ALL(a1, a2)
#define _CUTIL_UNEQUAL_MUTUALLY_3(a1, ...)	CUTIL_EXPAND(CUTIL_UNEQUAL_ALL(a1, __VA_ARGS__) && _CUTIL_UNEQUAL_MUTUALLY_2(__VA_ARGS__))
#define _CUTIL_UNEQUAL_MUTUALLY_4(a1, ...)	CUTIL_EXPAND(CUTIL_UNEQUAL_ALL(a1, __VA_ARGS__) && _CUTIL_UNEQUAL_MUTUALLY_3(__VA_ARGS__))
#define _CUTIL_UNEQUAL_MUTUALLY_5(a1, ...)	CUTIL_EXPAND(CUTIL_UNEQUAL_ALL(a1, __VA_ARGS__) && _CUTIL_UNEQUAL_MUTUALLY_4(__VA_ARGS__))
#define _CUTIL_UNEQUAL_MUTUALLY_6(a1, ...)	CUTIL_EXPAND(CUTIL_UNEQUAL_ALL(a1, __VA_ARGS__) && _CUTIL_UNEQUAL_MUTUALLY_5(__VA_ARGS__))
#define _CUTIL_UNEQUAL_MUTUALLY_7(a1, ...)	CUTIL_EXPAND(CUTIL_UNEQUAL_ALL(a1, __VA_ARGS__) && _CUTIL_UNEQUAL_MUTUALLY_6(__VA_ARGS__))
#define _CUTIL_UNEQUAL_MUTUALLY_8(a1, ...)	CUTIL_EXPAND(CUTIL_UNEQUAL_ALL(a1, __VA_ARGS__) && _CUTIL_UNEQUAL_MUTUALLY_7(__VA_ARGS__))
#define _CUTIL_UNEQUAL_MUTUALLY_9(a1, ...)	CUTIL_EXPAND(CUTIL_UNEQUAL_ALL(a1, __VA_ARGS__) && _CUTIL_UNEQUAL_MUTUALLY_8(__VA_ARGS__))
#define _CUTIL_UNEQUAL_MUTUALLY_10(a1, ...)	CUTIL_EXPAND(CUTIL_UNEQUAL_ALL(a1, __VA_ARGS__) && _CUTIL_UNEQUAL_MUTUALLY_9(__VA_ARGS__))
#define _CUTIL_UNEQUAL_MUTUALLY_11(a1, ...)	CUTIL_EXPAND(CUTIL_UNEQUAL_ALL(a1, __VA_ARGS__) && _CUTIL_UNEQUAL_MUTUALLY_10(__VA_ARGS__))
#define _CUTIL_UNEQUAL_MUTUALLY_12(a1, ...)	CUTIL_EXPAND(CUTIL_UNEQUAL_ALL(a1, __VA_ARGS__) && _CUTIL_UNEQUAL_MUTUALLY_11(__VA_ARGS__))
#define _CUTIL_UNEQUAL_MUTUALLY_13(a1, ...)	CUTIL_EXPAND(CUTIL_UNEQUAL_ALL(a1, __VA_ARGS__) && _CUTIL_UNEQUAL_MUTUALLY_12(__VA_ARGS__))
#define _CUTIL_UNEQUAL_MUTUALLY_14(a1, ...)	CUTIL_EXPAND(CUTIL_UNEQUAL_ALL(a1, __VA_ARGS__) && _CUTIL_UNEQUAL_MUTUALLY_13(__VA_ARGS__))
#define _CUTIL_UNEQUAL_MUTUALLY_15(a1, ...)	CUTIL_EXPAND(CUTIL_UNEQUAL_ALL(a1, __VA_ARGS__) && _CUTIL_UNEQUAL_MUTUALLY_14(__VA_ARGS__))
#define _CUTIL_UNEQUAL_MUTUALLY_16(a1, ...)	CUTIL_EXPAND(CUTIL_UNEQUAL_ALL(a1, __VA_ARGS__) && _CUTIL_UNEQUAL_MUTUALLY_15(__VA_ARGS__))
#define _CUTIL_UNEQUAL_MUTUALLY_17(a1, ...)	CUTIL_EXPAND(CUTIL_UNEQUAL_ALL(a1, __VA_ARGS__) && _CUTIL_UNEQUAL_MUTUALLY_16(__VA_ARGS__))
#define _CUTIL_UNEQUAL_MUTUALLY_18(a1, ...)	CUTIL_EXPAND(CUTIL_UNEQUAL_ALL(a1, __VA_ARGS__) && _CUTIL_UNEQUAL_MUTUALLY_17(__VA_ARGS__))
#define _CUTIL_UNEQUAL_MUTUALLY_19(a1, ...)	CUTIL_EXPAND(CUTIL_UNEQUAL_ALL(a1, __VA_ARGS__) && _CUTIL_UNEQUAL_MUTUALLY_18(__VA_ARGS__))
#define _CUTIL_UNEQUAL_MUTUALLY_20(a1, ...)	CUTIL_EXPAND(CUTIL_UNEQUAL_ALL(a1, __VA_ARGS__) && _CUTIL_UNEQUAL_MUTUALLY_19(__VA_ARGS__))
#define _CUTIL_UNEQUAL_MUTUALLY_21(a1, ...)	CUTIL_EXPAND(CUTIL_UNEQUAL_ALL(a1, __VA_ARGS__) && _CUTIL_UNEQUAL_MUTUALLY_20(__VA_ARGS__))
#define _CUTIL_UNEQUAL_MUTUALLY_22(a1, ...)	CUTIL_EXPAND(CUTIL_UNEQUAL_ALL(a1, __VA_ARGS__) && _CUTIL_UNEQUAL_MUTUALLY_21(__VA_ARGS__))
#define _CUTIL_UNEQUAL_MUTUALLY_23(a1, ...)	CUTIL_EXPAND(CUTIL_UNEQUAL_ALL(a1, __VA_ARGS__) && _CUTIL_UNEQUAL_MUTUALLY_22(__VA_ARGS__))
#define _CUTIL_UNEQUAL_MUTUALLY_24(a1, ...)	CUTIL_EXPAND(CUTIL_UNEQUAL_ALL(a1, __VA_ARGS__) && _CUTIL_UNEQUAL_MUTUALLY_23(__VA_ARGS__))
#define _CUTIL_UNEQUAL_MUTUALLY_25(a1, ...)	CUTIL_EXPAND(CUTIL_UNEQUAL_ALL(a1, __VA_ARGS__) && _CUTIL_UNEQUAL_MUTUALLY_24(__VA_ARGS__)) // recurse upwards
/* Instruction:
	int var = 10;
	if(CUTIL_EQUAL_ANY(var, 5, 10)){
		// equivalent to `if(var == 5 || var == 10)`
		// equivalent to `if(!CUTIL_UNEQUAL_ALL(var, 5, 10))`
	}
	if(CUTIL_EQUAL_ANY(var, 2, 4, 6, 8, 10)){
		// equivalent to `if(var == 2 || var == 4 || var == 6 || var == 8 || var == 10)`
		// equivalent to `if(!CUTIL_UNEQUAL_ALL(var, 2, 4, 6, 8, 10))`
	}
	if(CUTIL_EQUAL_ALL(var, 2, 4, 6, 8, 10)){
		// equivalent to `if(var == 2 && var == 4 && var == 6 && var == 8 && var == 10)`
		// equivalent to `if(CUTIL_EQUAL_MUTUALLY(var, 2, 4, 6, 8, 10))`
		// equivalent to `if(!CUTIL_UNEQUAL_ANY(var, 2, 4, 6, 8, 10))`
	}
	bool anyEquals = cutil::equalAny(var, 2, 4, 6, 8, 10); // C++
	bool allEquals = cutil::equalAll(var, 2, 4, 6, 8, 10); // C++
	
	//* WARNING: you can't compare some return value of functions like `getchar()`
	// if you use `if(CUTIL_EQUAL_ANY(getchar(), 'a', 'b'))`
	// it will expand as `if(getchar() == 'a' || getchar() == 'b')`
	
	//*-------------------------------------------
	if(CUTIL_UNEQUAL_ALL(var, 5, 10)){
		// equivalent to `if(var != 5 && var != 10)`
		// equivalent to `if(! CUTIL_EQUAL_ANY(var, 5, 10))`
	}
	if(CUTIL_UNEQUAL_ALL(var, 2, 4, 6, 8, 10)){
		// equivalent to `if(var != 2 && var != 4 && var != 6 && var != 8 && var != 10)`
		// equivalent to `if(! CUTIL_EQUAL_ANY(var, 2, 4, 6, 8, 10))`
	}
	if(CUTIL_UNEQUAL_ANY(var, 2, 4, 6, 8, 10)){
		// equivalent to `if(var != 2 || var != 4 || var != 6 || var != 8 || var != 10)`
		// equivalent to `if(! CUTIL_EQUAL_ALL(var, 2, 4, 6, 8, 10))`
	}
	bool allUnequals = cutil::unequalAll(var, 2, 4, 6, 8, 10); // C++
	bool anyUnequals = cutil::unequalAny(var, 2, 4, 6, 8, 10); // C++
	
	//* WARNING: you can't compare some return value of functions like `getchar()`
	// if you use `if(CUTIL_UNEQUAL_ALL(getchar(), 'a', 'b'))`
	// it will expand as `if(getchar() != 'a' && getchar() != 'b')`
	
	//*----------------------------------------------
	if(CUTIL_UNEQUAL_MUTUALLY(a1, a2, a3, a4)){ // is `a1`, `a2`, `a3`, `a4` mutually different?
		// (  ((a1) != (a2) && (a1) != (a3) && (a1) != (a4))
		// && ((a2) != (a3) && (a2) != (a4))
		// && ((a3) != (a4))   )
	}
	
	if(CUTIL_UNEQUAL_MUTUALLY(a1, a2, a3, a4, a5)){
		// (  ((a1) != (a2) && (a1) != (a3) && (a1) != (a4) && (a1) != (a5))
		// && ((a2) != (a3) && (a2) != (a4) && (a2) != (a5))
		// && ((a3) != (a4) && (a3) != (a5))
		// && ((a4) != (a5))   )
	}
	
	if(CUTIL_EQUAL_MUTUALLY(a1, a2, a3, a4, a5)){
		// ((a1) == (a2) && (a1) == (a3) && (a1) == (a4) && (a1) == (a5))
		// equivalent to `if(CUTIL_EQUAL_ALL(a1, a2, a3, a4, a5))`
	}
	
	bool isMutuallyDifferent = cutil::unequalMutually(a1, a2, a3, a4, a5); // C++
	bool isMutuallyEqual     = cutil::equalMutually(a1, a2, a3, a4, a5);   // C++
*/


//======================== Repeat And Range Statements =========================

//* call a single-argument function/macro for each parameter, simillar to `BOOST_PP_SEQ_FOR_EACH`, up to 25 iterations
#define CUTIL_SEQ_FOREACH(_action, ...)				do {CUTIL_EXPAND(CUTIL_OVERLOAD_AMOUNT(_CUTIL_SEQ_FOREACH_, __VA_ARGS__)(_action, __VA_ARGS__))} while(0)
	// The following macro definitions are private, DO NOT call them EXTERNALLY.
#define _CUTIL_SEQ_FOREACH_1(_action, _1)			_action(_1);
#define _CUTIL_SEQ_FOREACH_2(_action, _1, _2)		_action(_1); _CUTIL_SEQ_FOREACH_1(_action, _2)
#define _CUTIL_SEQ_FOREACH_3(_action, _1, ...)		_action(_1); CUTIL_EXPAND(_CUTIL_SEQ_FOREACH_2(_action, __VA_ARGS__))
#define _CUTIL_SEQ_FOREACH_4(_action, _1, ...)		_action(_1); CUTIL_EXPAND(_CUTIL_SEQ_FOREACH_3(_action, __VA_ARGS__))
#define _CUTIL_SEQ_FOREACH_5(_action, _1, ...)		_action(_1); CUTIL_EXPAND(_CUTIL_SEQ_FOREACH_4(_action, __VA_ARGS__))
#define _CUTIL_SEQ_FOREACH_6(_action, _1, ...)		_action(_1); CUTIL_EXPAND(_CUTIL_SEQ_FOREACH_5(_action, __VA_ARGS__))
#define _CUTIL_SEQ_FOREACH_7(_action, _1, ...)		_action(_1); CUTIL_EXPAND(_CUTIL_SEQ_FOREACH_6(_action, __VA_ARGS__))
#define _CUTIL_SEQ_FOREACH_8(_action, _1, ...)		_action(_1); CUTIL_EXPAND(_CUTIL_SEQ_FOREACH_7(_action, __VA_ARGS__))
#define _CUTIL_SEQ_FOREACH_9(_action, _1, ...)		_action(_1); CUTIL_EXPAND(_CUTIL_SEQ_FOREACH_8(_action, __VA_ARGS__))
#define _CUTIL_SEQ_FOREACH_10(_action, _1, ...)		_action(_1); CUTIL_EXPAND(_CUTIL_SEQ_FOREACH_9(_action, __VA_ARGS__))
#define _CUTIL_SEQ_FOREACH_11(_action, _1, ...)		_action(_1); CUTIL_EXPAND(_CUTIL_SEQ_FOREACH_10(_action, __VA_ARGS__))
#define _CUTIL_SEQ_FOREACH_12(_action, _1, ...)		_action(_1); CUTIL_EXPAND(_CUTIL_SEQ_FOREACH_11(_action, __VA_ARGS__))
#define _CUTIL_SEQ_FOREACH_13(_action, _1, ...)		_action(_1); CUTIL_EXPAND(_CUTIL_SEQ_FOREACH_12(_action, __VA_ARGS__))
#define _CUTIL_SEQ_FOREACH_14(_action, _1, ...)		_action(_1); CUTIL_EXPAND(_CUTIL_SEQ_FOREACH_13(_action, __VA_ARGS__))
#define _CUTIL_SEQ_FOREACH_15(_action, _1, ...)		_action(_1); CUTIL_EXPAND(_CUTIL_SEQ_FOREACH_14(_action, __VA_ARGS__))
#define _CUTIL_SEQ_FOREACH_16(_action, _1, ...)		_action(_1); CUTIL_EXPAND(_CUTIL_SEQ_FOREACH_15(_action, __VA_ARGS__))
#define _CUTIL_SEQ_FOREACH_17(_action, _1, ...)		_action(_1); CUTIL_EXPAND(_CUTIL_SEQ_FOREACH_16(_action, __VA_ARGS__))
#define _CUTIL_SEQ_FOREACH_18(_action, _1, ...)		_action(_1); CUTIL_EXPAND(_CUTIL_SEQ_FOREACH_17(_action, __VA_ARGS__))
#define _CUTIL_SEQ_FOREACH_19(_action, _1, ...)		_action(_1); CUTIL_EXPAND(_CUTIL_SEQ_FOREACH_18(_action, __VA_ARGS__))
#define _CUTIL_SEQ_FOREACH_20(_action, _1, ...)		_action(_1); CUTIL_EXPAND(_CUTIL_SEQ_FOREACH_19(_action, __VA_ARGS__))
#define _CUTIL_SEQ_FOREACH_21(_action, _1, ...)		_action(_1); CUTIL_EXPAND(_CUTIL_SEQ_FOREACH_20(_action, __VA_ARGS__))
#define _CUTIL_SEQ_FOREACH_22(_action, _1, ...)		_action(_1); CUTIL_EXPAND(_CUTIL_SEQ_FOREACH_21(_action, __VA_ARGS__))
#define _CUTIL_SEQ_FOREACH_23(_action, _1, ...)		_action(_1); CUTIL_EXPAND(_CUTIL_SEQ_FOREACH_22(_action, __VA_ARGS__))
#define _CUTIL_SEQ_FOREACH_24(_action, _1, ...)		_action(_1); CUTIL_EXPAND(_CUTIL_SEQ_FOREACH_23(_action, __VA_ARGS__))
#define _CUTIL_SEQ_FOREACH_25(_action, _1, ...)		_action(_1); CUTIL_EXPAND(_CUTIL_SEQ_FOREACH_24(_action, __VA_ARGS__)) // recurse upwards
/* Instruction:
	#define TEST_PRINT(x)   fmt::println("{}", x) //* Must take exactly 1 argument
	
	CUTIL_SEQ_FOREACH(TEST_PRINT, 1, 2, 3, 4, 5, 6, 7);
	// -> {fmt::println("{}", 1); fmt::println("{}", 2); ...}
*/


//* repeat function or macro calling, similar to `BOOST_PP_REPEAT`, up to 25 loops
#define CUTIL_REPEAT(_count, _action, ...)		do {CUTIL_EXPAND(CUTIL_OVERLOAD_IDX(_CUTIL_REPEAT_, _count)(_action, __VA_ARGS__))} while(0)
	// The following macro definitions are private, DO NOT call them EXTERNALLY.
#define _CUTIL_REPEAT_1(_action, ...)			CUTIL_EXPAND(_action(__VA_ARGS__));
#define _CUTIL_REPEAT_2(_action, ...)			CUTIL_EXPAND(_action(__VA_ARGS__); _CUTIL_REPEAT_1(_action, __VA_ARGS__))
#define _CUTIL_REPEAT_3(_action, ...)			CUTIL_EXPAND(_action(__VA_ARGS__); _CUTIL_REPEAT_2(_action, __VA_ARGS__))
#define _CUTIL_REPEAT_4(_action, ...)			CUTIL_EXPAND(_action(__VA_ARGS__); _CUTIL_REPEAT_3(_action, __VA_ARGS__))
#define _CUTIL_REPEAT_5(_action, ...)			CUTIL_EXPAND(_action(__VA_ARGS__); _CUTIL_REPEAT_4(_action, __VA_ARGS__))
#define _CUTIL_REPEAT_6(_action, ...)			CUTIL_EXPAND(_action(__VA_ARGS__); _CUTIL_REPEAT_5(_action, __VA_ARGS__))
#define _CUTIL_REPEAT_7(_action, ...)			CUTIL_EXPAND(_action(__VA_ARGS__); _CUTIL_REPEAT_6(_action, __VA_ARGS__))
#define _CUTIL_REPEAT_8(_action, ...)			CUTIL_EXPAND(_action(__VA_ARGS__); _CUTIL_REPEAT_7(_action, __VA_ARGS__))
#define _CUTIL_REPEAT_9(_action, ...)			CUTIL_EXPAND(_action(__VA_ARGS__); _CUTIL_REPEAT_8(_action, __VA_ARGS__))
#define _CUTIL_REPEAT_10(_action, ...)			CUTIL_EXPAND(_action(__VA_ARGS__); _CUTIL_REPEAT_9(_action, __VA_ARGS__))
#define _CUTIL_REPEAT_11(_action, ...)			CUTIL_EXPAND(_action(__VA_ARGS__); _CUTIL_REPEAT_10(_action, __VA_ARGS__))
#define _CUTIL_REPEAT_12(_action, ...)			CUTIL_EXPAND(_action(__VA_ARGS__); _CUTIL_REPEAT_11(_action, __VA_ARGS__))
#define _CUTIL_REPEAT_13(_action, ...)			CUTIL_EXPAND(_action(__VA_ARGS__); _CUTIL_REPEAT_12(_action, __VA_ARGS__))
#define _CUTIL_REPEAT_14(_action, ...)			CUTIL_EXPAND(_action(__VA_ARGS__); _CUTIL_REPEAT_13(_action, __VA_ARGS__))
#define _CUTIL_REPEAT_15(_action, ...)			CUTIL_EXPAND(_action(__VA_ARGS__); _CUTIL_REPEAT_14(_action, __VA_ARGS__))
#define _CUTIL_REPEAT_16(_action, ...)			CUTIL_EXPAND(_action(__VA_ARGS__); _CUTIL_REPEAT_15(_action, __VA_ARGS__))
#define _CUTIL_REPEAT_17(_action, ...)			CUTIL_EXPAND(_action(__VA_ARGS__); _CUTIL_REPEAT_16(_action, __VA_ARGS__))
#define _CUTIL_REPEAT_18(_action, ...)			CUTIL_EXPAND(_action(__VA_ARGS__); _CUTIL_REPEAT_17(_action, __VA_ARGS__))
#define _CUTIL_REPEAT_19(_action, ...)			CUTIL_EXPAND(_action(__VA_ARGS__); _CUTIL_REPEAT_18(_action, __VA_ARGS__))
#define _CUTIL_REPEAT_20(_action, ...)			CUTIL_EXPAND(_action(__VA_ARGS__); _CUTIL_REPEAT_19(_action, __VA_ARGS__))
#define _CUTIL_REPEAT_21(_action, ...)			CUTIL_EXPAND(_action(__VA_ARGS__); _CUTIL_REPEAT_20(_action, __VA_ARGS__))
#define _CUTIL_REPEAT_22(_action, ...)			CUTIL_EXPAND(_action(__VA_ARGS__); _CUTIL_REPEAT_21(_action, __VA_ARGS__))
#define _CUTIL_REPEAT_23(_action, ...)			CUTIL_EXPAND(_action(__VA_ARGS__); _CUTIL_REPEAT_22(_action, __VA_ARGS__))
#define _CUTIL_REPEAT_24(_action, ...)			CUTIL_EXPAND(_action(__VA_ARGS__); _CUTIL_REPEAT_23(_action, __VA_ARGS__))
#define _CUTIL_REPEAT_25(_action, ...)			CUTIL_EXPAND(_action(__VA_ARGS__); _CUTIL_REPEAT_24(_action, __VA_ARGS__)) // recurse upwards
/* Instruction:
	#define TEST_PRINT(x)   	fmt::println("{}", x)
	#define TEST_1(x, y)   		fmt::println("{} {}", x, y)
	#define TEST_2(x, ...) 		printf("%d", x); CUTIL_SEQ_FOREACH(TEST_PRINT, __VA_ARGS__)
	
	CUTIL_REPEAT(3, TEST_1, 22, 44);			// repeat `fmt::println("{} {}", 22, 44)` for 3 times
	CUTIL_REPEAT(4, TEST_2, 2, 4, 6, 8, 10);	// repeat `printf("%d", 2);printf("%d", 4); ... printf("%d, 10")` for 4 times
*/


//* generate code like `int arg0, int arg1, int arg2`, similar to `BOOST_PP_ENUM`, up to 25 params
#define CUTIL_ENUM(_type, _name, _count)	CUTIL_OVERLOAD_IDX(_CUTIL_ENUM_, _count)(_name, _type)
	// The following macro definitions are private, DO NOT call them EXTERNALLY.
#define _CUTIL_ENUM_1(_type, _name)			_type _name##0
#define _CUTIL_ENUM_2(_type, _name)			_CUTIL_ENUM_1(_type, _name), _type _name##1
#define _CUTIL_ENUM_3(_type, _name)			_CUTIL_ENUM_2(_type, _name), _type _name##2
#define _CUTIL_ENUM_4(_type, _name)			_CUTIL_ENUM_3(_type, _name), _type _name##3
#define _CUTIL_ENUM_5(_type, _name)			_CUTIL_ENUM_4(_type, _name), _type _name##4
#define _CUTIL_ENUM_6(_type, _name)			_CUTIL_ENUM_5(_type, _name), _type _name##5
#define _CUTIL_ENUM_7(_type, _name)			_CUTIL_ENUM_6(_type, _name), _type _name##6
#define _CUTIL_ENUM_8(_type, _name)			_CUTIL_ENUM_7(_type, _name), _type _name##7
#define _CUTIL_ENUM_9(_type, _name)			_CUTIL_ENUM_8(_type, _name), _type _name##8
#define _CUTIL_ENUM_10(_type, _name)		_CUTIL_ENUM_9(_type, _name), _type _name##9
#define _CUTIL_ENUM_11(_type, _name)		_CUTIL_ENUM_10(_type, _name), _type _name##10
#define _CUTIL_ENUM_12(_type, _name)		_CUTIL_ENUM_11(_type, _name), _type _name##11
#define _CUTIL_ENUM_13(_type, _name)		_CUTIL_ENUM_12(_type, _name), _type _name##12
#define _CUTIL_ENUM_14(_type, _name)		_CUTIL_ENUM_13(_type, _name), _type _name##13
#define _CUTIL_ENUM_15(_type, _name)		_CUTIL_ENUM_14(_type, _name), _type _name##14
#define _CUTIL_ENUM_16(_type, _name)		_CUTIL_ENUM_15(_type, _name), _type _name##15
#define _CUTIL_ENUM_17(_type, _name)		_CUTIL_ENUM_16(_type, _name), _type _name##16
#define _CUTIL_ENUM_18(_type, _name)		_CUTIL_ENUM_17(_type, _name), _type _name##17
#define _CUTIL_ENUM_19(_type, _name)		_CUTIL_ENUM_18(_type, _name), _type _name##18
#define _CUTIL_ENUM_20(_type, _name)		_CUTIL_ENUM_19(_type, _name), _type _name##19
#define _CUTIL_ENUM_21(_type, _name)		_CUTIL_ENUM_20(_type, _name), _type _name##20
#define _CUTIL_ENUM_22(_type, _name)		_CUTIL_ENUM_21(_type, _name), _type _name##21
#define _CUTIL_ENUM_23(_type, _name)		_CUTIL_ENUM_22(_type, _name), _type _name##22
#define _CUTIL_ENUM_24(_type, _name)		_CUTIL_ENUM_23(_type, _name), _type _name##23
#define _CUTIL_ENUM_25(_type, _name)		_CUTIL_ENUM_24(_type, _name), _type _name##24  // recurse upwards
/* Instruction:
	void func(CUTIL_ENUM(int, var_, 3)){
		// equivalent to `void func(int var_0, int var_1, int var_2)`
	}
*/

//* similar to `CUTIL_ENUM`, but you can customize the suffix, up to 25 loops
#define CUTIL_SEQ_ENUM(_action, ...)			CUTIL_EXPAND(CUTIL_OVERLOAD_AMOUNT(_CUTIL_SEQ_ENUM_, __VA_ARGS__)(_action, __VA_ARGS__))
	// The following macro definitions are private, DO NOT call them EXTERNALLY.
#define _CUTIL_SEQ_ENUM_1(_action, _1)			_action(_1)
#define _CUTIL_SEQ_ENUM_2(_action, _1, _2)		_action(_1), _CUTIL_SEQ_ENUM_1(_action, _2)
#define _CUTIL_SEQ_ENUM_3(_action, _1, ...)		_action(_1), CUTIL_EXPAND(_CUTIL_SEQ_ENUM_2(_action, __VA_ARGS__))
#define _CUTIL_SEQ_ENUM_4(_action, _1, ...)		_action(_1), CUTIL_EXPAND(_CUTIL_SEQ_ENUM_3(_action, __VA_ARGS__))
#define _CUTIL_SEQ_ENUM_5(_action, _1, ...)		_action(_1), CUTIL_EXPAND(_CUTIL_SEQ_ENUM_4(_action, __VA_ARGS__))
#define _CUTIL_SEQ_ENUM_6(_action, _1, ...)		_action(_1), CUTIL_EXPAND(_CUTIL_SEQ_ENUM_5(_action, __VA_ARGS__))
#define _CUTIL_SEQ_ENUM_7(_action, _1, ...)		_action(_1), CUTIL_EXPAND(_CUTIL_SEQ_ENUM_6(_action, __VA_ARGS__))
#define _CUTIL_SEQ_ENUM_8(_action, _1, ...)		_action(_1), CUTIL_EXPAND(_CUTIL_SEQ_ENUM_7(_action, __VA_ARGS__))
#define _CUTIL_SEQ_ENUM_9(_action, _1, ...)		_action(_1), CUTIL_EXPAND(_CUTIL_SEQ_ENUM_8(_action, __VA_ARGS__))
#define _CUTIL_SEQ_ENUM_10(_action, _1, ...)	_action(_1), CUTIL_EXPAND(_CUTIL_SEQ_ENUM_9(_action, __VA_ARGS__))
#define _CUTIL_SEQ_ENUM_11(_action, _1, ...)	_action(_1), CUTIL_EXPAND(_CUTIL_SEQ_ENUM_10(_action, __VA_ARGS__))
#define _CUTIL_SEQ_ENUM_12(_action, _1, ...)	_action(_1), CUTIL_EXPAND(_CUTIL_SEQ_ENUM_11(_action, __VA_ARGS__))
#define _CUTIL_SEQ_ENUM_13(_action, _1, ...)	_action(_1), CUTIL_EXPAND(_CUTIL_SEQ_ENUM_12(_action, __VA_ARGS__))
#define _CUTIL_SEQ_ENUM_14(_action, _1, ...)	_action(_1), CUTIL_EXPAND(_CUTIL_SEQ_ENUM_13(_action, __VA_ARGS__))
#define _CUTIL_SEQ_ENUM_15(_action, _1, ...)	_action(_1), CUTIL_EXPAND(_CUTIL_SEQ_ENUM_14(_action, __VA_ARGS__))
#define _CUTIL_SEQ_ENUM_16(_action, _1, ...)	_action(_1), CUTIL_EXPAND(_CUTIL_SEQ_ENUM_15(_action, __VA_ARGS__))
#define _CUTIL_SEQ_ENUM_17(_action, _1, ...)	_action(_1), CUTIL_EXPAND(_CUTIL_SEQ_ENUM_16(_action, __VA_ARGS__))
#define _CUTIL_SEQ_ENUM_18(_action, _1, ...)	_action(_1), CUTIL_EXPAND(_CUTIL_SEQ_ENUM_17(_action, __VA_ARGS__))
#define _CUTIL_SEQ_ENUM_19(_action, _1, ...)	_action(_1), CUTIL_EXPAND(_CUTIL_SEQ_ENUM_18(_action, __VA_ARGS__))
#define _CUTIL_SEQ_ENUM_20(_action, _1, ...)	_action(_1), CUTIL_EXPAND(_CUTIL_SEQ_ENUM_19(_action, __VA_ARGS__))
#define _CUTIL_SEQ_ENUM_21(_action, _1, ...)	_action(_1), CUTIL_EXPAND(_CUTIL_SEQ_ENUM_20(_action, __VA_ARGS__))
#define _CUTIL_SEQ_ENUM_22(_action, _1, ...)	_action(_1), CUTIL_EXPAND(_CUTIL_SEQ_ENUM_21(_action, __VA_ARGS__))
#define _CUTIL_SEQ_ENUM_23(_action, _1, ...)	_action(_1), CUTIL_EXPAND(_CUTIL_SEQ_ENUM_22(_action, __VA_ARGS__))
#define _CUTIL_SEQ_ENUM_24(_action, _1, ...)	_action(_1), CUTIL_EXPAND(_CUTIL_SEQ_ENUM_23(_action, __VA_ARGS__))
#define _CUTIL_SEQ_ENUM_25(_action, _1, ...)	_action(_1), CUTIL_EXPAND(_CUTIL_SEQ_ENUM_24(_action, __VA_ARGS__)) // recurse upwards
/* Instruction:
	#define TEST(_x)    test_##_x 		//* Must take exactly 1 argument
	#define TEST2(_x)   test_##_x = 1
	
	int CUTIL_SEQ_ENUM(TEST2, a, b, c, d);
	// -> int test_a = 1, test_b = 1, test_c = 1, test_d = 1;
	
	printf("%d %d %d %d", CUTIL_SEQ_ENUM(TEST, a, b, c, d));
	printf("%d %d %d %d", test_a, test_b, test_c, test_d);	// equivalent to above
*/

//* for loop in range [0, _end) or [_first, _end)
#define CUTIL_FOR_TYPE(_type, ...)		 CUTIL_EXPAND(CUTIL_OVERLOAD_IDX(_CUTIL_FOR_TYPE_, CUTIL_VA_CNT(__VA_ARGS__))(_type, __VA_ARGS__))
#define _CUTIL_FOR_TYPE_1(_type, _var, _end)		 for(_type _var = 0;        (_var) <= (_end); (_var)++)
#define _CUTIL_FOR_TYPE_2(_type, _var, _first, _end) for(_type _var = (_first); (_var) <= (_end); (_var)++)

#define CUTIL_FOR(_var, ...)			 CUTIL_EXPAND(CUTIL_OVERLOAD_IDX(_CUTIL_FOR_, CUTIL_VA_CNT(__VA_ARGS__))(_var, __VA_ARGS__))
#define _CUTIL_FOR_1(_var, _end)		 _CUTIL_FOR_TYPE_1(CUTIL_TYPEOF(_end), _var, _end)
#define _CUTIL_FOR_2(_var, _first, _end) _CUTIL_FOR_TYPE_2(CUTIL_TYPEOF(_end), _var, _first, _end)
/*
	CUTIL_FOR_TYPE(int, i, 5)	 {} // `for(int i = 0; i < 5; i++)`; i <- [0..4];
	CUTIL_FOR_TYPE(int, i, 2, 4) {}	// `for(int i = 2; i < 4; i++)`; i <- [2..3];
	
	// for C23, GNU C, C++; type of `_var` is deduced from `_end`
	CUTIL_FOR(i, 5)				 {}	// `for(int i = 0; i < 5; i++)`; i <- [0..4];
	CUTIL_FOR(i, 0, 10)			 {}	// `for(int vi = 2; i < 4; i++)`; i <- [2..3];
*/





//======================= Bit Operations ============================
//* bit calculating macros, not recommended in C++ (std::bitset<>)
#define CUTIL_BIT_GET_MASK(_NUM, _BIT_MASK)		((_NUM) &   (_BIT_MASK)        )
#define CUTIL_BIT_SET_MASK(_NUM, _BIT_MASK)		((_NUM) |=  (_BIT_MASK), (_NUM))
#define CUTIL_BIT_CLEAR_MASK(_NUM, _BIT_MASK)	((_NUM) &= ~(_BIT_MASK), (_NUM))
#define CUTIL_BIT_FLIP_MASK(_NUM, _BIT_MASK)	((_NUM) ^=  (_BIT_MASK), (_NUM))
#define CUTIL_BIT_CHECK_MASK(_NUM, _BIT_MASK)	(CUTIL_BIT_GET_MASK(_NUM, _BIT_MASK) ? 1 : 0)

#define CUTIL_BIT_GET_IDX(_NUM, _BIT_IDX)		CUTIL_BIT_GET_MASK(_NUM, 	(1u << (_BIT_IDX)))	// if bit of index _BIT_IDX is 1, returns (1<<_BIT_IDX), NOT 1
#define CUTIL_BIT_SET_IDX(_NUM, _BIT_IDX)		CUTIL_BIT_SET_MASK(_NUM, 	(1u << (_BIT_IDX)))	// must use them in separate lines, returns nothing
#define CUTIL_BIT_CLEAR_IDX(_NUM, _BIT_IDX)		CUTIL_BIT_CLEAR_MASK(_NUM, 	(1u << (_BIT_IDX)))
#define CUTIL_BIT_FLIP_IDX(_NUM, _BIT_IDX)		CUTIL_BIT_FLIP_MASK(_NUM, (1u << (_BIT_IDX)))
#define CUTIL_BIT_CHECK_IDX(_NUM, _BIT_IDX)		(CUTIL_BIT_GET_IDX(_NUM, _BIT_IDX) ? 1 : 0) 	// returns 1 if bit of _BIT_IDX is 1, != CUTIL_BIT_GET_IDX()

// rotate bits, use them in a separate line
#define CUTIL_BIT_ROTATE_LEFT_SIZE(_BIT_SIZE, _BIT, _STEP)	((_BIT) = (((_BIT) << (_STEP)) | ((_BIT) >> ((_BIT_SIZE) - (_STEP)))), (_BIT))
#define CUTIL_BIT_ROTATE_RIGHT_SIZE(_BIT_SIZE, _BIT, _STEP)	((_BIT) = (((_BIT) >> (_STEP)) | ((_BIT) << ((_BIT_SIZE) - (_STEP)))), (_BIT))

#define CUTIL_BIT_ROTATE_LEFT(_BIT, _STEP)		CUTIL_BIT_ROTATE_LEFT_SIZE(8u * sizeof(_BIT), _BIT, _STEP)
#define CUTIL_BIT_ROTATE_RIGHT(_BIT, _STEP)		CUTIL_BIT_ROTATE_RIGHT_SIZE(8u * sizeof(_BIT), _BIT, _STEP)
/*
	uint16_t num {0};
	
	// operate bit by index, starts at 0. use them in a seperate line, and returns nothing
	CUTIL_BIT_SET_IDX(num, 0);    // equals to {num |=  (1u << 0));}
	CUTIL_BIT_CLEAR_IDX(num, 2);  // equals to {num &= ~(1u << 2));}
	CUTIL_BIT_FLIP_IDX(num, 3);   // equals to {num ^=  (1u << 3));}
	if(CUTIL_BIT_GET_IDX(num, 0) != 0x0000){ // reading bit, if bit is 1, returns `(1<<BIT_IDX)`, NOT 1
		printf("%x\n", num);
	}
	if(CUTIL_BIT_CHECK_IDX(num, 0) == true){ // reading bit, if bit is 1, returns `1`, `!= CUTIL_BIT_GET_IDX()`
		printf("%x\n", num);
	}

	// operate bit by mask
	CUTIL_BIT_SET_MASK(num, 0x2B00);    // equals to {num |=  0x2B00;}
	CUTIL_BIT_CLEAR_MASK(num, 0x2B00);  // equals to {num &= ~0x2B00;}
	CUTIL_BIT_FLIP_MASK(num, 0x1100);   // equals to {num ^=  0x1100;}
	if(CUTIL_BIT_GET_MASK(num, 0x0022) != 0x0000){ // returns (num & 0x0022)
		printf("%x\n", num);
	}
	if(CUTIL_BIT_CHECK_MASK(num, 0x0022) == true){ // returns (bool)(num & 0x0022)
		printf("%x\n", num);
	}

	// rotate bits. use them in a seperate line, and returns nothing
	uint16_t var{0x1234};           // 0b0001'0010'0011'0100
	CUTIL_BIT_ROTATE_LEFT(var, 1);  -> 0b0010'0100'0110'1000
	CUTIL_BIT_ROTATE_RIGHT(var, 1); -> 0b0001'0010'0011'0100
*/

//* assign or cast bitwise
//  use `std::bit_cast<T>()` in C++20
#define CUTIL_BITWISE_ASSIGN(_OUT_TYPE, _OUT_PTR, _IN_PTR)	memcpy(&_OUT_PTR, &_IN_PTR, sizeof(_OUT_TYPE))
#define CUTIL_BITWISE_MEMCPY(_OUT_TYPE, _OUT_PTR, _IN_PTR)	CUTIL_BITWISE_ASSIGN(_OUT_TYPE, _OUT_PTR, _IN_PTR) // alias
// reinterpret_cast
#define CUTIL_BITWISE_CAST_UNSAFE(_OUT_TYPE, _IN_PTR)		(* (volatile _OUT_TYPE*) (volatile void*) _IN_PTR)
/*
	uint32_t i = 0x12345678;
	float f;
	CUTIL_BITWISE_MEMCPY(float, &f, &i); // assign `i` to `f` bitwise
	f = CUTIL_BITWISE_CAST_UNSAFE(float, &f) // UB, unrecommended, similar as `reinterpret_cast<float&>(f)`
*/




//======================= Numeric and Math Operations =========================

//* get the bigger or smaller item between two numeric variables
//  use std::max(), std::min() function in C++
#define CUTIL_MAX(_VAR1, _VAR2) 			(((_VAR1) > (_VAR2)) ? (_VAR1) : (_VAR2))
#define CUTIL_MIN(_VAR1, _VAR2)				(((_VAR1) < (_VAR2)) ? (_VAR1) : (_VAR2))
/*
	uint32_t a = 1, b = 2; // type of `a` and `b` must be strictly equal.
	
	int max_ab = CUTIL_MAX(a, b); // bigger number between a and b
	int min_ab = CUTIL_MIN(a, b); // smaller number between a and b
	
	max_ab = std::max(a, b); // equivalent to above in C++
*/


//* get abs of int/float/double (not recommended in C++, pls use abs() function)
// equivalent to abs(), fabs(), fabsf() function in C
#define CUTIL_ABS(_VAR)						(((_VAR) >= 0) ? (_VAR) : (-1)*(_VAR) )


#if (CONSOLE_UTIL_DO_NOT_USE_SHORTER_ALIAS == 0) //* shorter aliases
	#define CU_MAX(_VAR1, _VAR2) 			CUTIL_MAX(_VAR1, _VAR2)
	#define CU_MIN(_VAR1, _VAR2) 			CUTIL_MIN(_VAR1, _VAR2)
	#define CU_ABS(_VAR)					CUTIL_ABS(_VAR)
#endif // CONSOLE_UTIL_DO_NOT_USE_SHORTER_ALIAS

//*	高效地计算一个值 val 除以一个以 2 为幂的数 mod_by 的余数
#define CUTIL_MOD_BY_POWER_OF_2(_var, _mod_2)	 ((size_t)(_var) & (dword)((_mod_2)-1))


//* limit the numeric variable to the range [_MIN, _MAX]
	// recommended to use `std::clamp` after C++17.
#define CUTIL_LIMIT(_VAR, _MIN, _MAX)		(((_VAR) < (_MIN) ? (_VAR) = (_MIN) : (_VAR)), ((_VAR) > (_MAX) ? (_VAR) = (_MAX) : (_VAR)), (_VAR))
#define CUTIL_CLAMP(_VAR, _MIN, _MAX)		((_VAR) < (_MIN) ? (_MIN) : ((_VAR) > (_MAX) ? (_MAX) : (_VAR)))

//* get if a numeric variable is within the range [_MIN, _MAX] or (_MIN, _MAX)
#define CUTIL_IN_RANGE(_VAR, _MIN, _MAX)		((((_VAR) >= (_MIN)) && ((_VAR) <= (_MAX))) ? 1 : 0) // inclusive range
#define CUTIL_IN_OPEN_RANGE(_VAR, _MIN, _MAX)	((((_VAR) > (_MIN)) && ((_VAR) < (_MAX))) ? 1 : 0)   // open range
/*
	int a = 35, b = 26, c = 19, d = 35;
	CUTIL_LIMIT(a, 20, 30);		// a: 35 -> 30
	CUTIL_LIMIT(b, 20, 30);		// b: 26
	CUTIL_LIMIT(c, 20, 30);		// c: 19 -> 20

	d = CUTIL_CLAMP(d, 20, 30);	// d: 35 -> 30, only returns value
	d = std::clamp(d, 20, 30);  // C++17, equivalent to above

	printf("%d %d %d\n", a, b, c);
	// output: 30 26 20

	printf("%d %d", CUTIL_IN_RANGE(a, 20, 40), CUTIL_IN_OPEN_RANGE(c, 20, 30));
	// output: 1 0
*/


//* increase or decrease the value of variable within the range [_min, _max]
#define CUTIL_INCREASE_UNDER_LIMIT(_var, _max, _inc)	((_var) < (_max) ? (_var) += (_inc) : (_var))
#define CUTIL_DECREASE_ABOVE_LIMIT(_var, _min, _inc)	((_var) > (_min) ? (_var) -= (_inc) : (_var))

//* increase or decrease the value, and prevent overflowing, only for GNU C, C23, C++11
#define CUTIL_INCREASE_PREVENT_OVERFLOWING(_var, _inc)	((_var) = (((CUTIL_TYPEOF(_var))((_var) + (_inc)) > (_var))) ? (CUTIL_TYPEOF(_var))((_var) + (_inc)) : (_var))
#define CUTIL_DECREASE_PREVENT_OVERFLOWING(_var, _inc)	((_var) = (((CUTIL_TYPEOF(_var))((_var) - (_inc)) < (_var))) ? (CUTIL_TYPEOF(_var))((_var) - (_inc)) : (_var))

//* increase or decrease the value of variable, and rolling within the range [_min, _max]
#define CUTIL_INCREASE_ROLLING(_var, _min, _max, _inc)	((_var) < (_max) ? (_var) += (_inc) : (_var) = (_min))
#define CUTIL_DECREASE_ROLLING(_var, _min, _max, _inc)	((_var) > (_min) ? (_var) -= (_inc) : (_var) = (_max))
/*
	int num = 0;
	for(int i = 0; i < 50; i++){
		printf("%d ", CUTIL_INCREASE_UNDER_LIMIT(num, 5, 1));     // step:1, result: 1 2 3 4 5 5 5 5 5 5 5 5
	}
	for(int i = 0; i < 50; i++){
		printf("%d ", CUTIL_DECREASE_ABOVE_LIMIT(num, 0, 1));     // step:1, result: 5 4 3 2 1 0 0 0 0 0 0 0
	}

	for(int i = 0; i < 50; i++){
		printf("%d ", CUTIL_INCREASE_ROLLING(num, 0, 5, 1));   // step:1, result: 1 2 3 4 5 0 1 2 3 4 5 0
	}
	for(int i = 0; i < 50; i++){
		printf("%d ", CUTIL_DECREASE_ROLLING(num, 0, 5, 1));   // step:1, result: 5 4 3 2 1 0 5 4 3 2 1 0
	}

	int8_t num = -125;
	for(int i = 0; i < 30; i++){
		CUTIL_DECREASE_PREVENT_OVERFLOWING(num, 1u);
		printf("%d ", num); // prevent overflowing: -126 -127 -128 -128 -128 -128
	}
	num = 124;
	for(int i = 0; i < 30; i++){
		CUTIL_INCREASE_PREVENT_OVERFLOWING(num, 1u);
		printf("%d ", num); // prevent overflowing: 125 126 127 127 127 127
	}
*/

//* determine if two float/double numbers are regarded as equal (within epsilon)
// 	<float.h> must be included
#define CUTIL_EQUAL(_F1, _F2, _EPSILON)		(( CUTIL_ABS((_F1) - (_F2)) < CUTIL_ABS((_EPSILON)) ) ? 1 : 0) // diff within (-epsilon, +epsilon)
#define CUTIL_EQUAL_F(_F1, _F2)				CUTIL_EQUAL(_F1, _F2, FLT_EPSILON)	// float, using epsilon values defined in <float.h>
#define CUTIL_EQUAL_D(_F1, _F2)				CUTIL_EQUAL(_F1, _F2, DBL_EPSILON)	// double
#define CUTIL_EQUAL_LD(_F1, _F2)			CUTIL_EQUAL(_F1, _F2, LDBL_EPSILON) // long double

#if (CONSOLE_UTIL_DO_NOT_USE_SHORTER_ALIAS == 0) //* shorter aliases
	#define CU_EQU(_F1, _F2, _EPSILON)		CUTIL_EQUAL(_F1, _F2, _EPSILON)
	#define CU_EQU_F(_F1, _F2)				CUTIL_EQUAL_F(_F1, _F2)
	#define CU_EQU_D(_F1, _F2)				CUTIL_EQUAL_D(_F1, _F2)
	#define CU_EQU_LD(_F1, _F2)				CUTIL_EQUAL_LD(_F1, _F2)
#endif // CONSOLE_UTIL_DO_NOT_USE_SHORTER_ALIAS
/*
	// include <float.h> first
	float a = -1.00000f, b = -0.99999f; // they can regarded as equal
	double c = 1.000000000, d = 1.0000000001;

	bool isEqual1 = CUTIL_EQUAL_F(a, b); // fabs(a-b) within (-epsilon, +epsilon), epsilon == FLT_EPSILON in <float.h>
	bool isEqual2 = CUTIL_EQUAL_D(c, d); // epsilon == DBL_EPSILON in <float.h>
	bool isEqual3 = CUTIL_EQUAL(c, d, 0.0001); // custom epsilon value
	
	bool isEqual4 = cutil::math::fequal(a, b); // (abs(a - b) <= std::numeric_limits<decltype(a)>::epsilon())
	bool isEqual5 = cutil::math::fequal(c, d, 0.0001); // equivelent
*/

//* get power of an integer.
// example: int ret = CUTIL_INTPOW(2, 3); 	// 2^3 = 8; generates `(2 * 2 * 2)`; arg `exp` must be an constexpr.
//			ret = CUTIL_INTPOW(ret, 2); 	// 8^2 = 64; generates `(ret * ret)`
//			ret = CUTIL_INTPOW_2(ret);		// 64^2 = 4096; equivalent to `CUTIL_INTPOW(ret, 2)`
//			//ret = CUTIL_INTPOW(ret, ret);	// ERROR! 2nd param `exp` must be a constexpr integer!
// notice:  std::pow(base, exp) in `<cmath>` is for float/double, not for integer.
// warning: the second parameter `exp` must be a constexpr integer value, not a variable.
#define CUTIL_INTPOW(_base, exp)	(CUTIL_OVERLOAD_IDX(CUTIL_INTPOW_, exp)(_base))
#define CUTIL_INTPOW_1(_base) 		(_base)
#define CUTIL_INTPOW_2(_base) 		((_base) * (_base))
#define CUTIL_INTPOW_3(_base) 		(CUTIL_INTPOW_2(_base) * (_base))
#define CUTIL_INTPOW_4(_base) 		(CUTIL_INTPOW_3(_base) * (_base))
#define CUTIL_INTPOW_5(_base) 		(CUTIL_INTPOW_4(_base) * (_base))
#define CUTIL_INTPOW_6(_base) 		(CUTIL_INTPOW_5(_base) * (_base))
#define CUTIL_INTPOW_7(_base) 		(CUTIL_INTPOW_6(_base) * (_base))
#define CUTIL_INTPOW_8(_base) 		(CUTIL_INTPOW_7(_base) * (_base))
#define CUTIL_INTPOW_9(_base) 		(CUTIL_INTPOW_8(_base) * (_base))
#define CUTIL_INTPOW_10(_base) 		(CUTIL_INTPOW_9(_base) * (_base))
#define CUTIL_INTPOW_11(_base) 		(CUTIL_INTPOW_10(_base) * (_base))
#define CUTIL_INTPOW_12(_base) 		(CUTIL_INTPOW_11(_base) * (_base))
#define CUTIL_INTPOW_13(_base) 		(CUTIL_INTPOW_12(_base) * (_base))
#define CUTIL_INTPOW_14(_base) 		(CUTIL_INTPOW_13(_base) * (_base))
#define CUTIL_INTPOW_15(_base) 		(CUTIL_INTPOW_14(_base) * (_base))
#define CUTIL_INTPOW_16(_base) 		(CUTIL_INTPOW_15(_base) * (_base))
#define CUTIL_INTPOW_17(_base) 		(CUTIL_INTPOW_16(_base) * (_base))
#define CUTIL_INTPOW_18(_base) 		(CUTIL_INTPOW_17(_base) * (_base))
#define CUTIL_INTPOW_19(_base) 		(CUTIL_INTPOW_18(_base) * (_base))
#define CUTIL_INTPOW_20(_base) 		(CUTIL_INTPOW_19(_base) * (_base))
#define CUTIL_INTPOW_21(_base) 		(CUTIL_INTPOW_20(_base) * (_base))
#define CUTIL_INTPOW_22(_base) 		(CUTIL_INTPOW_21(_base) * (_base))
#define CUTIL_INTPOW_23(_base) 		(CUTIL_INTPOW_22(_base) * (_base))
#define CUTIL_INTPOW_24(_base) 		(CUTIL_INTPOW_23(_base) * (_base))
#define CUTIL_INTPOW_25(_base) 		(CUTIL_INTPOW_24(_base) * (_base))


//* C char conversion and assertion
// this feature contains in `<ctype.h>`, so it's just an alternative.
#define CUTIL_CHAR_IS_UPPER(_ch)		((_ch) >= 'A' && (_ch) <= 'Z')
#define CUTIL_CHAR_IS_LOWER(_ch)		((_ch) >= 'a' && (_ch) <= 'z')
#define CUTIL_CHAR_IS_ALPHABET(_ch)		(CUTIL_CHAR_IS_UPPER(_ch) || CUTIL_CHAR_IS_LOWER(_ch))
#define CUTIL_CHAR_GET_UPPER(_ch)		((char)(CUTIL_CHAR_IS_LOWER(_ch) ? ((_ch) - 0x20) : (_ch)))
#define CUTIL_CHAR_GET_LOWER(_ch)		((char)(CUTIL_CHAR_IS_UPPER(_ch) ? ((_ch) + 0x20) : (_ch)))
#define CUTIL_CHAR_SET_UPPER(_ch)		((_ch) = CUTIL_CHAR_GET_UPPER(_ch), (_ch))
#define CUTIL_CHAR_SET_LOWER(_ch)		((_ch) = CUTIL_CHAR_GET_LOWER(_ch), (_ch))

#define CUTIL_CHAR_IS_NUMBER(_ch)		((_ch) >= '0' && (_ch) <= '9')
// #define CUTIL_CHAR_IS_DIGIT(_ch)		CUTIL_CHAR_IS_DEC(_ch)
#define CUTIL_CHAR_IS_DEC(_ch)			CUTIL_CHAR_IS_NUMBER(_ch)
#define CUTIL_CHAR_IS_HEX(_ch)			(CUTIL_CHAR_IS_NUMBER(_ch) || ((_ch) >= 'A' && (_ch) <= 'F') || ((_ch) >= 'a' && (_ch) <= 'f'))

#define CUTIL_CHAR_IS_ALPHANUMERIC(_ch)	(CUTIL_CHAR_IS_ALPHABET(_ch) || CUTIL_CHAR_IS_NUMBER(_ch))
#define CUTIL_CHAR_IS_PUNCT(_ch)		(((_ch) >= '!' && (_ch) <= '/') || ((_ch) >= ':' && (_ch) <= '@') || ((_ch) >= '[' && (_ch) <= '`') || ((_ch) >= '{' && (_ch) <= '~'))
#define CUTIL_CHAR_IS_CONTROL(_ch)		((_ch) <= 0x1F && (_ch) >= 0x00)
#define CUTIL_CHAR_IS_ASCII(_ch)		((_ch) >= 0x01 && (_ch) <= 0x7E)
#define CUTIL_CHAR_IS_SYMBOL(_ch)		((_ch) >= 0x20 && (_ch) <= 0x7E)
/*
	#define TEST(_x)    fmt::println("{}: {}", _x, CUTIL_CHAR_IS_UPPER(_x))
	CUTIL_SEQ_FOREACH(TEST, '`', 'a', 'b', 'z', '{', '0', '9', '@', 'A', 'B', 'Z', '[');
	// fmt::println("{}: {}", '`', CUTIL_CHAR_IS_UPPER('`'));
	// fmt::println("{}: {}", '`', CUTIL_CHAR_IS_UPPER('`'));
	//  ...
	// fmt::println("{}: {}", '[', CUTIL_CHAR_IS_UPPER('['));

*/


//======================= Math Constants =========================

//* Mathematical Constants:
#define CUTIL_E				2.71828182845904523536	// e
#define CUTIL_LOG2E			1.44269504088896340736	// log2(e)
#define CUTIL_LOG10E		0.43429448190325182765	// log10(e)
#define CUTIL_LN2			0.69314718055994530942	// ln(2)
#define CUTIL_LN10			2.30258509299404568402	// ln(10)

#define CUTIL_PI			3.14159265358979323846	// pi
#define CUTIL_2_PI			6.28318530717958647692	// 2*pi
#define CUTIL_3_PI			9.42477796076937971538	// 3*pi
#define CUTIL_PI_2			1.57079632679489661923	// pi/2
#define CUTIL_PI_3			1.04719755119659774615	// pi/3
#define CUTIL_PI_4			0.78539816339744830962	// pi/4
#define CUTIL_INV_PI		0.31830988618379067154	// 1/pi
#define CUTIL_INV_SQRT_PI	0.56418958354775628694	// 1/sqrt(pi)
#define CUTIL_2_INV_PI		0.63661977236758134308	// 2/pi
#define CUTIL_2_SQRT_PI		1.12837916709551257390	// 2/sqrt(pi)

#define CUTIL_SQRT_2		1.41421356237309504880	// sqrt(2)
#define CUTIL_INV_SQRT_2	0.70710678118654752440	// 1/sqrt(2)
#define CUTIL_SQRT_3		1.73205080756887729353	// sqrt(3)
#define CUTIL_INV_SQRT_3	0.57735026918962576451	// 1/sqrt(3)

#define CUTIL_PHI			1.61803398874989484820	// (1 + sqrt(5)) / 2, golden ratio
#define CUTIL_INV_PHI		0.61803398874989484820	// 2 / (1 + sqrt(5)), inversed golden ratio

#define CUTIL_EGAMMA		0.57721566490153286060	// Euler-Mascheroni constant

// float versions of mathematical constants:
#define CUTIL_E_F			2.71828182845904523536f	// e
#define CUTIL_LOG2E_F		1.44269504088896340736f	// log2(e)
#define CUTIL_LOG10E_F		0.43429448190325182765f	// log10(e)
#define CUTIL_LN2_F			0.69314718055994530942f	// ln(2)
#define CUTIL_LN10_F		2.30258509299404568402f	// ln(10)

#define CUTIL_PI_F			3.14159265358979323846f	// pi
#define CUTIL_2_PI_F		6.28318530717958647692f	// 2*pi
#define CUTIL_3_PI_F		9.42477796076937971538f	// 3*pi
#define CUTIL_PI_2_F		1.57079632679489661923f	// pi/2
#define CUTIL_PI_3_F		1.04719755119659774615f	// pi/3
#define CUTIL_PI_4_F		0.78539816339744830962f	// pi/4
#define CUTIL_INV_PI_F		0.31830988618379067154f	// 1/pi
#define CUTIL_INV_SQRT_PI_F	0.56418958354775628694f	// 1/sqrt(pi)
#define CUTIL_2_INV_PI_F	0.63661977236758134308f	// 2/pi
#define CUTIL_2_SQRT_PI_F	1.12837916709551257390f	// 2/sqrt(pi)

#define CUTIL_SQRT_2_F		1.41421356237309504880f	// sqrt(2)
#define CUTIL_INV_SQRT_2_F	0.70710678118654752440f	// 1/sqrt(2)
#define CUTIL_SQRT_3_F		1.73205080756887729353f	// sqrt(3)
#define CUTIL_INV_SQRT_3_F	0.57735026918962576451f	// 1/sqrt(3)

#define CUTIL_PHI_F			1.61803398874989484820f	// (1 + sqrt(5)) / 2, golden ratio
#define CUTIL_INV_PHI_F		0.61803398874989484820f	// 2 / (1 + sqrt(5)), inversed golden ratio

#define CUTIL_EGAMMA_F		0.57721566490153286060f	// Euler-Mascheroni constant




//======================= Memory Operations =========================
//* swap items, only for C, types of `_VAR1` and `_VAR2` should be strictly equal
//	WARNING: cannot use for C arrays, use `std::swap` in C++
#define CUTIL_SWAP_TYPE(_TYPE, _VAR1, _VAR2) 	do {_TYPE _sw = (_VAR2); (_VAR2) = (_VAR1); (_VAR1) = _sw;} while(0) // CUTIL_SWAP_VARS(uint32_t, a, b);
#define CUTIL_SWAP(_VAR1, _VAR2)			 	CUTIL_SWAP_TYPE(CUTIL_TYPEOF(_VAR1), _VAR1, _VAR2) // only for GNU C and C23 because it uses `typeof`
/*
	uint32_t a = 1, b = 2; // type of `a` and `b` must be strictly equal.

	CUTIL_SWAP(a, b); // in C++(std::decay<decltype(var)>::type), GNU C(typeof), or C23(typeof)

	CUTIL_SWAP_TYPE(uint32_t, a, b); 	// equivelent, specify the type.
	CUTIL_SWAP_TYPE(typeof(a), a, b); 	// equivelent, in GNU C or C23
	CUTIL_SWAP_TYPE(std::decay<decltype(var)>::type, a, b); // equivelent in C++, but prefer to use `std::swap()`
	
	std::swap(a, b); // C++
*/


//* get size of a C array
// WARNING: if a C array is passed to a function, it will decay to a pointer, then this macro dose not work.
#define CUTIL_ARRAY_SIZE(_arr)			(sizeof((_arr)) / sizeof((_arr[0])))


//* get high or low byte (uint8_t) of a word (uint16_t)
#define CUTIL_GET_WORD_LOW(_W)			((uint8_t) ((uint16_t)(_W) & 0xFF))
#define CUTIL_GET_WORD_HIGH(_W)			((uint8_t) ((uint16_t)(_W) >> 8u))

#define CUTIL_SET_WORD_LOW(_W, _val)	((_W) = (((uint16_t)(_W) & 0xFF00) | (uint8_t)(_val)), (_W))
#define CUTIL_SET_WORD_HIGH(_W, _val)	((_W) = (((uint16_t)(_W) & 0x00FF) | (uint16_t)(_val) << 8u), (_W))
/*
	uint16_t v {0x1234};
	printf("%x \n", v); // -> 1234
	printf("%x %x \n", CUTIL_GET_WORD_HIGH(v), CUTIL_GET_WORD_LOW(v));	// -> 12 34
	printf("%x %x \n", CUTIL_SET_WORD_HIGH(v, 0xFE), CUTIL_SET_WORD_LOW(v, 0xBA)); // -> FE BA
	printf("%x \n", v);	// -> FEBA
*/


//* operate value of specific memory location
// get pointer (in specific type) which points to the address of specific variable
#define CUTIL_GET_PTR_VOID(_var)				(			 (void*) &(_var))
#define CUTIL_GET_PTR_U8(_var)					((uint8_t*)	 (void*) &(_var))
#define CUTIL_GET_PTR_U16(_var)					((uint16_t*) (void*) &(_var))
#define CUTIL_GET_PTR_U32(_var)					((uint32_t*) (void*) &(_var))
#define CUTIL_GET_PTR_U64(_var)					((uint64_t*) (void*) &(_var))
#define CUTIL_GET_PTR_SIZE(_var)				((size_t*)	 (void*) &(_var))
#define CUTIL_GET_PTR_TYPE(_type, _var)			((_type *)	 (void*) &(_var))

// get value from the memory address in the specific type
#define CUTIL_GET_MEM_U8(_ptr)					(*((volatile uint8_t*)	(_ptr)))
#define CUTIL_GET_MEM_U16(_ptr)					(*((volatile uint16_t*)	(_ptr)))
#define CUTIL_GET_MEM_U32(_ptr)					(*((volatile uint32_t*)	(_ptr)))
#define CUTIL_GET_MEM_U64(_ptr)					(*((volatile uint64_t*)	(_ptr)))
#define CUTIL_GET_MEM_SIZE(_ptr)				(*((volatile size_t*)	(_ptr)))
#define CUTIL_GET_MEM_TYPE(_type, _ptr)			(*((volatile _type *)	(_ptr)))

// set memory at the specific location in the specific type
#define CUTIL_SET_MEM_U8(_ptr, _val)			(*((volatile uint8_t*)	_ptr) = _val, _val)
#define CUTIL_SET_MEM_U16(_ptr, _val)			(*((volatile uint16_t*)	_ptr) = _val, _val)
#define CUTIL_SET_MEM_U32(_ptr, _val)			(*((volatile uint32_t*)	_ptr) = _val, _val)
#define CUTIL_SET_MEM_U64(_ptr, _val)			(*((volatile uint64_t*)	_ptr) = _val, _val)
#define CUTIL_SET_MEM_SIZE(_ptr, _val)			(*((volatile size_t*)	_ptr) = _val, _val)
#define CUTIL_SET_MEM_TYPE(_type, _ptr, _val) 	(*((volatile _type *)	_ptr) = _val, _val)
/*
	uint32_t a = 0x12345678;
	uint32_t b = 0xFEDCBA98;
	
	printf("%x, %x \n", CUTIL_GET_MEM_U32(&a), CUTIL_GET_MEM_U32(&b)); 	// get content as type `uint32_t` at the location `&a and `&b`, it prints the value of `a` and `b`
	
	printf("%p, %p \n", CUTIL_GET_PTR_U32(a), CUTIL_GET_PTR_U32(b));	// get address as type `uint32_t*` of the variable `a` and `b`
	printf("%p\n", CUTIL_GET_PTR_TYPE(uint32_t, a));					// equivelent
	
	CUTIL_SET_MEM_U32(&a, 0x66666666);				// set content of address `&b` as `0x66666666`, in the type of `uint32_t`
	CUTIL_SET_MEM_TYPE(uint32_t, &b, 0x77777777);	// set content of address `&b` as `0x77777777`, in the type of `uint32_t`
	
	printf("%x, %x \n", CUTIL_GET_MEM_U32(&a), CUTIL_GET_MEM_U32(&b));
	
	
	// output:
	//		12345678, fedcba98
	//		000000C48D7BFB04, 000000C48D7BFB24
	//		000000C48D7BFB04
	//		66666666, fedcba98
*/


//* C memory allocations
	// use `std::allocator()` in C++11 to replace malloc
// malloc by type and amount, only alloc heap memory without initialization. returns nullptr if failed.
#define CUTIL_TYPE_MALLOC(_TYPE, _AMOUNT) 			(_TYPE*)malloc((_AMOUNT)*sizeof(_TYPE)) // only alloc.
// calloc by type and amount, alloc heap memory then initialize with 0x00. returns nullptr if failed.
#define CUTIL_TYPE_CALLOC(_TYPE, _AMOUNT) 			(_TYPE*)calloc((_AMOUNT), sizeof(_TYPE))  // init to 0
// realloc memory by type and amount. returns nullptr if failed.
#define CUTIL_TYPE_REALLOC(_TYPE, _PTR, _AMOUNT)	(_TYPE*)realloc((_PTR), (_AMOUNT)*sizeof(_TYPE))
// free heap memory allocated with malloc/calloc, then set to nullptr.
#define CUTIL_TYPE_FREE(_PTR) 						do {if((_PTR) != NULL) {free(_PTR); _PTR = NULL;}} while(0)
#define CUTIL_FREE(_PTR)							CUTIL_TYPE_FREE(_PTR) // alias


//* C memory operations
	// use `std::uninitialized_copy` `std::uninitialized_fill` `std::uninitialized_move`  in  C++
// memcpy by type and amount. returns dest pointer.
#define CUTIL_TYPE_MEMCPY(_TYPE, _DESTPTR, _SRCPTR, _AMOUNT)	\
		(_TYPE*)memcpy((_DESTPTR), (_SRCPTR), (_AMOUNT)*sizeof(_TYPE))
// memmove by type and amount. supports overlapped memory blocks.
#define CUTIL_TYPE_MEMMOVE(_TYPE, _DESTPTR, _SRCPTR, _AMOUNT)	\
		(_TYPE*)memmove((_DESTPTR), (_SRCPTR), (_AMOUNT)*sizeof(_TYPE))
// set a range of memory by type and amount with BYTE data.
#define CUTIL_TYPE_MEMSET(_TYPE, _DESTPTR, _BYTE, _AMOUNT) 		\
		(_TYPE*)memset((_DESTPTR), (_BYTE), (_AMOUNT)*sizeof(_TYPE))
// compare a range of memory blocks data, returns integer values <0, >0 or =0(equal).
#define CUTIL_TYPE_MEMCMP(_TYPE, _PTR1, _PTR2, _AMOUNT)			\
		memcmp((_PTR1), (_PTR2), (_AMOUNT)*sizeof(_TYPE))
/*
* Examples:
	const size_t amount = 20; // amount of variables (!= length in bytes! )
	uint32_t* aD1 = CUTIL_TYPE_MALLOC(uint32_t, amount); // std::vector<uint32_t> v1(20); -> elements == 0xCDCDCDCD in heap
	uint32_t* aD2 = CUTIL_TYPE_CALLOC(uint32_t, amount); // std::vector<uint32_t> v1(20, 0x00000000);
	uint32_t aD3[amount]; // C99 VLA, unsupported in C++, -> elements == 0xCCCCCCCC in stack
	
	uint32_t* aD3 = CUTIL_TYPE_MEMSET(uint32_t, aD1, 0x66, amount); // set all elements of aD1 to 0x66666666, returns aD3 == aD1
	uint32_t* aD4 = CUTIL_TYPE_MEMMOVE(uint32_t, aD2, aD1, amount); // copy aD1 elements to aD2, returns aD4==aD2
	uint32_t* aD5 = CUTIL_TYPE_MEMCPY(uint32_t, aD2, aD1, amount);  // equivalents to above.
	
	int compResult = CUTIL_TYPE_MEMCMP(uint32_t, aD1, aD2, amount); // returns 0, contents of mem blocks equal.
	
	CUTIL_TYPE_FREE(aD1); // element values -> 0xDDDDDDDD (deleted heap); then set `aD1` to `nullptr`
	CUTIL_TYPE_FREE(aD2);
	// you need't add `aD1 = NULL`.
*/


//* features with C struct and memory offset/address
// calculate the struct address from the member's address, within the type `size_t`
#define CUTIL_STRUCT_FIELD_OFFSET(_type, _field) 		((size_t) &((_type*) 0)->_field)

// get the size of a struct member
#define CUTIL_STRUCT_FIELD_SIZE(_type, _field)			sizeof(((_type*)0)->_field)

// use the address of a struct member, to calculate the address of the containing struct object, within the type `_type*`
#define CUTIL_STRUCT_FIELD_CONTAINER(_type, _field, _fieldAddr)	\
			((_type*)((char*)(_fieldAddr) - (char*) &((_type*)0)->_field)) // must use `char*`

#if (CONSOLE_UTIL_DO_NOT_USE_SHORTER_ALIAS == 0) //* shorter aliases
	#define CU_FIELD_OFFSET(_type, _field)					CUTIL_STRUCT_FIELD_OFFSET(_type, _field)
	#define CU_FIELD_SIZE(_type, _field)					CUTIL_STRUCT_FIELD_SIZE(_type, _field)
	#define CU_FIELD_CONTAINER(_type, _field, _fieldAddr)	CUTIL_STRUCT_FIELD_CONTAINER(_type, _field, _fieldAddr)
#endif // CONSOLE_UTIL_DO_NOT_USE_SHORTER_ALIAS
/*
	//* define a struct type `struct MyStruct`(C) or `MyStruct`(C++)
	struct MyStruct {
		uint8_t 	a;	// 0    (+0)
		uint8_t 	b;	// 1      |--(+1)
		uint32_t 	c;	// 4    (+4)
		uint8_t 	d;	// 8    (+4)
		uint8_t 	e;	// 9      |--(+1)
		uint8_t 	f;	// 10     |--(+1)
		uint64_t 	g;	// 16   (+8)
		uint32_t 	h;	// 24   (+8)
	};
	struct MyStruct myStruct; //* create a struct object `myStruct`
	
	//* get the memory offset of a struct member
	printf("offset: a-%zu", CUTIL_STRUCT_FIELD_OFFSET(struct MyStruct, a));	// output: `offset: a-0`
	printf("offset: b-%zu", CUTIL_STRUCT_FIELD_OFFSET(struct MyStruct, b));	// output: `offset: b-1`
	printf("offset: c-%zu", CUTIL_STRUCT_FIELD_OFFSET(struct MyStruct, c));	// output: `offset: c-4`
	//...
	// output: `offset: a:0, b:1, c:4, d:8, e:9, f:10, g:16, h:24`
	
	// you can simplify the code above with `CUTIL_SEQ_ENUM`, like this:
	#define MYSTRUCT_OFFSET_OF_ELEMENT(_x)  CUTIL_STRUCT_FIELD_OFFSET(struct MyStruct, _x)
	printf("offset: a:%zu, b:%zu, c:%zu, zu:%zu, e:%zu, f:%zu, g:%zu, h:%zu \n"
			, CUTIL_SEQ_ENUM(MYSTRUCT_OFFSET_OF_ELEMENT, a, b, c, d, e, f, g, h)
				// , CUTIL_STRUCT_FIELD_OFFSET(struct MyStruct, a)
				// , CUTIL_STRUCT_FIELD_OFFSET(struct MyStruct, b)
				//  ...
				// , CUTIL_STRUCT_FIELD_OFFSET(struct MyStruct, h)
	);	// output: `offset: a:0, b:1, c:4, d:8, e:9, f:10, g:16, h:24`
	
	
	//* get the size of a struct member
	printf("size: a-%zu", CUTIL_STRUCT_FIELD_SIZE(struct MyStruct, a));	// output: `size: a-1`
	printf("size: b-%zu", CUTIL_STRUCT_FIELD_SIZE(struct MyStruct, b));	// output: `size: b-1`
	printf("size: g-%zu", CUTIL_STRUCT_FIELD_SIZE(struct MyStruct, g));	// output: `size: g-8`
	// ...
	// output: `size: a:1, b:1, c:4, d:1, e:1, f:1, g:8, h:4`
	
	// you can simplify the code above with `CUTIL_SEQ_ENUM`, like this:
	#define MYSTRUCT_SIZE_OF_ELEMENT(_x)  CUTIL_FIELD_SIZE(struct MyStruct, _x)
	printf("size: a:%zu, b:%zu, c:%zu, d:%zu, e:%zu, f:%zu, g:%zu, h:%zu \n"
			, CUTIL_SEQ_ENUM(MYSTRUCT_SIZE_OF_ELEMENT, a, b, c, d, e, f, g, h)
				// , CUTIL_STRUCT_FIELD_SIZE(struct MyStruct, a)
				// , CUTIL_STRUCT_FIELD_SIZE(struct MyStruct, b)
				//  ...
				// , CUTIL_STRUCT_FIELD_SIZE(struct MyStruct, h)
	);	// output: `size: a:1, b:1, c:4, d:1, e:1, f:1, g:8, h:4`
	
	
	//* use the address of a struct member, to calculate the address of the containing struct object
	printf("loc of myStruct: %p %p \n",
		&myStruct,
		CUTIL_STRUCT_FIELD_CONTAINER(struct MyStruct, b, &myStruct.b) // [b, &myStruct.b] => &myStruct
	);
	// output: `loc of myStruct: 0000006CE9EFF9D8 0000006CE9EFF9D8`
*/

//* get if the expression is an ICE (integral constant expression)
#define CUTIL_IS_ICE(_x)	(sizeof(int) == sizeof(*(1 ? ((void*)((_x) * 0l)) : (int*)1)))




#endif /* CONSOLEUTIL_C_UTIL_H__ */
