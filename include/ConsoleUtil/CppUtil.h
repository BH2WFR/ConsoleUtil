/* UTF-8 encoding
* Project URL: 	https://github.com/BH2WFR/ConsoleUtil
  Author:		BH2WFR
* You can include this header in header files.
*/
#ifndef CONSOLEUTIL_CPP_UTIL_H__
#define CONSOLEUTIL_CPP_UTIL_H__


//* ==== Environment Check, `> C99/C++98` with `##__VA_ARGS__` extension (available in MSVC(>VS2015 U3)/GCC/Clang)
#if (!defined(__cplusplus)) && (__STDC_VERSION__ < 199901L || (!defined(__STDC_VERSION__)))
	#error This Header DO NOT SUPPORTS C89! - >=C99 or C++ Required.
#endif



// include vital C headers
#ifdef __cplusplus
	#include <cstdio>
	#include <cstdlib>
	#include <cstdint>
	#include <cfloat>
#else //. !__cplusplus
	#include <stdio.h>
	#include <stdlib.h>
	#include <stdint.h>	// uint32_t
	#include <float.h>	// floating-point limits
	#if (__STDC_VERSION__ >= 199901L) && (__STDC_VERSION__ < 202311L)
		#include <stdbool.h> // bool support since C99, before C23 (became keyword)
	#endif
#endif // __cplusplus






//===================== Basic Macros =========================
// #define CUTIL_EMPTY(x)
// #define CUTIL_SELF(_1)					_1
#define CUTIL_CAT_TOKENS(_1, _2)		_1 ## _2 	// do not merge with `CUTIL_CAT_2()`
#define CUTIL_EXPAND(...)				__VA_ARGS__ // for MSVC without `/Zc:preprocessor`

// macro function overloading support
#define CUTIL_OVERLOAD_IDX(_func, _idx)			CUTIL_CAT_TOKENS(_func, _idx)
#define _CUTIL_OVERLOAD_DISPACHER(_func, ...) 	CUTIL_OVERLOAD_IDX(_func, CUTIL_VA_CNT(__VA_ARGS__))




//======================= C Utils ============================

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


//* get type of variable, only for GNU C, C23, C++
#ifndef __cplusplus
	#define CUTIL_TYPE(_VAR)	typeof(_VAR)	// only for GNU C, and C23.
#else //. ! __cplusplus
	#define CUTIL_TYPE(_VAR)	decltype(_VAR) 	// do not quote `_VAR`
#endif //. ! __cplusplus


//* get count of arguments, up to 35
#define _CUTIL_VA_63TH_ARG(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9, \
			a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z, \
			A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,_63TH_ARG,...)  _63TH_ARG
#define CUTIL_VA_CNT(...)	CUTIL_EXPAND(_CUTIL_VA_63TH_ARG("ignored", ##__VA_ARGS__, \
			Z,Y,X,W,V,U,T,S,R,Q,P,O,N,M,L,K,J,I,H,G,F,E,D,C,B,A,35,34,33,32,31,30,29,28,27, \
			26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0))
/*
 Examples:
	int a = CUTIL_VA_CNT(); 			// -> 0
	int b = CUTIL_VA_CNT(b1); 			// -> 1
	int c = CUTIL_VA_CNT(c1, c2); 		// -> 2
	int c = CUTIL_VA_CNT(c1, c2, c3); 	// -> 3
	...
*/



//* string conversion support
#define CUTIL_STR(_1)			#_1
#define CUTIL_LSTR(_1)			CUTIL_CAT_TOKENS(L, #_1)	// wchar_t
#define CUTIL_U8STR(_1)			CUTIL_CAT_TOKENS(u8, #_1) 	// C++17, char8_t
#define CUTIL_U16STR(_1)		CUTIL_CAT_TOKENS(u, #_1) 	// C++11, char16_t
#define CUTIL_U32STR(_1)		CUTIL_CAT_TOKENS(U, #_1) 	// C++11, char32_t


