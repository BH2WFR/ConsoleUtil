/*    UTF-8 encoding
	* Project URL: https://github.com/BH2WFR/ConsoleUtil
	* Author:		BH2WFR
	
	* If libs like fmtlib or Qt also included in source file, pls #include their headers FIRST, then #include this header.
	* 引用说明: 若源文件使用了 fmtlib 或 Qt 等库, 请先 #include 这些头文件, 最后再 #include 此头文件.
*/
#ifndef CONSOLE_UTIL_H__
#define CONSOLE_UTIL_H__

#define CONSOLE_UTIL_VER	3


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


//* ==== customize parameters:
	// #define CONSOLE_UTIL_ANSI_UTIL_UNSUPPORTED	1  // set 0 to disable style changing



//====================== CONSOLE CUSTOMIZING MACROS =========================
//* reference:    https://en.wikipedia.org/wiki/ANSI_escape_code
			   // https://zh.wikipedia.org/wiki/ANSI%E8%BD%AC%E4%B9%89%E5%BA%8F%E5%88%97
			   
//* WARNING:  Windows built-in command-line tools in versions prior to Windows 10 1511 do not support this feature.
//		If font or color customizing features is needed in Windows 7 or prior system, pls use SetConsoleTextAttribute() function.

#if (CONSOLE_UTIL_ANSI_UTIL_UNSUPPORTED == 0) // || (WINVER >= 0x0A00)
	#define CAnsiEsc(_STR)		"\033[" _STR
	#define CAnsiEscStr(_STR)	_STR
#else
	#define CAnsiEsc(_STR)	// Windows 7 or older version do not supports "\033[" ANSI Escape code
	#define CAnsiEscStr(_STR)
#endif


//* RESET color formatting and font styles to DEFAULT, you must add this after customizing font color
	#define CReset 		CAnsiEsc("0m")
	#define CRst		CReset 		// alias
	#define CStyle(_STYLE, _STR)	_STYLE _STR CReset
	// example: printf(FYellow BBlue "yellow text" CRst);

//* font foreground colors
// dark font color series
	#define FBlack		CAnsiEsc("30m")
	#define FRed 		CAnsiEsc("31m")
	#define FGreen 		CAnsiEsc("32m")
	#define FYellow		CAnsiEsc("33m")	// in some terminals, it renders like brown.
	#define FBlue		CAnsiEsc("34m")
	#define FMagenta	CAnsiEsc("35m")
	#define FCyan		CAnsiEsc("36m")
	#define FWhite		CAnsiEsc("37m")
	
// light font color series
	#define FLBlack		CAnsiEsc("90m")	// it's gray.
	#define FLRed 		CAnsiEsc("91m")
	#define FLGreen 	CAnsiEsc("92m")
	#define FLYellow 	CAnsiEsc("93m")
	#define FLBlue 		CAnsiEsc("94m")
	#define FLMagenta 	CAnsiEsc("95m")
	#define FLCyan 		CAnsiEsc("96m")
	#define FLWhite 	CAnsiEsc("97m")
	#define FGray		FLBlack 	// equals to "CLBlack"
	#define FGrey		FLBlack
	
// font color: custom RGB values CRGB
	#define FRgb(R, G, B)	CAnsiEsc("38;2;" #R ";" #G ";" #B "m")
	#define FCode(C)		CAnsiEsc("38;5;"#C"m") // 8-bit color code, supports 0-15, 16-231, 232-255
	#define FDefault		CAnsiEsc("39m") 	// default foreground color

//* font background colors, can be combined with foreground colors
// dark font background color series
	#define BBlack		CAnsiEsc("40m")
	#define BRed 		CAnsiEsc("41m")
	#define BGreen 		CAnsiEsc("42m")
	#define BYellow		CAnsiEsc("43m")
	#define BBlue		CAnsiEsc("44m")
	#define BMagenta	CAnsiEsc("45m")
	#define BCyan		CAnsiEsc("46m")
	#define BWhite		CAnsiEsc("47m")
	
