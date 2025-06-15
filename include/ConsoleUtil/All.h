/* UTF-8 encoding
* Project URL: https://github.com/BH2WFR/ConsoleUtil
  Author:		BH2WFR
  Updated:		2 JAN 2025
  License:		MIT License
* You can include this header in header files.
*/
#ifndef CONSOLEUTIL_ALL_H__
#define CONSOLEUTIL_ALL_H__

//* core header
#include <ConsoleUtil/Base.h>

//* console util
#include <ConsoleUtil/ConsoleUtil.h>

//* c util (macros)
#include <ConsoleUtil/CUtil.h>
#include <ConsoleUtil/CudaUtil.h>

#ifdef __cplusplus
	//* cpp util
	#include <ConsoleUtil/CppBase.hpp>
	#include <ConsoleUtil/CppUtil.hpp>
	#include <ConsoleUtil/CppBit.hpp>
	#include <ConsoleUtil/CppMath.hpp>
	#include <ConsoleUtil/CppScopeGuard.hpp>
	#include <ConsoleUtil/CppStringUtil.hpp>
	#include <ConsoleUtil/QtUtil.hpp>
	
	//* external headers
	#include <ConsoleUtil/External/Span.hpp>
	
	#ifdef CUTIL_CPP17_SUPPORTED
		#include <ConsoleUtil/External/XorStr.hpp>
		
		#include "ConsoleUtil/External/MagicEnum/magic_enum.hpp"
		// #include "ConsoleUtil/External/MagicEnum/magic_enum_containers.hpp"
		// #include "ConsoleUtil/External/MagicEnum/magic_enum_flags.hpp"
		// #include "ConsoleUtil/External/MagicEnum/magic_enum_format.hpp"
		// #include "ConsoleUtil/External/MagicEnum/magic_enum_fuse.hpp"
		// #include "ConsoleUtil/External/MagicEnum/magic_enum_iostream.hpp"
		// #include "ConsoleUtil/External/MagicEnum/magic_enum_switch.hpp"
		// #include "ConsoleUtil/External/MagicEnum/magic_enum_utility.hpp"
	#endif // C++17
	
#endif // __cplusplus


#endif /* CONSOLEUTIL_ALL_H__ */