//* token concatenation support
#define CUTIL_CAT_2(_1, _2)				    _1 ## _2
#define CUTIL_CAT_3(_1, _2, _3)			    _1 ## _2 ## _3
#define CUTIL_CAT_4(_1, _2, _3, _4)		    _1 ## _2 ## _3 ## _4
#define CUTIL_CAT_5(_1, _2, _3, _4, _5)	    _1 ## _2 ## _3 ## _4 ## _5
#define CUTIL_CAT_6(_1, _2, _3, _4, _5, _6) \
							_1 ## _2 ## _3 ## _4 ## _5 ## _6
#define CUTIL_CAT_7(_1, _2, _3, _4, _5, _6, _7) \
							_1 ## _2 ## _3 ## _4 ## _5 ## _6 ## _7
#define CUTIL_CAT_8(_1, _2, _3, _4, _5, _6, _7, _8) \
							_1 ## _2 ## _3 ## _4 ## _5 ## _6 ## _7 ## _8
#define CUTIL_CAT_9(_1, _2, _3, _4, _5, _6, _7, _8, _9) \
							_1 ## _2 ## _3 ## _4 ## _5 ## _6 ## _7 ## _8 ## _9
#define CUTIL_CAT_10(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10) \
							_1 ## _2 ## _3 ## _4 ## _5 ## _6 ## _7 ## _8 ## _9 ## _10
#define CUTIL_CAT_11(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) \
							_1 ## _2 ## _3 ## _4 ## _5 ## _6 ## _7 ## _8 ## _9 ## _10 ## _11
#define CUTIL_CAT_12(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) \
							_1 ## _2 ## _3 ## _4 ## _5 ## _6 ## _7 ## _8 ## _9 ## _10 ## _11 ## _12
#define CUTIL_CAT_13(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) \
							_1 ## _2 ## _3 ## _4 ## _5 ## _6 ## _7 ## _8 ## _9 ## _10 ## _11 ## _12 ## _13
#define CUTIL_CAT_14(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) \
							_1 ## _2 ## _3 ## _4 ## _5 ## _6 ## _7 ## _8 ## _9 ## _10 ## _11 ## _12 ## _13 ## _14
#define CUTIL_CAT_15(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) \
							_1 ## _2 ## _3 ## _4 ## _5 ## _6 ## _7 ## _8 ## _9 ## _10 ## _11 ## _12 ## _13 ## _14 ## _15
#define CUTIL_CAT(...)        		CUTIL_EXPAND(CUTIL_OVERLOAD_IDX(CUTIL_CAT_, CUTIL_VA_CNT(__VA_ARGS__))(__VA_ARGS__))
/* Instruction:
	int a1 = CUTIL_CAT(11, 22); 			// a1 = 1122
	int a2 = CUTIL_CAT(10, 11, 12, 13); 	// a2 = 10111213
	std::cout << CUTIL_CAT(a, 1) << "\n"; 	// print variable `a1`
*/


//* to simplify the code like `(var == 1 || var == 2 || var == 3 || ...)`
#define CUTIL_EQUAL_OR_1(_var, _1) 					((_var) == (_1))
#define CUTIL_EQUAL_OR_2(_var, _1, _2) 				((_var) == (_1) || (_var) == (_2))
#define CUTIL_EQUAL_OR_3(_var, _1, _2, _3) 			(CUTIL_EQUAL_OR_2(_var, _1, _2) || (_var) == (_3))
#define CUTIL_EQUAL_OR_4(_var, _1, _2, _3, _4) 		(CUTIL_EQUAL_OR_3(_var, _1, _2, _3) || (_var) == (_4))
#define CUTIL_EQUAL_OR_5(_var, _1, _2, _3, _4, _5) 	(CUTIL_EQUAL_OR_4(_var, _1, _2, _3, _4) || (_var) == (_5))
#define CUTIL_EQUAL_OR_6(_var, _1, _2, _3, _4, _5, _6) \
						(CUTIL_EQUAL_OR_5(_var, _1, _2, _3, _4, _5) || (_var) == (_6))
#define CUTIL_EQUAL_OR_7(_var, _1, _2, _3, _4, _5, _6, _7) \
						(CUTIL_EQUAL_OR_6(_var, _1, _2, _3, _4, _5, _6) || (_var) == (_7))