// light font background color series
	#define BLBlack		CAnsiEsc("100m")  // actually it's gray
	#define BLRed 		CAnsiEsc("101m")
	#define BLGreen 	CAnsiEsc("102m")
	#define BLYellow	CAnsiEsc("103m")
	#define BLBlue		CAnsiEsc("104m")
	#define BLMagenta	CAnsiEsc("105m")
	#define BLCyan		CAnsiEsc("106m")
	#define BLWhite		CAnsiEsc("107m")
	#define BGray		BLBlack	 // equals to "BLBlack"
	#define BGrey		BLBlack
	
// font background color: custom RGB values
	#define BRgb(R, G, B)	CAnsiEsc("48;2;" #R ";" #G ";" #B "m")
	#define BColor(C)		CAnsiEsc("48;5;"#C"m") // 8-bit color code, supports 0-15, 16-231, 232-255
	#define BDefault		CAnsiEsc("49m") 	// default background color

//* font styles
	#define CBold			CAnsiEsc("1m")	// 加粗
	#define CWeak			CAnsiEsc("2m")	// 变暗
	#define CItalic			CAnsiEsc("3m")	// 斜体
	#define CUnderLine		CAnsiEsc("4m")	// 下划线
	#define CFlash			CAnsiEsc("5m")	// 闪烁
	#define CQFlash			CAnsiEsc("6m")	// quick flashing
	#define CInvert			CAnsiEsc("7m")	// Swap foreground and background colors
	#define CHide			CAnsiEsc("8m")	// Hide or Conceal
	// actually, "\033[1;31m" means bold and red text, these props can be stacked in this way.
	
	#define CDblUnderline	CAnsiEsc("21m")
	#define CNotUnderline	CAnsiEsc("24m")
	
//=== special foreground and background color combinations
	#define CTurn 			CAnsiEsc("107;30m")	// 白底黑字, white text on a black background
	#define CLYelBold 		CAnsiEsc("1;93m")	// bold, and light yellow
	#define CInvLYel		CAnsiEsc("1;30;103m")
	#define CLRedBold		CAnsiEsc("1;91m")
	#define CLightBold		CAnsiEsc("1;97;100m")
	#define CInvBold		CAnsiEsc("1;30;107m")

	
//* Cursor control
	#define CUp(n)			CAnsiEsc(#n"A") // cursor Up:   Moves the cursor n (default 1) cells in the given direction.
	#define CDown(n)		CAnsiEsc(#n"B") // cursor Down: e.g. std::cout << CDown("2") // moves cursor 2 cells down
	#define CForward(n)		CAnsiEsc(#n"C") // cursor Forward:
	#define CBack(n)		CAnsiEsc(#n"D") // cursor Back
	#define CFwd(n)			CForward(n)  // alias

	#define CNextLn(n)		CAnsiEsc(#n"E") // Moves cursor to beginning of the line n (default 1) lines down
	#define CPrevLn(n)		CAnsiEsc(#n"F") // Moves cursor to beginning of the line n (default 1) lines up.
	#define CHorzPos(n)		CAnsiEsc(#n"G") // Moves the cursor to column n (default 1, absolute).

	#define CCursorPos(x, y) CAnsiEsc(#x";"#y"H") // Moves the cursor to row n, column m
	#define CPos(x, y) 		 CCursorPos(x, y) // alias

//* clear the screen or line
	#define CClear(n)		CAnsiEsc(#n"J") //  If the cursor is already at the edge of the screen, this has no effect.
	#define CClearAfter		CClear(0)   // clear from cursor to end of screen
	#define CClearBefore	CClear(1)   // clear from cursor to beginning of the screen
	#define CClearScr		CClear(2) 	// clear screen(console), and moves cursor to upper left on DOS ANSI.SYS.
	#define CClearAll		CClear(3) 	// erase screen(console), and delete all lines saved in the scrollback buffer


	#define CEraseLn(n)		CAnsiEsc(#n"K") // Erases part of the line. Cursor position does not change.
	#define CEraseLnAfter	CEraseLn(0)  // clear from cursor to the end of the line
	#define CEraseLnBefore	CEraseLn(1)  // clear from cursor to beginning of the line
	#define CEraseLnAll		CEraseLn(2)  // clear entire line

