/*    UTF-8 encoding
	* Project URL: https://github.com/BH2WFR/ConsoleUtil
	* Author:		BH2WFR
	* 引用说明: 若源文件使用了 fmtlib 或 Qt 等库, 请先 #include 这些头文件, 再 #include 此头文件.
	* If libs like fmtlib or Qt also included in source file, pls #include their headers FIRST, then #include this header.
*/
#ifndef CONSOLE_UTIL_H__
#define CONSOLE_UTIL_H__

#define CONSOLE_UTIL_VER	1

#define CONSOLE_UTIL_USE_DEPRECATED	  0  //* using deprecated macros


#ifdef __cplusplus // include vital C headers
	#include <cstdio>
	#include <cstdlib>
	#include <cstdint>
#else //. !__cplusplus
	#include <stdio.h>
	#include <stdlib.h>
	#include <stdint.h>
	#include <stdbool.h>
#endif // __cplusplus


// include winapi headers
// #if defined(_WIN32) || defined(WIN32) || defined(__WIN32)
// 	#include <windows.h>
// #endif // WinAPI 适配


// #ifdef _MSC_VER
// 	#pragma warning( disable: 4003 4996 )
// #endif



//====================== CONSOLE COSTOMIZING MACROS =========================

//* RESET color formatting and font styles to DEFAULT, you must add this after customizing font color
	#define CReset 		"\033[0m"
	#define CRst		CReset 		// alias
	#define CStyle(_STYLE, _STR)	_STYLE _STR CReset
	// example: printf(FYellow BBlue "yellow text" CRst);

//* font foreground colors
// dark font color series
	#define FBlack		"\033[30m"
	#define FRed 		"\033[31m"
	#define FGreen 		"\033[32m"
	#define FYellow		"\033[33m"
	#define FBlue		"\033[34m"
	#define FMagenta	"\033[35m"
	#define FCyan		"\033[36m"
	#define FWhite		"\033[37m"
	#define FBrown		FYellow  	// equals to "FYellow"
	
// light font color series
	#define FLBlack		"\033[90m"	// it's gray
	#define FLRed 		"\033[91m"
	#define FLGreen 	"\033[92m"
	#define FLYellow 	"\033[93m"
	#define FLBlue 		"\033[94m"
	#define FLMagenta 	"\033[95m"
	#define FLCyan 		"\033[96m"
	#define FLWhite 	"\033[97m"
	#define FGray		FLBlack 	// equls to "CLBlack"
	
// font color: custom RGB values CRGB
	#define FRgb(R, G, B)	"\033[38;2;" #R ";" #G ";" #B "m"
	#define FCode(C)		"\033[38;5;"#C"m" // 8-bit color code, supports 0-15, 16-231, 232-255


//* font background colors, can be combined with foreground colors
// dark font background color series
	#define BBlack		"\033[40m"
	#define BRed 		"\033[41m"
	#define BGreen 		"\033[42m"
	#define BYellow		"\033[43m"
	#define BBlue		"\033[44m"
	#define BMagenta	"\033[45m"
	#define BCyan		"\033[46m"
	#define BWhite		"\033[47m"
	#define BBrown		BYellow	// equals to "BYellow"
	
// light font background color series
	#define BLBlack		"\033[100m"  // actually it's gray
	#define BLRed 		"\033[101m"
	#define BLGreen 	"\033[102m"
	#define BLYellow	"\033[103m"
	#define BLBlue		"\033[104m"
	#define BLMagenta	"\033[105m"
	#define BLCyan		"\033[106m"
	#define BLWhite		"\033[107m"
	#define BGray		BLBlack	 // equals to "BLBlack"
	
// font background color: custom RGB values
	#define BRgb(R, G, B)	"\033[48;2;" #R ";" #G ";" #B "m"
	#define BColor(C)		"\033[48;5;"#C"m" // 8-bit color code, supports 0-15, 16-231, 232-255

//* special foreground and background color pairs
	#define CTurn 		"\033[107;30m"	// 白底黑字, white text on a black background