#define CUTIL_EQUAL_OR_8(_var, _1, _2, _3, _4, _5, _6, _7, _8) \
						(CUTIL_EQUAL_OR_7(_var, _1, _2, _3, _4, _5, _6, _7) || (_var) == (_8))
#define CUTIL_EQUAL_OR_9(_var, _1, _2, _3, _4, _5, _6, _7, _8, _9) \
						(CUTIL_EQUAL_OR_8(_var, _1, _2, _3, _4, _5, _6, _7, _8) || (_var) == (_9))
#define CUTIL_EQUAL_OR_10(_var, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) \
						(CUTIL_EQUAL_OR_9(_var, _1, _2, _3, _4, _5, _6, _7, _8, _9) || (_var) == (_10))
#define CUTIL_EQUAL_OR_11(_var, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) \
						(CUTIL_EQUAL_OR_10(_var, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) || (_var) == (_11))
#define CUTIL_EQUAL_OR_12(_var, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) \
						(CUTIL_EQUAL_OR_11(_var, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) || (_var) == (_12))
#define CUTIL_EQUAL_OR_13(_var, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) \
						(CUTIL_EQUAL_OR_12(_var, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) || (_var) == (_13))
#define CUTIL_EQUAL_OR_14(_var, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) \
						(CUTIL_EQUAL_OR_13(_var, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) || (_var) == (_14))
#define CUTIL_EQUAL_OR_15(_var, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) \
						(CUTIL_EQUAL_OR_14(_var, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) || (_var) == (_15))
#define CUTIL_EQUAL_OR(_var, ...) 	CUTIL_EXPAND(CUTIL_OVERLOAD_IDX(CUTIL_EQUAL_OR_, CUTIL_VA_CNT(__VA_ARGS__))(_var, __VA_ARGS__))
/* Instruction:
	int var = 10;
	if(CUTIL_EQUAL_OR(var, 5, 10)){
		// equivalent to `if(var == 5 || var == 10)`
		// equivalent to `if(! CUTIL_UNEQUAL_AND(var, 5, 10))`
	}
	if(CUTIL_EQUAL_OR(var, 2, 4, 6, 8, 10)){
		// equivalent to `if(var == 2 || var == 4 || var == 6 || var == 8 || var == 10)`
		// equivalent to `if(! CUTIL_UNEQUAL_AND(var, 2, 4, 6, 8, 10))`
	}
*/


//* to simplify the code like `(var != 1 && var != 2 && var != 3 && ...)`
#define CUTIL_UNEQUAL_AND_1(_var, _1) 					((_var) != (_1))
#define CUTIL_UNEQUAL_AND_2(_var, _1, _2) 				((_var) != (_1) && (_var) != (_2))
#define CUTIL_UNEQUAL_AND_3(_var, _1, _2, _3) 			(CUTIL_UNEQUAL_AND_2(_var, _1, _2) && (_var) != (_3))
#define CUTIL_UNEQUAL_AND_4(_var, _1, _2, _3, _4) 		(CUTIL_UNEQUAL_AND_3(_var, _1, _2, _3) && (_var) != (_4))
#define CUTIL_UNEQUAL_AND_5(_var, _1, _2, _3, _4, _5) 	(CUTIL_UNEQUAL_AND_4(_var, _1, _2, _3, _4) && (_var) != (_5))
#define CUTIL_UNEQUAL_AND_6(_var, _1, _2, _3, _4, _5, _6) \
						(CUTIL_UNEQUAL_AND_5(_var, _1, _2, _3, _4, _5) && (_var) != (_6))
#define CUTIL_UNEQUAL_AND_7(_var, _1, _2, _3, _4, _5, _6, _7) \
						(CUTIL_UNEQUAL_AND_6(_var, _1, _2, _3, _4, _5, _6) && (_var) != (_7))
#define CUTIL_UNEQUAL_AND_8(_var, _1, _2, _3, _4, _5, _6, _7, _8) \
						(CUTIL_UNEQUAL_AND_7(_var, _1, _2, _3, _4, _5, _6, _7) && (_var) != (_8))