//* scroll control
	#define CScrollUp(n)	CAnsiEsc(#n"S") // Scroll whole page up by n (default 1) lines. New lines are added at the bottom.
	#define CScrollDn(n)	CAnsiEsc(#n"T") // Scroll whole page down by n (default 1) lines. New lines are added at the top.
	
	#define CSaveCursorPos	CAnsiEsc("s")
	#define CReadCursorPos  CAnsiEsc("u")
	
	#define CShowCursor		CAnsiEscStr("\033?25h")
	#define CHideCursor		CAnsiEscStr("\033?25l")


//* ==============================================================


//* macros for console window/application and streams
#if defined(_WIN32) || defined(WIN32) || defined(__WIN32) && !defined(__CYGWIN__) // in Windows
	#define CUTIL_ENCODING_CHCP(_NUM)	system("chcp "#_NUM);	//  custom chcp encoding (number) in Windows
	#define CUTIL_CLEAR()		system("cls");			//  clear the screen (console)
	#define CUTIL_SIZE(X, Y) 	system("mode con cols=" #X "lines=" #Y); // set console window size
	#define CUTIL_PAUSE()		system("pause");		// pause the console application

#else 	// in Linux/MacOS
	#define CUTIL_ENCODING_CHCP(_NUM)
	#define CUTIL_CLEAR()		system("clear"); 		//  clear the screen (console)
	#define CUTIL_SIZE(X, Y)
	#define CUTIL_PAUSE()		getchar();				// pause the console application
	
#endif


//* Flush the input buffer to ensure that subsequent "scanf()" or "cin" calls receive valid input.
#define CUTIL_FLUSH_INPUTBUFFER()	{char ch; while((ch = getchar()) != '\n') continue;}
	// 吸收输入缓存区内的其余字符, 以便下次 scanf 或 cin 时能够获取到正确的输入内容

//* Set Console Encoding by "chcp" command in Windows
#define CUTIL_ENCODING_UTF8()       CUTIL_ENCODING_CHCP(65001);   //* set console encoding to UTF-8 in windows
#define CUTIL_ENCODING_GB2312()     CUTIL_ENCODING_CHCP(936);     //  Simp. Chinese, or 54936 for GB18030
#define CUTIL_ENCODING_BIG5()       CUTIL_ENCODING_CHCP(950);     //  Trad. Chinese
#define CUTIL_ENCODING_KOR()        CUTIL_ENCODING_CHCP(949);     //  Korean
#define CUTIL_ENCODING_JIS()        CUTIL_ENCODING_CHCP(932);     //  Shift_JIS,
#define CUTIL_ENCODING_LATIN1()     CUTIL_ENCODING_CHCP(850);     //  Latin 1 multilingual
#define CUTIL_ENCODING_LATIN2()     CUTIL_ENCODING_CHCP(852);     //  Latin 2 multilingual (Slavic)
#define CUTIL_ENCODING_CYR()        CUTIL_ENCODING_CHCP(855);     //  Cyrillic / Russian
#define CUTIL_ENCODING_WIN1250()    CUTIL_ENCODING_CHCP(1250);    //  windows 1250, Central European
#define CUTIL_ENCODING_WIN1251()    CUTIL_ENCODING_CHCP(1251);    //  windows 1251, Cyrillic
#define CUTIL_ENCODING_WIN1252()    CUTIL_ENCODING_CHCP(1252);    //  windows 1252, western European


//* features with win32api
#if defined(_WINDOWS_) || defined(WINAPI)
	#define CUTIL_TITLE(_STR)			SetConsoleTitleA(_STR);        // set console title in windows
	#define CUTIL_CURSOR_POS(x, y)	\
		{COORD pos; pos.X=x; pos.Y=y;   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);}
	#define CUTIL_CONSOLE_ATTR(_ATTR)	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (_ATTR));
	#define CONSOLE_RESET_STYLE()		CUTIL_SET_CONSOLE_ATTR(0)
	