//* font styles
	#define CBold		"\033[1m"	// 加粗
	#define CWeak		"\033[2m"	// 变暗
	#define CItalic		"\033[3m"	// 斜体
	#define CUnderLine	"\033[4m"	// 下划线
	#define CFlash		"\033[5m"	// 闪烁
	#define CQFlash		"\033[6m"	// quick flashing
	#define CInverse	"\033[7m"	//


//* Cursor control
	#define CUp(n)			"\033["#n"A" // Up:   Moves the cursor n (default 1) cells in the given direction.
	#define CDown(n)		"\033["#n"B" // Down: e.g. std::cout << CDown("2") // moves cursor 2 cells down
	#define CLeft(n)		"\033["#n"C" // Left:
	#define CRight(n)		"\033["#n"D" // Right:

	#define CNextLn(n)		"\033["#n"E" // Moves cursor to beginning of the line n (default 1) lines down
	#define CPrevLn(n)		"\033["#n"F" // Moves cursor to beginning of the line n (default 1) lines up.
	#define CHorzPos(n)		"\033["#n"G" // Moves the cursor to column n (default 1, absolute).

	#define CCursorPos(x, y) "\033["#x";"#y"H" // Moves the cursor to row n, column m
	#define CPos(x, y) 		CCursorPos(x, y)

//* clear the screen or line
	#define CClear(n)		"\033["#n"J"
	#define CClearAfter		CClear(0)   // clear from cursor to end of screen
	#define CClearBefore	CClear(1)   // clear from cursor to beginning of the screen
	#define CClearScr		CClear(2) 	// clear screen(console), and moves cursor to upper left on DOS ANSI.SYS.
	#define CClearAll		CClear(3) 	// erase screen(console), and delete all lines saved in the scrollback buffer


	#define CEraseLine(n)	"\033["#n"K" // Erases part of the line. If n is 0 (or missing), clear from cursor to the end of the line. If n is 1, clear from cursor to beginning of the line. If n is 2, clear entire line. Cursor position does not change.

//* scroll control
	#define CScrollUp(n)	"\033["#n"S"
	#define CScrollDn(n)	"\033["#n"T"
	#define CSaveCursurPos	"\033[s"
	#define CReadCursurPos  "\033[u"

//* deprecated macros
#if CONSOLE_UTIL_USE_DEPRECATED == 1
	#define CDefault 	CReset

	#define BPurple		BMagenta
	#define BLPurple	BLMagenta

	#define CBlack		FBlack
	#define CRed 		FRed
	#define CGreen 		FGreen
	#define CBrown		FBrown
	#define CYellow		FYellow
	#define CBlue		FBlue
	#define CMagenta	FMagenta
	#define CPurple		CMagenta
	#define CCyan		FCyan
	#define CWhite		FWhite
	#define CGray		FGray
	#define CLBlack		FLBlack
	#define CLRed 		FLRed
	#define CLGreen 	FLGreen
	#define CLYellow 	FLYellow
	#define CLBlue 		FLBlue
	#define CLMagenta 	FLMagenta
	#define CLPurple 	CLMagenta
	#define CLCyan 		FLCyan
	#define CLWhite 	FLWhite
	
	#define SETCOLOR(_STYLE, _STR) 	CStyle(_STYLE, _STR)
	
#endif // CONSOLE_UTIL_USE_DEPRECATED

//* macros for console window/application and streams
#if defined(_WIN32) || defined(WIN32) || defined(__WIN32) // in windows
	#define CONSOLE_UTF_8() 	system("chcp 65001");	//* set console encoding to UTF-8 in windows
	#define CONSOLE_CLEAR()		system("cls");			//  clear the screen (console)

	#define CONSOLE_SIZE(X, Y) 	system("mode con cols=" #X "lines=" #Y); // set console window size

	#define CONSOLE_PAUSE()		system("pause");		// pause the console application

#else // in linux
	#define CONSOLE_UTF_8()
	#define CONSOLE_CLEAR()		system("clear"); 		//  clear the screen (console)

	#define CONSOLE_SIZE(X, Y)

	#define CONSOLE_PAUSE()		getchar();				// pause the console application
#endif