#define CUTIL_UNEQUAL_AND_9(_var, _1, _2, _3, _4, _5, _6, _7, _8, _9) \
						(CUTIL_UNEQUAL_AND_8(_var, _1, _2, _3, _4, _5, _6, _7, _8) && (_var) != (_9))
#define CUTIL_UNEQUAL_AND_10(_var, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) \
						(CUTIL_UNEQUAL_AND_9(_var, _1, _2, _3, _4, _5, _6, _7, _8, _9) && (_var) != (_10))
#define CUTIL_UNEQUAL_AND_11(_var, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) \
						(CUTIL_UNEQUAL_AND_10(_var, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) && (_var) != (_11))
#define CUTIL_UNEQUAL_AND_12(_var, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) \
						(CUTIL_UNEQUAL_AND_11(_var, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) && (_var) != (_12))
#define CUTIL_UNEQUAL_AND_13(_var, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) \
						(CUTIL_UNEQUAL_AND_12(_var, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) && (_var) == (_13))
#define CUTIL_UNEQUAL_AND_14(_var, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) \
						(CUTIL_UNEQUAL_AND_13(_var, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) && (_var) == (_14))
#define CUTIL_UNEQUAL_AND_15(_var, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) \
						(CUTIL_UNEQUAL_AND_14(_var, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) && (_var) == (_15))
#define CUTIL_UNEQUAL_AND(_var, ...) 	CUTIL_EXPAND(CUTIL_OVERLOAD_IDX(CUTIL_UNEQUAL_AND_, CUTIL_VA_CNT(__VA_ARGS__))(_var, __VA_ARGS__))
/* Instruction:
	int var = 10;
	if(CUTIL_UNEQUAL_AND(var, 5, 10)){
		// equivalent to `if(var != 5 && var != 10)`
		// equivalent to `if(! CUTIL_EQUAL_OR(var, 5, 10))`
	}
	if(CUTIL_UNEQUAL_AND(var, 2, 4, 6, 8, 10)){
		// equivalent to `if(var != 2 && var != 4 && var != 6 && var != 8 && var != 10)`
		// equivalent to `if(! CUTIL_EQUAL_OR(var, 2, 4, 6, 8, 10))`
	}
*/




//* bit calculating macros
#define CUTIL_BIT_GET_MASK(_NUM, _BIT_MASK)		((_NUM) & (_BIT_MASK))
#define CUTIL_BIT_SET_MASK(_NUM, _BIT_MASK)		{(_NUM) |=  (_BIT_MASK);}	// must use them in a separate line, returns nothing
#define CUTIL_BIT_CLEAR_MASK(_NUM, _BIT_MASK)	{(_NUM) &= ~(_BIT_MASK);}
#define CUTIL_BIT_TOGGLE_MASK(_NUM, _BIT_MASK)	{(_NUM) ^=  (_BIT_MASK);}

#define CUTIL_BIT_GET_IDX(_NUM, _BIT_IDX)		CUTIL_BIT_GET_MASK(_NUM, 	(1u << (_BIT_IDX)))	// if bit of index _BIT_IDX is 1, returns (1<<_BIT_IDX), NOT 1
#define CUTIL_BIT_SET_IDX(_NUM, _BIT_IDX)		CUTIL_BIT_SET_MASK(_NUM, 	(1u << (_BIT_IDX)))	// must use them in separate lines, returns nothing
#define CUTIL_BIT_CLEAR_IDX(_NUM, _BIT_IDX)		CUTIL_BIT_CLEAR_MASK(_NUM, 	(1u << (_BIT_IDX)))
#define CUTIL_BIT_TOGGLE_IDX(_NUM, _BIT_IDX) 	CUTIL_BIT_TOGGLE_MASK(_NUM, (1u << (_BIT_IDX)))
#define CUTIL_BIT_CHK_IDX(_NUM, _BIT_IDX)		(CUTIL_BIT_GET_IDX(_NUM, _BIT_IDX) ? 1 : 0) 	// returns 1 if bit of _BIT_IDX is 1, != CUTIL_BIT_GET_IDX()

