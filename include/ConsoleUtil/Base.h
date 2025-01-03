/* UTF-8 encoding
* Project URL: https://github.com/BH2WFR/ConsoleUtil
  Author:		BH2WFR
  Updated:		2 JAN 2025
  License:		MIT License
* You can include this header in header files.
*/
#ifndef CONSOLEUTIL_BASE_H__
#define CONSOLEUTIL_BASE_H__



//* get C++ language standard version
// in MSVC compiler, `__cplusplus` always equals to `199711L` without compiler argument `/Zc:__cplusplus`,
//    but `_MSVC_LANG`(Prior to VS2015) equals to cpp standard version
#ifdef __cplusplus
	#ifdef _MSVC_LANG // example: #if CUTIL_CPP_LANG >= 201103L
		#define CUTIL_CPP_LANG			_MSVC_LANG	// for MSVC
	#else //. !defined _MSVC_LANG
		#define CUTIL_CPP_LANG			__cplusplus // for GCC, Clang (also MSVC with the copiler argument `/Zc:__cplusplus`)
	#endif // _MSVC_LANG
#endif // __cplusplus
#if (CUTIL_CPP_LANG >= 199711L) // >= C++98
	#define CUTIL_CPP98_SUPPORTED	1
#endif
#if (CUTIL_CPP_LANG >= 201103L) // >= C++11
	#define CUTIL_CPP11_SUPPORTED	1
#endif
#if (CUTIL_CPP_LANG >= 201402L) // >= C++14
	#define CUTIL_CPP14_SUPPORTED	1
#endif
#if (CUTIL_CPP_LANG >= 201703L) // >= C++17
	#define CUTIL_CPP17_SUPPORTED	1
#endif
#if (CUTIL_CPP_LANG >= 202002L) // >= C++20
	#define CUTIL_CPP20_SUPPORTED	1
#endif
#if (CUTIL_CPP_LANG >= 202302L) // >= C++23
	#define CUTIL_CPP23_SUPPORTED	1
#endif
/* example:
	#if CUTIL_CPP_LANG >= 199711L	// C++98
	#if CUTIL_CPP_LANG >= 201103L	// C++11
	#if CUTIL_CPP_LANG >= 201402L	// C++14
	#if CUTIL_CPP_LANG >= 201703L	// C++17
	#if CUTIL_CPP_LANG >= 202002L	// C++20
	#if CUTIL_CPP_LANG >= 202302L	// C++23 (temporary not supported)
*/


//* get C language standard version
#ifndef __cplusplus
	#ifdef __STDC_VERSION__
		#define CUTIL_C_LANG	__STDC_VERSION__
	#else // C89 didn't define this macro
		#define CUTIL_C_LANG	198912L
	#endif
#endif //. ! __cplusplus
#if (CUTIL_C_LANG >= 198912L) // >= C89
	#define CUTIL_C89_SUPPORTED	1
#endif
#if (CUTIL_C_LANG >= 199901L) // >= C99
	#define CUTIL_C99_SUPPORTED	1
#endif
#if (CUTIL_C_LANG >= 201112L) // >= C11
	#define CUTIL_C11_SUPPORTED	1
#endif
#if (CUTIL_C_LANG >= 201710L) // >= C17
	#define CUTIL_C17_SUPPORTED	1
#endif
#if (CUTIL_C_LANG >= 202311L) // >= C23
	#define CUTIL_C23_SUPPORTED	1
#endif
/* example:
	#if CUTIL_C_LANG >= 198912L	// C89
	#if CUTIL_C_LANG >= 199901L	// C99
	#if CUTIL_C_LANG >= 201112L	// C11
	#if CUTIL_C_LANG >= 201710L	// C17
	#if CUTIL_C_LANG >= 202311L	// C23
*/


//* ==== Environment Check, `> C99/C++11` with `##__VA_ARGS__` extension (available in MSVC(>VS2015 U3)/GCC/Clang)
#if (!defined(__cplusplus)) && !defined(CUTIL_C99_SUPPORTED)
	#error This Header DO NOT SUPPORTS C89! - >=C99 or C++ Required.
#elif defined(__cplusplus) && !defined(CUTIL_CPP11_SUPPORTED)
	#error This Header DO NOT SUPPORTS C++98! - >=C++14 Required.