//#else // without win32api, or in Linux
#elif (CONSOLE_UTIL_ANSI_UTIL_UNSUPPORTED == 0) // without win32api, or in Linux
	#define CUTIL_TITLE(_STR)			printf("\033]0;%s\007", _STR); // set console title in linux
	#define CUTIL_CURSOR_POS(x, y)		printf(CCursorPos(x, y));
	#define CUTIL_CONSOLE_ATTR(_ATTR)
	#define CONSOLE_RESET_STYLE()		printf(CReset);
	
#else
	#define CUTIL_TITLE(_STR)
	#define CUTIL_CURSOR_POS(x, y)
	#define CUTIL_CONSOLE_ATTR(_ATTR)
	#define CONSOLE_RESET_STYLE()
	
#endif


/*
* Instruction:
	#include <print.h>			// C++23
	#include <windows.h>		// include other headers first
	#include <fmt/core.h>		// include other headers first
	
	#include <ConsoleUtil.h> 	// include this header at last
	
	int main(int argc, char* argv[]){
		CUTIL_ENCODING_UTF8(); 		// switch console encoding to UTF-8 (windows)
		CUTIL_TITLE("MyProject"); 	// set console window title
		CUTIL_SIZE(100, 30);		// set console window size to with of 30 chars and height of 30 lines.
		CUTIL_CLEAR();				// clear console (system("cls"))
		
		CUTIL_PRINT_ARGV(argc, argv);	// print all argc and argv[n] of main() function
		
		printf(FLGreen "Hello World!\n" CReset);   // print "Hello World" with light yellow console color formatting
														you should put "CReset" at the end of string to RESET console font color to DEFAULT
		printf(CStyle(FLGreen, "Hello World!\n")); // Equivalent
		
		std::cout << FLRed "ERROR\n" CReset;  // print "ERROR" with font color light red, "CReset" is also needed to revert font color to default
		std::cout << CStyle(FLRed, "ERROR\n");// Equivalent
		
		printf(BRed FGreen CQFlash "test\n" CReset);  // Print text with green font and red background, and quickly flashing
		printf(CStyle(BRed FGreen CQFlash, "test\n"));// Equivalent
		
		
		printf(CForward(2)); // move thr cursor 2 characters right
		
		
		CUTIL_PRINT_ERR("error occured!"); // print an error message with filename, function name and line number ATTACHED.
		
		CUTIL_PAUSE(); 			 // system("pause");
		
		return 0;
	}

*/



//===================== C++ Utils ==========================
#ifdef __cplusplus

//* get C++ language standard version, do not add "L" suffix after number
 // in MSVC compiler, __cplusplus always equals to 199711L, but _MSVC_LANG(Prior to VS2015) equals to cpp standard version