#if (CONSOLE_UTIL_DO_NOT_USE_SHORTER_ALIAS == 0) //* shorter aliases
	#define CU_BIT_IDX(_NUM, _BIT_IDX)			CUTIL_BIT_GET_IDX(_NUM, _BIT_IDX)
	#define CU_BIT_1(_NUM, _BIT_IDX)			CUTIL_BIT_CHK_IDX(_NUM, _BIT_IDX)
#endif // CONSOLE_UTIL_DO_NOT_USE_SHORTER_ALIAS


// rotate bits, use them in a separate line
#define CUTIL_BIT_ROTATE_LEFT_SIZE(_BIT_SIZE, _BIT, _STEP)		{(_BIT) = ((_BIT) << (_STEP)) | ((_BIT) >> ((_BIT_SIZE) - (_STEP)));}
#define CUTIL_BIT_ROTATE_RIGHT_SIZE(_BIT_SIZE, _BIT, _STEP)		{(_BIT) = ((_BIT) >> (_STEP)) | ((_BIT) << ((_BIT_SIZE) - (_STEP)));}

#define CUTIL_BIT_ROTATE_LEFT_TYPE(_TYPE, _BIT, _STEP)		CUTIL_BIT_ROTATE_LEFT_SIZE(8u * sizeof(_TYPE), _BIT, _STEP)
#define CUTIL_BIT_ROTATE_RIGHT_TYPE(_TYPE, _BIT, _STEP)		CUTIL_BIT_ROTATE_RIGHT_SIZE(8u * sizeof(_TYPE), _BIT, _STEP)

#define CUTIL_BIT_ROTATE_LEFT(_BIT, _STEP)		CUTIL_BIT_ROTATE_LEFT_TYPE(CUTIL_TYPE(_BIT), _BIT, _STEP) // uses `typeof`, GNU C, C23, C++ only
#define CUTIL_BIT_ROTATE_RIGHT(_BIT, _STEP)		CUTIL_BIT_ROTATE_RIGHT_TYPE(CUTIL_TYPE(_BIT), _BIT, _STEP)


//* swap items, only for C, types of `_VAR1` and `_VAR2` should be strictly equal, do not use in
#define CUTIL_SWAP_TYPE(_TYPE, _VAR1, _VAR2) 	{_TYPE _sw = (_VAR2); (_VAR2) = (_VAR1); (_VAR1) = _sw;} // CUTIL_SWAP_VARS(uint32_t, a, b);
#define CUTIL_SWAP(_VAR1, _VAR2)			 	CUTIL_SWAP_TYPE(CUTIL_TYPE(_VAR1), _VAR1, _VAR2) // only for GNU C and C23 because it uses `typeof`


//* get min or max value
#define CUTIL_MAX(_VAR1, _VAR2) 	(((_VAR1) > (_VAR2)) ? (_VAR1) : (_VAR2))
#define CUTIL_MIN(_VAR1, _VAR2)		(((_VAR1) < (_VAR2)) ? (_VAR1) : (_VAR2))

//* get abs of int/float/double (not recommended in C++, pls use abs() function)
#define CUTIL_ABS(_VAR)		(((_VAR) >= 0) ? (_VAR) : (-1)*(_VAR) ) // equals to abs(), fabs(), fabsf() function in C

#if (CONSOLE_UTIL_DO_NOT_USE_SHORTER_ALIAS == 0) //* shorter aliases
	#define CU_MAX(_VAR1, _VAR2) 		CUTIL_MAX(_VAR1, _VAR2)
	#define CU_MIN(_VAR1, _VAR2) 		CUTIL_MIN(_VAR1, _VAR2)
	#define CU_ABS(_VAR)				CUTIL_ABS(_VAR)
#endif // CONSOLE_UTIL_DO_NOT_USE_SHORTER_ALIAS


//* determine if two float/double numbers are regarded as equal (within epsilon)
#define CUTIL_EQUAL(_F1, _F2, _EPSILON)		(( CUTIL_ABS((_F1) - (_F2)) < CUTIL_ABS((_EPSILON)) ) ? 1 : 0) // diff within (-epsilon, +epsilon)
#define CUTIL_EQUAL_F(_F1, _F2)				CUTIL_EQUAL(_F1, _F2, FLT_EPSILON)	// float, using epsilon values defined in <float.h>
#define CUTIL_EQUAL_D(_F1, _F2)				CUTIL_EQUAL(_F1, _F2, DBL_EPSILON)	// double
#define CUTIL_EQUAL_LD(_F1, _F2)			CUTIL_EQUAL(_F1, _F2, LDBL_EPSILON) // long double