#else
	// available
#endif


//* include vital C headers
#ifdef __cplusplus
	#include <cstdio>
	#include <cstdlib>
	#include <cstdint>
	#include <cfloat>
	#include <limits> // for epsilon of float
#else //. !__cplusplus
	#include <stdio.h>
	#include <stdlib.h>
	#include <stdint.h>	// uint32_t
	#include <float.h>	// floating-point limits
	#if defined(CUTIL_C99_SUPPORTED) && !defined(CUTIL_C23_SUPPORTED)
		#include <stdbool.h> // bool support since C99, before C23 (became keyword)
	#endif
#endif // __cplusplus


//* C++ namespace
#ifndef CUTIL_PARAM_USE_SHORTEN_NAMESPACE
	#define CUTIL_PARAM_USE_SHORTEN_NAMESPACE 1	//* use shorter namespace `cu::` instead of `cutil::`
#endif // CUTIL_PARAM_USE_SHORTEN_NAMESPACE
#ifdef __cplusplus
	#if (CUTIL_PARAM_USE_SHORTEN_NAMESPACE)
		#define _CUTIL_REDIFINE_SHORTER_NAMESPACE	namespace cu = cutil;
	#else
		#define _CUTIL_REDIFINE_SHORTER_NAMESPACE
	#endif
	#define _CUTIL_NAMESPACE_BEGIN					namespace cutil {
	#define _CUTIL_NAMESPACE_END					} _CUTIL_REDIFINE_SHORTER_NAMESPACE
	#define _CUTIL_NAMESPACE_BEGIN_NAME(_NAME)		namespace _NAME {
	#define _CUTIL_NAMESPACE_END_NAME(_NAME)		}
#else  // C
	#define _CUTIL_REDIFINE_SHORTER_NAMESPACE
	#define _CUTIL_NAMESPACE_BEGIN
	#define _CUTIL_NAMESPACE_END
	#define _CUTIL_NAMESPACE_BEGIN_NAME(_NAME)
	#define _CUTIL_NAMESPACE_END_NAME(_NAME)
#endif // defined __cplusplus


//* constexpr function
#ifdef CUTIL_CPP17_SUPPORTED // C++17
	#define _CUTIL_CONSTEXPR_CPP17	constexpr
#else
	#define _CUTIL_CONSTEXPR_CPP17
#endif
#if defined(CUTIL_CPP14_SUPPORTED) || (defined(__cpp_constexpr) && __cpp_constexpr >= 201304) // C++14
	#define _CUTIL_CONSTEXPR_CPP14	constexpr
#else
	#define _CUTIL_CONSTEXPR_CPP14
#endif


//* attributes
#ifdef CUTIL_CPP17_SUPPORTED // C++17
	#define _CUTIL_NODISCARD	[[nodiscard]]
	#define _CUTIL_MAYBE_UNUSED	[[maybe_unused]]
#else
	#define _CUTIL_NODISCARD
	#define _CUTIL_MAYBE_UNUSED
#endif
#ifdef CUTIL_CPP14_SUPPORTED // C+14
	#define _CUTIL_DEPRECATED	[[deprecated]]
#else
	#define _CUTIL_DEPRECATED
#endif


//* assert in constexpr function
#ifdef CUTIL_CPP14_SUPPORTED // C++14
	#define _CUTIL_CONSTEXPR_ASSERT(_EXPR)	assert(_EXPR)
#else
	#define _CUTIL_CONSTEXPR_ASSERT(_EXPR)
#endif


//* get decayed type of variable, only for GNU C, C23, C++11
#ifndef __cplusplus // C
	#if defined(__GNUC__) || defined(CUTIL_C23_SUPPORTED)
		#define CUTIL_TYPEOF(_VAR)	typeof(_VAR)	// only for GNU C, and C23.
	#endif
#else // C++		// C++11
	#ifdef CUTIL_CPP11_SUPPORTED 	//* >= C++11
		#define CUTIL_TYPEOF(_VAR)	std::decay<decltype(_VAR)>::type
		// int& -> int; const int -> int; const int* const -> const int*; int[] -> int*;
	#endif
#endif //. ! __cplusplus


#endif /* CONSOLEUTIL_BASE_H__ */