// 吸收输入缓存区内的其余字符, 以便下次 scanf 或 cin 时能够获取到正确的输入内容
//* Flush the input buffer to ensure that subsequent "scanf()" or "cin" calls receive valid input.
#define CONSOLE_FLUSH_INPUT_BUFFER()	{char ch; while((ch = getchar()) != '\n') continue;}


#if defined(_WINDOWS_) || defined(WINAPI) // WinAPI 适配
	#define CONSOLE_TITLE(str)		SetConsoleTitleA(str);        // set console title in windows
#else // 没有 WinAPI
	#define CONSOLE_TITLE(str)		printf("\033]0;%s\007", str); // set console title in linux
#endif

#if CONSOLE_UTIL_USE_DEPRECATED == 1
	#define CONSOLE_ABSORB()		CONSOLE_FLUSH_INPUT_BUFFER() // deprecated
	
	// 行尾附着换行符的 printf
	#define NPRINTF(str, ...) 				printf(str "\n",  ##__VA_ARGS__ );

	// 可自定义颜色, 输出后恢复默认的 printf
	#define CPRINTF(color, str, ... ) 		printf(color str CReset, ##__VA_ARGS__ );

	// 可自定义颜色, 输出后恢复默认, 行尾附着换行符的 printf
	#define CNPRINTF(color, str, ... ) 		printf(color str CReset "\n", ##__VA_ARGS__ );
#endif // CONSOLE_UTIL_USE_DEPRECATED


/*
 * reference:    https://en.wikipedia.org/wiki/ANSI_escape_code
   Ansi 转义序列: https://zh.wikipedia.org/wiki/ANSI%E8%BD%AC%E4%B9%89%E5%BA%8F%E5%88%97
   
Instruction:

	int main(int argc, char* argv[]){
		CONSOLE_UTF_8(); 			// switch console encoding to UTF-8 (windows)
		CONSOLE_TITLE("MyProject"); // set console window title
		CONSOLE_SIZE(100, 30);		// set console window size to with of 30 chars and height of 30 lines.
		CONSOLE_CLEAR();			// clear console (system("cls"))
		
		PRINT_ARGV(argc, argv);		// print all argc and argv[n] of main() function
		
		printf(FLGreen "Hello World!\n" CReset);   // print "Hello World" with light yellow console color formatting
														you should put "CReset" at the end of string to RESET console font color to DEFAULT
		printf(CStyle(FLGreen, "Hello World!\n")); // Equivalent
		
		std::cout << FLRed "ERROR\n" CReset;  // print "ERROR" with font color light red, "CReset" is also needed to revert font color to default
		std::cout << CStyle(FLRed, "ERROR\n");// Equivalent
		
		printf(BRed FGreen CQFlash "test\n" CReset);  // Print text with green font and red background, and quickly flashing
		printf(CStyle(BRed FGreen CQFlash, "test\n"));// Equivalent
		
		
		printf(CRight(2)); // move thr cursor up 2 lines
		
		PRINT_ERR("error occured!"); // print an error message with filename, function name and line number ATTACHED.
		
		CONSOLE_PAUSE(); 			 // system("pause");
		
		return 0;
	}

*/




//===================== C++ Utils ==========================
#ifdef __cplusplus

//* get C++ language standard version, do not add "L" suffix after param number
 // in MSVC compiler, __cplusplus always equals to 199711L, but _MSVC_LANG(Prior to VS2015) equals to cpp standard version