#if (CONSOLE_UTIL_DO_NOT_USE_SHORTER_ALIAS == 0) //* shorter aliases
	#define CU_EQU(_F1, _F2, _EPSILON)			CUTIL_EQUAL(_F1, _F2, _EPSILON)
	#define CU_EQU_F(_F1, _F2)					CUTIL_EQUAL_F(_F1, _F2)
	#define CU_EQU_D(_F1, _F2)					CUTIL_EQUAL_D(_F1, _F2)
	#define CU_EQU_LD(_F1, _F2)					CUTIL_EQUAL_LD(_F1, _F2)
#endif // CONSOLE_UTIL_DO_NOT_USE_SHORTER_ALIAS

//* C memory allocations
// malloc by type and amount, only alloc heap memory without initialization. returns nullptr if failed.
#define CUTIL_TYPE_MALLOC(_TYPE, _AMOUNT) 			(_TYPE*)malloc((_AMOUNT)*sizeof(_TYPE)) // only alloc.
// calloc by type and amount, alloc heap memory then initialize with 0x00. returns nullptr if failed.
#define CUTIL_TYPE_CALLOC(_TYPE, _AMOUNT) 			(_TYPE*)calloc((_AMOUNT), sizeof(_TYPE))  // init to 0
// realloc memory by type and amount. returns nullptr if failed.
#define CUTIL_TYPE_REALLOC(_TYPE, _PTR, _AMOUNT)	(_TYPE*)realloc((_PTR), (_AMOUNT)*sizeof(_TYPE))
// free heap memory allocated with malloc/calloc, then set to nullptr.
#define CUTIL_TYPE_FREE(_PTR) 						{if((_PTR) != NULL) {free(_PTR); _PTR = NULL;}}
#define CUTIL_FREE(_PTR)							CUTIL_TYPE_FREE(_PTR) // alias


//* C memory operations
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


//======================= C++ Utils ==========================
#ifdef __cplusplus

//* get C++ language standard version, do not add "L" suffix after number
 // in MSVC compiler, __cplusplus always equals to 199711L, but _MSVC_LANG(Prior to VS2015) equals to cpp standard version
#ifdef _MSVC_LANG // example: #if CUTIL_CPP_LANG >= 201103L
	#define CUTIL_CPP_LANG			_MSVC_LANG	// for MSVC
#else //. !defined _MSVC_LANG
	#define CUTIL_CPP_LANG			__cplusplus // for GCC, Clang (also MSVC with the copiler argument "/Zc:__cplusplus")
#endif // _MSVC_LANG
/*
* example:
	#if CUTIL_CPP_LANG >= 199711L	// C++98
	#if CUTIL_CPP_LANG >= 201103L	// C++11
	#if CUTIL_CPP_LANG >= 201402L	// C++14
	#if CUTIL_CPP_LANG >= 201703L	// C++17
	#if CUTIL_CPP_LANG >= 202002L	// C++20
	#if CUTIL_CPP_LANG >= 202302L	// C++23 (temporary not supported)
*/


//* delete a heap pointer, and set it nullptr. arg "p" must be a pointer inited by "new" or "new[]".
#define CUTIL_DELETE(p)		{delete   p; p = NULL;}
#define CUTIL_DELETE_ARR(p)	{delete[] p; p = NULL;}
	// keyword "nullptr" is unsupported in C++98


