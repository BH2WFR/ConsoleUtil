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
	#include <ConsoleUtil/CppUtil.h>
	#include <ConsoleUtil/QtUtil.h>
	
	//* external headers
	#include <ConsoleUtil/External/ScopeGuard.h>
	#include <ConsoleUtil/External/Span.h>
	#include <ConsoleUtil/External/StringUtil.h>
	#include <ConsoleUtil/External/XorStr.h>
#endif // __cplusplus


#endif /* CONSOLEUTIL_ALL_H__ */