#ifdef _MSVC_LANG // example: #if CUTIL_CPP_VER_HIGHER_EQUAL_THAN(201103)
	#define CUTIL_CPP_VER_HIGHER_EQUAL_THAN(_VER) \
		( (defined __cplusplus) && (_MSVC_LANG >= _VER##L) )
	#define CUTIL_CPP_VER_LOWER_THAN(_VER) \
		( (defined __cplusplus) && (_MSVC_LANG <  _VER##L) )
#else //. !defined _MSVC_LANG
	#define CUTIL_CPP_VER_HIGHER_EQUAL_THAN(_VER) \
		(__cplusplus >= _VER##L)
	#define CUTIL_CPP_VER_LOWER_THAN(_VER) \
		(__cplusplus <  _VER##L)
#endif // _MSVC_LANG
/*
* example:
	#if CUTIL_CPP_VER_HIGHER_EQUAL_THAN(199711) 	// do not add "L" after number
	#if CUTIL_CPP_VER_HIGHER_EQUAL_THAN(201103)	// C++11
	#if CUTIL_CPP_VER_HIGHER_EQUAL_THAN(201402)	// C++14
	#if CUTIL_CPP_VER_HIGHER_EQUAL_THAN(201703)	// C++17
	#if CUTIL_CPP_VER_HIGHER_EQUAL_THAN(202002)	// C++20
	#if CUTIL_CPP_VER_HIGHER_EQUAL_THAN(202302)	// C++23 (temporary not supported)
*/


//* delete a heap pointer, and set it nullptr. arg "p" must be a pointer inited by "new" or "new[]".
#define CUTIL_DELETE_AND_NULL(p)		{delete   p; p = NULL;}
#define CUTIL_DELETE_AND_NULL_ARR(p)	{delete[] p; p = NULL;}


#endif // __cplusplus


//============= PROGRAM DEBUGGING: Print Args/Error Messages ===============

//* detect Debug Build or Release Build
#if (defined(_DEBUG) || defined(IS_DEBUG) || defined(DEBUG)) && !(defined(NDEBUG) || defined(_NDEBUG))
	#define CUTIL_GET_IS_DEBUG_BUILD 	 1
#else // defined(NDEBUG)
	#define CUTIL_GET_IS_DEBUG_BUILD 	 0
#endif
// example: #if CUTIL_GET_IS_DEBUG_BUILD

//* print all argc and argv[n] arguments for main(int argc, char* argv[]) function
#define CUTIL_PRINT_ARGV(_argc, _argv) { \
		printf(CReset "\n"); \
		printf(FBlack BLYellow FLYellow CBold "====== Print Program params, all " FLRed "argc" FBlack " and " FLRed "argv[i]" FBlack " =====" CReset "\n");\
		printf(FLMagenta "    argc:   " FLWhite "%d\n", (_argc)); \
		printf(FLGreen   "    argv[  0]: " FLBlue "%.256s\n", (_argv)[0]); \
		for(int i = 1; i < (_argc); i++) { \
			printf(FLYellow "    argv[%3d]: " FLCyan "%.256s\n", i, (_argv)[i]); \
		} \
		printf(CReset "\n"); \
	}
		
//* print an error message with filename, function name and line number ATTACHED.
#define CUTIL_PRINT_ERR(_STR) \
	printf(FLRed "\n=============== ERROR: " FLYellow _STR FLRed "\n" \
				"    file: " __FILE__ "\n" \
				"    func: %s\n" \
				"    line: %d\n\n" CReset \
			, __func__, __LINE__);


// print an error message, and force abort application.
#define CUTIL_ABORT_ERR(_STR) 	 	{CUTIL_PRINT_ERR(_STR); exit(-1);}
#define CUTIL_ABORT_ERR_ASM(_STR) 	{CUTIL_PRINT_ERR(_STR); asm("exit");}


//* bit calculating macros
#define CUTIL_GET_BIT(_NUM, BIT_IDX)	((_NUM) & (1u << (BIT_IDX)))	// if bit is 1, returns (1<<BIT_IDX), NOT 1
#define CUTIL_SET_BIT(_NUM, BIT_IDX)	((_NUM) |=  (1u << (BIT_IDX)));	// must use them in separate lines
#define CUTIL_CLEAR_BIT(_NUM, BIT_IDX)	((_NUM) &= ~(1u << (BIT_IDX)));
#define CUTIL_TOGGLE_BIT(_NUM, BIT_IDX)	((_NUM) ^=  (1u << (BIT_IDX)));


//* swap items, only for C, do not use in C++ (use std::swap())
#define CUTIL_SWAP_VARS(_VAR1, _VAR2, _TYPE) {_TYPE sw = _VAR2; _VAR2 = _VAR1; _VAR1 = sw;}
#define CUTIL_SWAP_VARS_GNU(_VAR1, _VAR2)	 {typeof(_VAR1) sw = _VAR2; _VAR2 = _VAR1; _VAR1 = sw;} // GNU C only
	// CUTIL_SWAP_VARS(int, a, b);


//* macros for print something ONLY IN DEBUG BUILD
#if CUTIL_GET_IS_DEBUG_BUILD // print in Debug Build
	#if defined(FMT_VERSION) && defined(__cplusplus) // fmt::print(), fmt::println()
		#define CUTIL_DEBUG_PRINT(_STR, ...)	   fmt::print(_STR, ##__VA_ARGS__);
		#define CUTIL_DEBUG_PRINTLN(_STR, ...)	   fmt::println(_STR, ##__VA_ARGS__);
	#elif CUTIL_CPP_VER_HIGHER_EQUAL_THAN(202302) // C++23 std::print(), std::println()
		#if __has_include(<print>) // C++17 support, && (defined(_PRINT_) || defined(_GLIBCXX_PRINT)
			#define CUTIL_DEBUG_PRINT(_STR, ...)   std::print(_STR, ##__VA_ARGS__);
			#define CUTIL_DEBUG_PRINTLN(_STR, ...) std::println(_STR, ##__VA_ARGS__);
		#else // no fmtlib, and after C++23
			#define CUTIL_DEBUG_PRINT(_STR, ...)
			#define CUTIL_DEBUG_PRINTLN(_STR, ...)
		#endif
	#else // no fmtlib, and before C++23
		#define CUTIL_DEBUG_PRINT(_STR, ...)
		#define CUTIL_DEBUG_PRINTLN(_STR, ...)
	#endif // _PRINT_
	
	// for std::cout, and printf()
	#define CUTIL_DEBUG_COUT(...)			 std::cout << __VA_ARGS__;
	#define CUTIL_DEBUG_COUTLN(...)			 std::cout << __VA_ARGS__ << '\n';
	
	#define CUTIL_DEBUG_PRINTF(_STR, ...)    printf(_STR, ##__VA_ARGS__);
	#define CUTIL_DEBUG_PRINTFLN(_STR, ...)  printf(_STR "\n", ##__VA_ARGS__);
	
#else // Do nothing in Release Build
	#define CUTIL_DEBUG_PRINT(_STR, ...)
	#define CUTIL_DEBUG_PRINTLN(_STR, ...)
	
	#define CUTIL_DEBUG_COUT(...)
	#define CUTIL_DEBUG_COUTLN(...)
	
	#define CUTIL_DEBUG_PRINTF(_STR, ...)
	#define CUTIL_DEBUG_PRINTFLN(_STR, ...)
	
#endif // CUTIL_GET_IS_DEBUG_BUILD
/* instruction:
	if you want to print some debug message to console, and only do this in DEBUG BUILD,
	use these macros above, they will do nothing in release build.
* example:
	CUTIL_DEBUG_COUT("this is: " << 5); // expand to std::cout in debug build, and nothing in release build
	CUTIL_DEBUG_COUTLN("");             // with a line break ( << '\n')
	CUTIL_DEBUG_PRINTLN("this is {}", 5); // expand to fmt::println(if you include fmtlib headers above
										this header include), or std::println(C++23)
	CUTIL_DEBUG_PRINTF("this is %d", 5); // expand to printf in debug build
*/



//===================== Qt Utils ==========================
#if defined(QT_VERSION) && defined(__cplusplus)
//* you need to #include Qt Headers first before #include of this header.

//* Qt5 high DPI support since Qt5.6, and fractional scaling support since Qt5.14
//  in Qt6, high DPI and fractional scaling support is enabled by default and no need for this macro.
//  pls #include<QApplication> first before #include of this header.
#if ((QT_VERSION >= QT_VERSION_CHECK(5,6,0)) && (QT_VERSION < QT_VERSION_CHECK(5,14,0)))
	#define CUTIL_QT5_HIGH_DPI() \
		QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling); \
		QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
		
#elif ((QT_VERSION >= QT_VERSION_CHECK(5,14,0)) && (QT_VERSION < QT_VERSION_CHECK(6,0,0)))
	#define CUTIL_QT5_HIGH_DPI() \
		QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling); \
		QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps); \
		QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
		
#else // QT_VERSION ( >= 6.0.0 || <= 5.5.0 )
	#define CUTIL_QT5_HIGH_DPI()
	
#endif // QT_VERSION

//* Set QTextCodec default encoding to UTF-8,
//  or cannot correctly print chinese characters via qDebug() if code is saved in UTF-8 encoding;
//  pls #include<QTextCodec> first before #include of this header.
//  in MSVC Compiler, compiler argument "/utf-8" is required if code is saved in UTF-8 encoding;
//  	in CMake, you should add "set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")"
//  In Qt6, QTextCodec module is deleted and contained in Qt5 Compatibility Module.
#if defined(QTEXTCODEC_H)
	#define CUTIL_QT5_TEXTCODEC_SET(_STR)	QTextCodec::setCodecForLocale(QTextCodec::codecForName(_STR));
#else //. !QTEXTCODEC_H
	#define CUTIL_QT5_TEXTCODEC_SET(_STR)
#endif // QTEXTCODEC_H

#define CUTIL_QT5_TEXTCODEC_UTF8()		CUTIL_QT5_TEXTCODEC_SET("UTF-8");
#define CUTIL_QT5_TEXTCODEC_GBK()		CUTIL_QT5_TEXTCODEC_SET("GB18030");
#define CUTIL_QT5_TEXTCODEC_BIG5()		CUTIL_QT5_TEXTCODEC_SET("Big5");
#define CUTIL_QT5_TEXTCODEC_EUCKR()		CUTIL_QT5_TEXTCODEC_SET("EUC-KR");
#define CUTIL_QT5_TEXTCODEC_EUCJP()		CUTIL_QT5_TEXTCODEC_SET("EUC-JP");
#define CUTIL_QT5_TEXTCODEC_JIS()		CUTIL_QT5_TEXTCODEC_SET("Shift-JIS");


//* qDebug() without spaces or quotes
//  pls #include<QDebug> first before this header #include
#ifdef QDEBUG_H
	#define CUTIL_QDEBUG_N  qDebug().noquote() 		  	 // qDebug() without quotes
	#define CUTIL_QDEBUG_NN qDebug().nospace().noquote() // qDebug() without spaces and quotes
		// example: CUTIL_QDEBUG_N << "test" << 1;
	
#endif

/*
* example:
	#include <qglobal.h>
	#include <QApplication>
	#include <QDebug>
	#include <QTextCodec> // include Qt headers first
	
	#include <ConsoleUtil.h> // include this header at last
	
	int main(int argc, char* argv[])
	{
		CUTIL_QT5_HIGH_DPI(); 	  	//* use Qt5 high DPI support
		
		CUTIL_ENCODING_UTF8();
		CUTIL_QT5_TEXTCODEC_UTF8(); //* set Qt default text encoding to UTF-8
		
		QApplication app(argc, argv);
		
		return app.exec();
	}
*/





#endif // QT_VERSION


//==================== CUDA Utils ==========================
#ifdef __CUDA_RUNTIME_H__ //* CUDA 错误检查与退出机制

#define CUTIL_CUDA_PRINT_ERR(_STR) \
		printf(FLRed "\n=============== CUDA ERROR = %d: " _STR "\n" \
					"    file: " __FILE__ "\n" \
					"    func: %s\n" \
					"    line: %d\n" CReset \
				, err, __func__, __LINE__);
	
// 进行 cuda 部分操作后, 将返回值传入此宏定义中, 如果执行失败, 则输出信息, 并退出当前函数, 第三个参数为 return 值, void 则不填写
#define CUTIL_CUDA_RETURN_IF_ERR(_ERR, _STR, ...) \
	if (_ERR != cudaSuccess) { \
		CUTIL_CUDA_PRINT_ERR(_STR); \
		return __VA_ARGS__; \
	}

// 进行 cuda 部分操作后, 将返回值传入此宏定义中, 如果执行失败, 则输出信息并强行停止程序
#define CUTIL_CUDA_ABORT_IF_ERR(_ERR, _STR, _RET) \
	if (_ERR != cudaSuccess) { \
		CUTIL_CUDA_PRINT_ERR(_STR) \
		exit(_RET); \
	}

#endif //__CUDA_RUNTIME_H__







#endif // CONSOLE_UTIL_H__