//* set C++11 class constructor/moving/copying to disabled/default
#if CUTIL_CPP_LANG >= 201103L 	//* >= C++11
	// Default Constructor(no params) and Destructor
	#define CUTIL_CLASS_DEFAULT_CONSTRUCTOR(_CLASS_NAME) \
		_CLASS_NAME() = default; \
		~_CLASS_NAME() = default;
	
	// Disable copy constructor and copy operator=
	#define CUTIL_CLASS_DISABLE_COPY(_CLASS_NAME) \
		_CLASS_NAME(const _CLASS_NAME & ) = delete;\
		_CLASS_NAME& operator=(const _CLASS_NAME & ) = delete;
	
	// Default copy constructor and copy operator=
	#define CUTIL_CLASS_DEFAULT_COPY(_CLASS_NAME) \
		_CLASS_NAME(const _CLASS_NAME & ) = default;\
		_CLASS_NAME& operator=(const _CLASS_NAME & ) = default;
	
	// Disable move constructor and move operator=
	#define CUTIL_CLASS_DISABLE_MOVE(_CLASS_NAME) \
		_CLASS_NAME(_CLASS_NAME && ) noexcept = delete; \
		_CLASS_NAME& operator=(_CLASS_NAME && ) noexcept = delete;
	
	// Default move constructor and move operator=
	#define CUTIL_CLASS_DEFAULT_MOVE(_CLASS_NAME) \
		_CLASS_NAME(_CLASS_NAME && ) noexcept = default; \
		_CLASS_NAME& operator=(_CLASS_NAME && ) noexcept = default;
	
	// Disable moving and copying
	#define CUTIL_CLASS_DISABLE_COPY_MOVE(_CLASS_NAME) \
		CUTIL_CLASS_DISABLE_COPY(_CLASS_NAME) \
		CUTIL_CLASS_DISABLE_MOVE(_CLASS_NAME)
	
	// Default moving and copying
	#define CUTIL_CLASS_DEFAULT_COPY_MOVE(_CLASS_NAME) \
		CUTIL_CLASS_DEFAULT_COPY(_CLASS_NAME) \
		CUTIL_CLASS_DEFAULT_MOVE(_CLASS_NAME)
	
	// Default Constructor, Destructor, Copying, Moving
	#define CUTIL_CLASS_DEFAULT_FUNCTIONS(_CLASS_NAME) \
		CUTIL_CLASS_DEFAULT_CONSTRUCTOR(_CLASS_NAME) \
		CUTIL_CLASS_DEFAULT_COPY_MOVE(_CLASS_NAME)
	
#else // C++98/03
	#define CUTIL_CLASS_DEFAULT_CONSTRUCTOR(_CLASS_NAME)
	#define CUTIL_CLASS_DISABLE_COPY(_CLASS_NAME)
	#define CUTIL_CLASS_DEFAULT_COPY(_CLASS_NAME)
	#define CUTIL_CLASS_DISABLE_MOVE(_CLASS_NAME)
	#define CUTIL_CLASS_DEFAULT_MOVE(_CLASS_NAME)
	#define CUTIL_CLASS_DISABLE_COPY_MOVE(_CLASS_NAME)
	#define CUTIL_CLASS_DEFAULT_COPY_MOVE(_CLASS_NAME)
	#define CUTIL_CLASS_DEFAULT_FUNCTIONS(_CLASS_NAME)
	
#endif // >= C++11
#endif // __cplusplus


//===================== OS Related ========================

#if defined(_WIN32) || defined(WIN32) || defined(__WIN32) && !defined(__CYGWIN__) // in Windows
	#define CUTIL_OS_WIN32		//* Win32 || Win64
	#define CUTIL_OS_WINDOWS
	#if defined(WIN64) || defined(_WIN64) || defined(__WIN64)
		#define CUTIL_OS_WIN64	//* Win64
	#endif // WIN64
#endif // WIN32
#if defined (__CYGWIN__)
	#define CUTIL_OS_CYGWIN		//* Cygwin
#endif // __CYGWIN__
#if defined(__linux__) || defined(__linux)
	#define CUTIL_OS_LINUX		//* Linux
#endif // linux
#if defined(__ANDROID__) || defined(ANDROID)
	#define CUTIL_OS_ANDROID	//* Android
	#define CUTIL_OS_LINUX
#endif // android
#if defined(__APPLE__)
	#define CUTIL_OS_APPLE		//* Apple (IOS / MacOS / TVOS / WatchOS)
	#include <TargetConditionals.h>
	//TODO: 进一步的判断
#endif // apple


#endif // CONSOLEUTIL_CPP_UTIL_H__
