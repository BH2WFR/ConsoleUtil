/* UTF-8 encoding
* Project URL: https://github.com/BH2WFR/ConsoleUtil
  Author:		BH2WFR
* You can include this header in header files.
*/
#ifndef CONSOLEUTIL_CPP_UTIL_H__
#define CONSOLEUTIL_CPP_UTIL_H__


// include vital C headers
#ifdef __cplusplus
	#include <cstdio>
	#include <cstdlib>
	#include <cstdint>
#else //. !__cplusplus
	#include <stdio.h>
	#include <stdlib.h>
	#include <stdint.h>
	#include <stdbool.h>
#endif // __cplusplus


//==================== C Utils ============================
#define _DEBUG
#define NDEBUG
//* detect Debug Build or Release Build
#if (!defined(NDEBUG)) || defined(_DEBUG)
	#define CUTIL_DEBUG_BUILD 	 1 	// Debug
#else
	#define CUTIL_DEBUG_BUILD 	 0 	// Release RelWithDebInfo MinSizeRel
#endif
/*
	in MSVC, macro `_DEBUG` is defined under debug build;
	in GCC, macro `NDEBUG` is defined under release build;
	you can add `add_compile_definitions("$<IF:$<CONFIG:Debug>,_DEBUG,NDEBUG>")` in CMake.
	
Usage Example:
	#if CUTIL_DEBUG_BUILD // Debug
		//...
	#else // Release RelWithDebInfo MinSizeRel
		//...
	#endif
*/



//* get count of arguments
#define CUTIL_VA_63TH_ARG(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9, \
			a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z, \
			A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,_63TH_ARG,...)  _63TH_ARG
#define CUTIL_VA_CNT(...)	CUTIL_VA_63TH_ARG("ignored", ##__VA_ARGS__, \
			Z,Y,X,W,V,U,T,S,R,Q,P,O,N,M,L,K,J,I,H,G,F,E,D,C,B,A,35,34,33,32,31,30,29,28,27, \
			26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0)
/*
 Examples:
	int a = CUTIL_VA_CNT(); 			// -> 0
	int b = CUTIL_VA_CNT(b1); 			// -> 1
	int c = CUTIL_VA_CNT(c1, c2); 		// -> 2
	int c = CUTIL_VA_CNT(c1, c2, c3); 	// -> 3
	...
*/

//* bit calculating macros
#define CUTIL_BIT_GET(_NUM, BIT_IDX)	((_NUM) & (1u << (BIT_IDX)))	// if bit is 1, returns (1<<BIT_IDX), NOT 1
#define CUTIL_BIT_SET(_NUM, BIT_IDX)	((_NUM) |=  (1u << (BIT_IDX)));	// must use them in separate lines
#define CUTIL_BIT_CLEAR(_NUM, BIT_IDX)	((_NUM) &= ~(1u << (BIT_IDX)));
#define CUTIL_BIT_TOGGLE(_NUM, BIT_IDX)	((_NUM) ^=  (1u << (BIT_IDX)));


//* swap items, only for C, do not use in C++ (use std::swap())
#define CUTIL_SWAP_VARS(_VAR1, _VAR2, _TYPE) {_TYPE sw = _VAR2; _VAR2 = _VAR1; _VAR1 = sw;}
#define CUTIL_SWAP_VARS_GNU(_VAR1, _VAR2)	 {typeof(_VAR1) sw = _VAR2; _VAR2 = _VAR1; _VAR1 = sw;} // GNU C only
	// CUTIL_SWAP_VARS(int, a, b);


//* C memory allocations
// malloc by type and amount, only alloc heap memory without initialization. returns nullptr if failed.
#define CUTIL_TYPE_MALLOC(_TYPE, _AMOUNT) 	(_TYPE*)malloc((_AMOUNT)*sizeof(_TYPE)) // only alloc.
// calloc by type and amount, alloc heap memory then initialize with 0x00. returns nullptr if failed.
#define CUTIL_TYPE_CALLOC(_TYPE, _AMOUNT) 	(_TYPE*)calloc((_AMOUNT), sizeof(_TYPE))  // init to 0
// realloc memory by type and amount. returns nullptr if failed.
#define CUTIL_TYPE_REALLOC(_TYPE, _AMOUNT, _PTR)  (_TYPE*)realloc((_PTR), (_AMOUNT)*sizeof(_TYPE))
// free heap memory allocated with malloc/calloc, then set to nullptr.
#define CUTIL_TYPE_FREE(_PTR) 		{if((_PTR) != NULL) {free(_PTR); _PTR = NULL;}}