#ifdef _MSVC_LANG // sample: CPP_VER_HIGHER_EQUAL_THAN(201103)
	#define CPP_VER_HIGHER_EQUAL_THAN(_VER) \
		( (defined __cplusplus) && (_MSVC_LANG >= _VER##L) )
	#define CPP_VER_LOWER_THAN(_VER) \
		( (defined __cplusplus) && (_MSVC_LANG <  _VER##L) )
#else //. !defined _MSVC_LANG
	#define CPP_VER_HIGHER_EQUAL_THAN(_VER) \
		(__cplusplus >= _VER##L)
	#define CPP_VER_LOWER_THAN(_VER) \
		(__cplusplus <  _VER##L)
#endif // _MSVC_LANG


#endif // __cplusplus



//============= PROGRAM DEBUGGING: Print Args/Error Messages ===============

//* detect Debug Build or Release Build
#if (defined(_DEBUG) || defined(IS_DEBUG) || defined(DEBUG)) && !(defined(NDEBUG) || defined(_NDEBUG))
	#define GET_IS_DEBUG_BUILD() 	1
#else // defined(NDEBUG)
	#define GET_IS_DEBUG_BUILD() 	0
#endif


//* print all argc and argv[n] arguments for main() function
#define PRINT_ARGV(argc, argv) { \
		printf(CReset "\n"); \
		printf(FBlack BLYellow FLYellow CBold "====== Print Program params, all " FLRed "argc" FBlack " and " FLRed "argv[i]" FBlack " =====" CReset "\n");\
		printf(FLMagenta "    argc:   " FLWhite "%d\n", argc); \
		printf(FLGreen   "    argv[  0]: " FLBlue "%.256s\n", argv[0]); \
		for(int i = 1; i < argc; i++) { \
			printf(FLYellow "    argv[%3d]: " FLCyan "%.256s\n", i, argv[i]); \
		} \
		printf(CReset "\n"); \
	}
		
//* print an error message with filename, function name and line number ATTACHED.
#define PRINT_ERR(str) \
	printf(FLRed "\n=============== ERROR: " FLYellow str FLRed "\n" \
				"    file: " __FILE__ "\n" \
				"    func: %s\n" \
				"    line: %d\n\n" CReset \
			, __func__, __LINE__);


// print an error message, and force abort application.
#define ABORT_ERR(str) {PRINT_ERR(str); exit(-1);}
#define ABORT_ERR_ASM(str) {PRINT_ERR(str); asm("exit;" );}

#if CONSOLE_UTIL_USE_DEPRECATED == 1
	// 如果指针为空, 则强行退出程序
	#define ABORT_IF_NULLPTR(ptr, str) \
		{if(ptr == NULL) ABORT_ERR(str) }
		
	// 如果指针为空, 则退出函数
	#define RETURN_IF_NULLPTR(ptr, ...) \
		{if(ptr == NULL) return ##__VA_ARGS__;}
	
#endif // CONSOLE_UTIL_USE_DEPRECATED


//* macros for print something ONLY IN DEBUG BUILD
#if GET_IS_DEBUG_BUILD() // print in Debug Build
	#if defined(FMT_VERSION) // fmt::print(), fmt::println()
		#define DEBUG_PRINT(...)   fmt::print(__VA_ARGS__)
		#define DEBUG_PRINTLN(...) fmt::println(__VA_ARGS__)
	#elif CPP_VER_HIGHER_EQUAL_THAN(202302) // C++23 std::print(), std::println()
		#if __has_include(<print>) // && (defined(_PRINT_) || defined(_GLIBCXX_PRINT)
			#define DEBUG_PRINT(...)   std::print(__VA_ARGS__)
			#define DEBUG_PRINTLN(...) std::println(__VA_ARGS__)
		#else // no fmtlib, and after C++23
			#define DEBUG_PRINT(...)
			#define DEBUG_PRINTLN(...)
		#endif
	#else // no fmtlib, and before C++23
		#define DEBUG_PRINT(...)
		#define DEBUG_PRINTLN(...)
	#endif // _PRINT_
	
	// for std::cout, and printf()
	#define DEBUG_COUT(...)          std::cout << __VA_ARGS__
	#define DEBUG_COUTLN(...)        DEBUG_COUT(__VA_ARGS__) << '\n'
	
	#define DEBUG_PRINTF(STR, ...)   printf(STR, __VA_ARGS__)
	#define DEBUG_PRINTFLN(STR, ...) DEBUG_PRINTF(STR '\n', __VA_ARGS__)
	
#else // Do nothing in Release Build
	#define DEBUG_PRINT(...)
	#define DEBUG_PRINTLN(...)
	
	#define DEBUG_COUT(...)
	#define DEBUG_COUTLN(...)
	
	#define DEBUG_PRINTF(...)
	#define DEBUG_PRINTFLN(...)
	
#endif // GET_IS_DEBUG_BUILD
/* instruction:
	if you want to print some debug message to console, and only do this in DEBUG BUILD,
	use these macros above, they will do nothing in release build.
example:
	DEBUG_COUT("this is: " << 5); // expand to std::cout in debug build, and nothing in release build
	DEBUG_COUTLN("");             // with a line break ( << '\n')
	DEBUG_PRINTLN("this is {}", 5); // expand to fmt::println(if you include fmtlib headers above
										this header include), or std::println(C++23)
	DEBUG_PRINTF("this is %d", 5); // expand to printf in debug build
*/



//===================== Qt Utils ==========================
#if defined(QT_VERSION) && defined(__cplusplus)
//* you need to #include Qt Headers first before #include of this header.

//* Qt5 high DPI support since Qt5.6, and fractional scaling support since Qt5.14
//  in Qt6, high DPI and fractional scaling support is enabled by default and no need for this macro.
//  pls #include<QApplication> first before #include of this header.
#if ((QT_VERSION >= QT_VERSION_CHECK(5,6,0)) && (QT_VERSION < QT_VERSION_CHECK(5,14,0)))
	#define QT5_HIGH_DPI() \
		QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling); \
		QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#elif ((QT_VERSION >= QT_VERSION_CHECK(5,14,0)) && (QT_VERSION < QT_VERSION_CHECK(6,0,0)))
	#define QT5_HIGH_DPI() \
		QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling); \
		QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps); \
		QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
#else // QT_VERSION ( >= 6.0.0 || <= 5.5.0 )
	#define QT5_HIGH_DPI()
#endif // QT_VERSION

//* Set QTextCodec default encoding to UTF-8,
//  or cannot correctly print chinese characters via qDebug() if code is saved in UTF-8 encoding;
//  pls #include<QTextCodec> first before #include of this header.
//  in MSVC Compiler, compiler argument "/utf-8" is required if code is saved in UTF-8 encoding;
//  	in CMake, you should add "set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")"
//  In Qt6, QTextCodec module is deleted and
#if defined(QTEXTCODEC_H)
	#define QT5_TEXTCODEC_UTF_8() 	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
	#define QT5_TEXTCODEC_GBK()     QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB18030"));
#else //. !QTEXTCODEC_H
	#define QT5_TEXTCODEC_UTF_8()
	#define QT5_TEXTCODEC_GBK()
#endif // QTEXTCODEC_H

/* example:
	int main(int argc, char* argv[])
	{
		QT5_HIGH_DPI(); //* use Qt5 high DPI support
		QT5_TEXTCODEC_UTF_8(); //* set Qt text encoding to UTF-8
		
		QApplication app(argc, argv);
		
		return app.exec();
	}
*/

//* qDebug() without spaces or quotes
//  pls #include<QDebug> first before this header #include
#ifdef QDEBUG_H
	#define QDEBUGNN qDebug().nospace().noquote() // 不输出空格和引号的 qDebug()
	#define QDEBUGN  qDebug().noquote() 		  // 不加引号的 qDebug()
	// example: QDEBUGNN << "test" << 1;
#endif




#endif // QT_VERSION


//==================== CUDA Utils ==========================
#ifdef __CUDA_RUNTIME_H__ //* CUDA 错误检查与退出机制

#define PRINT_CUDA_ERR(str) \
		printf(FLRed "\n=============== CUDA ERROR = %d: " str "\n" \
					"    file: " __FILE__ "\n" \
					"    func: %s\n" \
					"    line: %d\n" CReset \
				, err, __func__, __LINE__);
	
// 进行 cuda 部分操作后, 将返回值传入此宏定义中, 如果执行失败, 则输出信息, 并退出当前函数, 第三个参数为 return 值, void 则不填写
#define RETURN_IF_CUDA_ERR(err, str, ...) \
	if (err != cudaSuccess) { \
		PRINT_CUDA_ERR(str); \
		return __VA_ARGS__; \
	}

// 进行 cuda 部分操作后, 将返回值传入此宏定义中, 如果执行失败, 则输出信息并强行停止程序
#define ABORT_IF_CUDA_ERR(err, str) \
	if (err != cudaSuccess) { \
		PRINT_CUDA_ERR(str) \
		exit(-1); \
	}

#endif //__CUDA_RUNTIME_H__







#endif // CONSOLE_UTIL_H__