//* C memory operations
// memcpy by type and amount. returns dest pointer.
#define CUTIL_TYPE_MEMCPY(_TYPE, _AMOUNT, _DESTPTR, _SRCPTR)	\
	(_TYPE*)memcpy((_DESTPTR), (_SRCPTR), (_AMOUNT)*sizeof(_TYPE))
// memmove by type and amount. supports overlapped memory blocks.
#define CUTIL_TYPE_MEMMOVE(_TYPE, _AMOUNT, _DESTPTR, _SRCPTR)	\
	(_TYPE*)memmove((_DESTPTR), (_SRCPTR), (_AMOUNT)*sizeof(_TYPE))
// set a range of memory by type and amount with BYTE data.
#define CUTIL_TYPE_MEMSET(_TYPE, _AMOUNT, _BYTE, _DESTPTR) 		\
	(_TYPE*)memset((_DESTPTR), (_BYTE), (_AMOUNT)*sizeof(_TYPE))
// compare a range of memory blocks data, returns integer values <0, >0 or =0(equal).
#define CUTIL_TYPE_MEMCMP(_TYPE, _AMOUNT, _PTR1, _PTR2)			\
	memcmp((_PTR1), (_PTR2), (_AMOUNT)*sizeof(_TYPE))

/*
* Examples:
	const size_t length = 20; // length of numbers
    uint32_t* aD1 = CUTIL_TYPE_MALLOC(uint32_t, length); // std::vector<uint32_t> v1(20); -> elements == 0xCDCDCDCD in heap
    uint32_t* aD2 = CUTIL_TYPE_CALLOC(uint32_t, length); // std::vector<uint32_t> v1(20, 0x00000000);
	uint32_t aD3[length]; // C99 VLA, unsupported in C++, -> elements == 0xCCCCCCCC in stack
    
    uint32_t* aD3 = CUTIL_TYPE_MEMSET(uint32_t, length, 0x66, aD1); // set all elements of aD1 to 0x66666666, returns aD3 == aD1
    uint32_t* aD4 = CUTIL_TYPE_MEMMOVE(uint32_t, length, aD2, aD1); // copy aD1 elements to aD2, returns aD4==aD2
    uint32_t* aD5 = CUTIL_TYPE_MEMCPY(uint32_t, length, aD2, aD1);  // equivalents to above.
    
    int compResult = CUTIL_TYPE_MEMCMP(uint32_t, length, aD1, aD2); // returns 0, contents of mem blocks equal.
	
	CUTIL_TYPE_FREE(aD1); // element values -> 0xDDDDDDDD (deleted heap)
    CUTIL_TYPE_FREE(aD2);
*/


//===================== C++ Utils ==========================
#ifdef __cplusplus

//* get C++ language standard version, do not add "L" suffix after number
 // in MSVC compiler, __cplusplus always equals to 199711L, but _MSVC_LANG(Prior to VS2015) equals to cpp standard version
#ifdef _MSVC_LANG // example: #if CUTIL_CPP_VER >= 201103L
	#define CUTIL_CPP_VER			_MSVC_LANG	// for MSVC
#else //. !defined _MSVC_LANG
	#define CUTIL_CPP_VER			__cplusplus // for GCC, Clang (also MSVC with the copiler argument "/Zc:__cplusplus")
#endif // _MSVC_LANG
/*
* example:
	#if CUTIL_CPP_VER >= 199711L	// C++98
	#if CUTIL_CPP_VER >= 201103L	// C++11
	#if CUTIL_CPP_VER >= 201402L	// C++14
	#if CUTIL_CPP_VER >= 201703L	// C++17
	#if CUTIL_CPP_VER >= 202002L	// C++20
	#if CUTIL_CPP_VER >= 202302L	// C++23 (temporary not supported)
*/


//* delete a heap pointer, and set it nullptr. arg "p" must be a pointer inited by "new" or "new[]".
#define CUTIL_DELETE_AND_NULL(p)		{delete   p; p = NULL;}
#define CUTIL_DELETE_AND_NULL_ARR(p)	{delete[] p; p = NULL;}
	// keyword "nullptr" is unsupported in C++98


//* set C++11 class constructor/moving/copying to disabled/default
#if CUTIL_CPP_VER >= 201103L 	//* >= C++11
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


//=================== OS Related ========================

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
