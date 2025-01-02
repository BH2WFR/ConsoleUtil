/* UTF-8 encoding
* Project URL: 	https://github.com/BH2WFR/ConsoleUtil
  Author:		BH2WFR
  Updated:		2 JAN 2025
  License:		MIT License
* Do not include this header in header files.
* If libs like fmtlib or Qt also included in source file, pls #include their headers FIRST, then #include this header.
	引用说明: 若源文件使用了 fmtlib 或 Qt 等库, 请先 #include 这些头文件, 最后再 #include 此头文件.
*/
#ifndef CONSOLEUTIL_CONSOLE_UTIL_H__
#define CONSOLEUTIL_CONSOLE_UTIL_H__
#include <ConsoleUtil/Base.h>
#include <ConsoleUtil/CUtil.h> // vital dependency


//* ==== customize parameters:
// #define CONSOLE_UTIL_ANSI_ESCAPE_UNSUPPORTED		1	// set 0 to disable style changing, espeacially before Windows 10 1511
// #define CONSOLE_UTIL_DO_NOT_USE_COLOR			1	// do not use color to stderr text
// #define CONSOLE_UTIL_DO_NOT_USE_SHORTER_ALIAS	1	// do not use shorter aliases, like `CU_DBG_PRINT` or `CU_EQU_F`
	// p.s. if these macros are not defined, `#if (MACRO == 0)` will evaluate to `true`.




_CUTIL_NAMESPACE_BEGIN

//====================== CONSOLE FORMAT/CUSTOMIZING MACROS =========================
//* reference:    https://en.wikipedia.org/wiki/ANSI_escape_code
			   // https://zh.wikipedia.org/wiki/ANSI%E8%BD%AC%E4%B9%89%E5%BA%8F%E5%88%97
			   
//* WARNING:  Windows built-in command-line tools in versions prior to Windows 10 1511 do not support this feature.
//		If font or color customizing features is needed in Windows 7 or prior system, pls use SetConsoleTextAttribute() function.
#if (CONSOLE_UTIL_ANSI_ESCAPE_UNSUPPORTED == 0) // || (WINVER >= 0x0A00)
	#define CAnsiEsc(_STR)		"\033[" _STR //* C++ Ansi Escape Codes with prefix
	#define CAnsiEscStr(_STR)	_STR 		 //  raw C++ Ansi EScape Code Strings
#else
	#define CAnsiEsc(_STR)	  	"" //* "\033[" ANSI Escape code is UNSUPPORTED before Windows 10 1511 in cmd
	#define CAnsiEscStr(_STR)	""
#endif

//* RESET color formatting and font styles to DEFAULT, you must add this after customizing font color
	#define CReset 			CAnsiEsc("0m")
	#define CRst			CReset 		// shorter alias
	#define CStyle(_STYLE, _STR)	_STYLE _STR CReset
	// example: printf(FYellow BBlue "yellow text" CRst);

//* font foreground colors
// dark font color series
	#define FBlack			CAnsiEsc("30m")
	#define FRed 			CAnsiEsc("31m")
	#define FGreen 			CAnsiEsc("32m")
	#define FYellow			CAnsiEsc("33m")	// in some terminals, it renders like brown.
	#define FBlue			CAnsiEsc("34m")
	#define FMagenta		CAnsiEsc("35m")
	#define FCyan			CAnsiEsc("36m")
	#define FWhite			CAnsiEsc("37m")
	
// light font color series
	#define FLBlack			CAnsiEsc("90m")	// it's gray.
	#define FLRed 			CAnsiEsc("91m")
	#define FLGreen 		CAnsiEsc("92m")
	#define FLYellow 		CAnsiEsc("93m")
	#define FLBlue 			CAnsiEsc("94m")
	#define FLMagenta 		CAnsiEsc("95m")
	#define FLCyan 			CAnsiEsc("96m")
	#define FLWhite 		CAnsiEsc("97m")
	#define FGray			FLBlack 	// equals to "CLBlack"
	#define FGrey			FLBlack
	
// font color: custom RGB values CRGB
	#define FRgb(R, G, B)	CAnsiEsc("38;2;" #R ";" #G ";" #B "m")
	#define FCode(C)		CAnsiEsc("38;5;"#C"m") // 8-bit color code, supports 0-15, 16-231, 232-255
	#define FDefault		CAnsiEsc("39m") 	// default foreground color

//* font background colors, can be combined with foreground colors
// dark font background color series
	#define BBlack			CAnsiEsc("40m")
	#define BRed 			CAnsiEsc("41m")
	#define BGreen 			CAnsiEsc("42m")
	#define BYellow			CAnsiEsc("43m")
	#define BBlue			CAnsiEsc("44m")
	#define BMagenta		CAnsiEsc("45m")
	#define BCyan			CAnsiEsc("46m")
	#define BWhite			CAnsiEsc("47m")
	
// light font background color series
	#define BLBlack			CAnsiEsc("100m")  // actually it's gray
	#define BLRed 			CAnsiEsc("101m")
	#define BLGreen 		CAnsiEsc("102m")
	#define BLYellow		CAnsiEsc("103m")
	#define BLBlue			CAnsiEsc("104m")
	#define BLMagenta		CAnsiEsc("105m")
	#define BLCyan			CAnsiEsc("106m")
	#define BLWhite			CAnsiEsc("107m")
	#define BGray			BLBlack	 // equals to "BLBlack"
	#define BGrey			BLBlack
	
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
	
	
//* ==== specific foreground and background color combinations
	#define CTurn 			CAnsiEsc("107;30m")		// 白底黑字, white text on a black background
	#define CLYelBold 		CAnsiEsc("1;93m")		// bold, and light yellow
	#define CInvLYel		CAnsiEsc("1;30;103m")
	#define CLRedBold		CAnsiEsc("1;91m")
	#define CLightBold		CAnsiEsc("1;97;100m")
	#define CInvBold		CAnsiEsc("1;30;107m")

//* ============
//* Cursor control
	#define CUp(n)			CAnsiEsc(#n"A") // cursor Up:   Moves the cursor n (default 1) cells in the given direction.
	#define CDown(n)		CAnsiEsc(#n"B") // cursor Down: e.g. std::cout << CDown("2") // moves cursor 2 cells down
	#define CForward(n)		CAnsiEsc(#n"C") // cursor Forward:
	#define CBack(n)		CAnsiEsc(#n"D") // cursor Back
	#define CFwd(n)			CForward(n)  	// aliases
	#define CRight(n)		CForward(n)
	#define CLeft(n)		CBack(n)

	#define CNextLn(n)		CAnsiEsc(#n"E") // Moves cursor to beginning of the line n (default 1) lines down
	#define CPrevLn(n)		CAnsiEsc(#n"F") // Moves cursor to beginning of the line n (default 1) lines up.
	#define CHorzPos(n)		CAnsiEsc(#n"G") // Moves the cursor to column n (default 1, absolute).

	#define CCursorPos(x, y) CAnsiEsc(#x";"#y"H") 	// Moves the cursor to row n, column m
	#define CPos(x, y) 		 CCursorPos(x, y) 		// shorter alias

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

//* macros for text color formatting
#if (CONSOLE_UTIL_DO_NOT_USE_COLOR == 1) || (CONSOLE_UTIL_ANSI_ESCAPE_UNSUPPORTED == 1)
	#define CUTIL_COLOR_OPT(_COLOR)		""
	// #define CUTIL_COLOR_ERR(_STR)		_STR
	
#else // CONSOLE_UTIL_DO_NOT_USE_COLOR
	#define CUTIL_COLOR_OPT(_COLOR)		_COLOR
	// #define CUTIL_COLOR_ERR(_STR)		CUTIL_COLOR_OPT(FLRed) _STR CUTIL_COLOR_OPT(CRst)
	
#endif // CONSOLE_UTIL_DO_NOT_USE_COLOR


//* ==============================================================


//* macros for console window/application and streams
#if defined(CUTIL_OS_WINDOWS) // in Windows
	#if defined(_WINDOWS_) || defined(WINAPI)
		#define CUTIL_CHCP_ENCODING(_NUM)	do {SetConsoleCP(_NUM); SetConsoleOutputCP(_NUM); system("chcp "#_NUM);} while(0)
	#else // in windows system, but without <windows.h> winapi
		#define CUTIL_CHCP_ENCODING(_NUM)	system("chcp "#_NUM)	// custom chcp encoding (number) in Windows
	#endif
	
	#define CUTIL_CONSOLE_CLEAR()			system("cls")			// clear the screen (console)
	#define CUTIL_CONSOLE_SIZE(X, Y) 		system("mode con cols=" #X "lines=" #Y) // set console window size
	#define CUTIL_CONSOLE_PAUSE()			system("pause")			// pause the console application
	
#else 	// in Linux/MacOS
	#define CUTIL_CHCP_ENCODING(_NUM)
	
	#define CUTIL_CONSOLE_CLEAR()			system("clear") 		// clear the screen (console)
	#define CUTIL_CONSOLE_SIZE(X, Y)
	#define CUTIL_CONSOLE_PAUSE()			getchar()				// pause the console application
	
#endif



//* features with win32api
#if defined(_WINDOWS_) || defined(WINAPI)
	#define CUTIL_CONSOLE_TITLE(_STR)			SetConsoleTitle(_STR)  // set console title in windows by winapi, (_A/_W?)
	#define CUTIL_CONSOLE_TITLE_A(_STR)			SetConsoleTitleA(_STR)
	#define CUTIL_CONSOLE_TITLE_W(_WSTR)		SetConsoleTitleW(_WSTR)
	
	#define CUTIL_CONSOLE_CURSOR_POS(x, y)	\
		do {COORD pos; pos.X=x; pos.Y=y; SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);} while(0)
	#define CUTIL_CONSOLE_ATTR(_ATTR)			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (_ATTR))
	#define CUTIL_CONSOLE_RESET_STYLE()			CUTIL_SET_CONSOLE_ATTR(0)
	#define CUTIL_ENABLE_VIRTUAL_TERMINAL()	\
		do {HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); DWORD mode; GetConsoleMode(handle, &mode); \
			mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING; SetConsoleMode(handle, mode);} while(0)
	//? 据说上面的函数在设置时只需要设置一次就可以自动适配到 STD_OUTPUT_HANDLE(stdout) 和 STD_ERROR_HANDLE(stderr) ?
	
//#else // without win32api, or in Linux
#elif (CONSOLE_UTIL_ANSI_ESCAPE_UNSUPPORTED == 0) // without win32api, or in Linux
	#define CUTIL_CONSOLE_TITLE(_STR)			printf("\033]0;%s\007", _STR) // set console title in linux
	#define CUTIL_CONSOLE_TITLE_A(_STR)			CUTIL_CONSOLE_TITLE(_STR)
	#define CUTIL_CONSOLE_TITLE_W(_WSTR)		wprintf("\033]0;%s\007", _WSTR)
	
	#define CUTIL_CONSOLE_CURSOR_POS(x, y)		printf(CCursorPos(x, y))
	#define CUTIL_CONSOLE_ATTR(_ATTR)
	#define CUTIL_CONSOLE_RESET_STYLE()			printf(CReset)
	#define CUTIL_ENABLE_VIRTUAL_TERMINAL()
	
#else
	#define CUTIL_CONSOLE_TITLE(_STR)
	#define CUTIL_CONSOLE_CURSOR_POS(x, y)
	#define CUTIL_CONSOLE_ATTR(_ATTR)
	#define CUTIL_CONSOLE_RESET_STYLE()
	#define CUTIL_ENABLE_VIRTUAL_TERMINAL()
	
#endif


//* Flush the input buffer to ensure that subsequent "scanf()" or "cin" calls receive valid input.
#define CUTIL_CONSOLE_FLUSH_INPUTBUFFER()	do {char ch; while((ch = getchar()) != '\n') continue;} while(0)
	// 吸收输入缓存区内的其余字符, 以便下次 scanf 或 cin 时能够获取到正确的输入内容

//* Set Console Encoding by "chcp" command in Windows
#define CUTIL_CHCP_ENCODING_UTF8()       CUTIL_CHCP_ENCODING(65001)		//* set console encoding to UTF-8 in windows
#define CUTIL_CHCP_ENCODING_GB2312()     CUTIL_CHCP_ENCODING(936)		//  Simp. Chinese, or 54936 for GB18030
#define CUTIL_CHCP_ENCODING_BIG5()       CUTIL_CHCP_ENCODING(950)		//  Trad. Chinese
#define CUTIL_CHCP_ENCODING_KOR()        CUTIL_CHCP_ENCODING(949)		//  Korean
#define CUTIL_CHCP_ENCODING_JIS()        CUTIL_CHCP_ENCODING(932)		//  Shift_JIS,
#define CUTIL_CHCP_ENCODING_LATIN1()     CUTIL_CHCP_ENCODING(850)		//  Latin 1 multilingual
#define CUTIL_CHCP_ENCODING_LATIN2()     CUTIL_CHCP_ENCODING(852)		//  Latin 2 multilingual (Slavic)
#define CUTIL_CHCP_ENCODING_CYR()        CUTIL_CHCP_ENCODING(855)		//  Cyrillic / Russian
#define CUTIL_CHCP_ENCODING_WIN1250()    CUTIL_CHCP_ENCODING(1250)		//  windows 1250, Central European
#define CUTIL_CHCP_ENCODING_WIN1251()    CUTIL_CHCP_ENCODING(1251)		//  windows 1251, Cyrillic
#define CUTIL_CHCP_ENCODING_WIN1252()    CUTIL_CHCP_ENCODING(1252)		//  windows 1252, western European

//* set execution locale
#define CUTIL_LOCALE_UTF8()				setlocale(LC_ALL, ".UTF-8")
#define CUTIL_LOCALE_DEFAULT()			setlocale(LC_ALL, "")
#define CUTIL_LOCALE_UTF8_PRINT()		do {char* pLocale = setlocale(LC_ALL, ".UTF-8");	\
											if(pLocale == NULL){ \
												printf(FLRed "  setlocale(): unknown locale!\n" CRst); \
											}else{	\
												printf(FLGreen "  setlocale(): locale set to %s" CRst, pLocale); \
											}		\
											printf("\n"); \
										} while(0)
/*
* Instruction:
	#include <locale.h>
	#include <stdio.h>
	#include <windows.h>		// include other headers first
	#include <fmt/core.h>		// include other headers first
	
	#include <ConsoleUtil/ConsoleUtil.h> 	// include this header at last
	
	int main(int argc, char* argv[]){
		CUTIL_CHCP_ENCODING_UTF8(); 		// switch console encoding to UTF-8 (windows)
		CUTIL_CONSOLE_TITLE(_TEXT("MyProject")); 	// set console window title
		CUTIL_CONSOLE_SIZE(100, 30);		// set console window size to with of 30 chars and height of 30 lines.
		CUTIL_CONSOLE_CLEAR();				// clear console (system("cls"))
		
		CUTIL_PRINT_ARGV(argc, argv);	// print all argc and argv[n] of main() function
		
		printf(FLGreen "Hello World!\n" CReset);   // print "Hello World" with light yellow console color formatting
														you should put "CReset" at the end of string to RESET console font color to DEFAULT
		printf(CStyle(FLGreen, "Hello World!\n")); // Equivalent
		
		std::cout << FLRed "ERROR\n" CReset;  // print "ERROR" with font color light red, "CReset" is also needed to revert font color to default
		std::cout << CStyle(FLRed, "ERROR\n");// Equivalent
		
		printf(BRed FGreen CQFlash "test\n" CReset);  // Print text with green font and red background, and quickly flashing
		printf(CStyle(BRed FGreen CQFlash, "test\n"));// Equivalent
		
		
		printf(CForward(2)); // move thr cursor 2 characters right, equals to `CRight(2)` or `CFwd(2)`.
		
		
		CUTIL_ERROR_MESSAGE("error occured!"); // print an error message with filename, function name and line number ATTACHED.
		
		CUTIL_CONSOLE_PAUSE(); 			 // system("pause");
		
		return 0;
	}

*/



//============= PROGRAM DEBUGGING: Print Args/Error Messages ===============

//* print all argc and argv[n] arguments for main(int argc, char* argv[]) function
#define CUTIL_PRINT_ARGV(_argc, _argv) do { \
		printf(CRst "\n"); \
		printf(FLCyan CBold "====== Print Program params for `int main(int " FLWhite "argc" FLCyan ", char* " FLYellow "argv[]" FLCyan ")` =====" CRst "\n");\
		printf(FLWhite CBold 	"  argc: " FLWhite "%d" CRst "\n", (_argc)); \
		printf(FLGreen   		"    argv[  0]: " FLBlue "%.256s\n", (_argv)[0]); \
		for(int i = 1; i < (_argc); i++) { \
			printf(FLYellow 	"    argv[%3d]: " FLGreen "%.256s\n", i, (_argv)[i]); \
		} \
		printf(CRst "\n"); \
	} while (0)
		
//* print an error message with filename, function name and line number ATTACHED.
#define CUTIL_ERROR_MESSAGE(_REASON) \
	fprintf(stderr, FLRed CBold	"\n=============== ERROR MESSAGE: " FLWhite _REASON CRst "\n" \
			FRed "    file: " FCyan  __FILE__ "\n" \
			FRed "    func: " FCyan "%s\n" \
			FRed "    line: " FCyan "%d\n" \
			CRst "\n" , __func__, __LINE__ \
	)

//* print an warning message with filename, function name and line number ATTACHED.
#define CUTIL_WARNING_MESSAGE(_REASON) \
	fprintf(stderr, FLYellow "\n=============== WARNING MESSAGE: " FLWhite _REASON CRst "\n" \
			FYellow "    file: " FCyan  __FILE__ "\n" \
			FYellow "    func: " FCyan "%s\n" \
			FYellow "    line: " FCyan "%d\n" \
			CRst "\n" , __func__, __LINE__ \
	)

// print an error message, and force abort application.
#define CUTIL_ABORT_ERR(_REASON) 	 	do {CUTIL_ERROR_MESSAGE(_REASON); exit(-1);		} while(0)
#define CUTIL_ABORT_ERR_ASM(_REASON) 	do {CUTIL_ERROR_MESSAGE(_REASON); asm("exit");	} while(0)


// print if the application is in debug or release build
#if CUTIL_DEBUG_BUILD
	#define CUTIL_PRINT_BUILD_TYPE()	printf(FLGreen "  build type: `Debug`\n" CRst)
#else // release
	#define CUTIL_PRINT_BUILD_TYPE()	printf(FLGreen "  build type: `Release`\n" CRst)
#endif


//* macros for print something ONLY IN DEBUG BUILD

#if CUTIL_DEBUG_BUILD // Only Print in Debug Build
	#if defined(FMT_VERSION) && defined(__cplusplus) // fmt::print(), fmt::println()
		#define CUTIL_DEBUG_PRINT(_STR, ...)			fmt::print(_STR, ##__VA_ARGS__)
		#define CUTIL_DEBUG_PRINTLN(_STR, ...)			fmt::println(_STR, ##__VA_ARGS__)
		#define CUTIL_DEBUG_PRINT_ERR(_STR, ...)		fmt::print(stderr, CUTIL_COLOR_OPT(FLRed) _STR CUTIL_COLOR_OPT(CRst), ##__VA_ARGS__)
		#define CUTIL_DEBUG_PRINTLN_ERR(_STR, ...)		fmt::println(stderr, CUTIL_COLOR_OPT(FLRed) _STR CUTIL_COLOR_OPT(CRst), ##__VA_ARGS__)
		// note: "##__VA_ARGS__" is supported in gnu C++, and MSVC for version >= VS2015 update 3
	#elif defined(CUTIL_CPP23_SUPPORTED) // C++23 std::print(), std::println()
		#if __has_include(<print>) // C++17 support, && (defined(_PRINT_) || defined(_GLIBCXX_PRINT)
			#define CUTIL_DEBUG_PRINT(_STR, ...)		std::print(_STR, ##__VA_ARGS__)
			#define CUTIL_DEBUG_PRINTLN(_STR, ...)		std::println(_STR, ##__VA_ARGS__)
			#define CUTIL_DEBUG_PRINT_ERR(_STR, ...)	std::print(stderr, CUTIL_COLOR_OPT(FLRed) _STR CUTIL_COLOR_OPT(CRst), ##__VA_ARGS__)
			#define CUTIL_DEBUG_PRINTLN_ERR(_STR, ...)	std::println(stderr, CUTIL_COLOR_OPT(FLRed) _STR CUTIL_COLOR_OPT(CRst), ##__VA_ARGS__)
		#else // no fmtlib, and after C++23
			#define CUTIL_DEBUG_PRINT(_STR, ...)
			#define CUTIL_DEBUG_PRINTLN(_STR, ...)
			#define CUTIL_DEBUG_PRINT_ERR(_STR, ...)
			#define CUTIL_DEBUG_PRINTLN_ERR(_STR, ...)
		#endif
	#else // no fmtlib, and before C++23
		#define CUTIL_DEBUG_PRINT(_STR, ...)
		#define CUTIL_DEBUG_PRINTLN(_STR, ...)
		#define CUTIL_DEBUG_PRINT_ERR(_STR, ...)
		#define CUTIL_DEBUG_PRINTLN_ERR(_STR, ...)
	#endif // _PRINT_
	
	// for std::cout, and printf()
	#define CUTIL_DEBUG_COUT(...)				std::cout << __VA_ARGS__
	#define CUTIL_DEBUG_COUTLN(...)				std::cout << __VA_ARGS__ << '\n'
	#define CUTIL_DEBUG_CERR(...)				std::cerr << CUTIL_COLOR_OPT(FLRed) "" << __VA_ARGS__ << CUTIL_COLOR_OPT(CRst) ""
	#define CUTIL_DEBUG_CERRLN(...)				std::cerr << CUTIL_COLOR_OPT(FLRed) "" << __VA_ARGS__ << CUTIL_COLOR_OPT(CRst) "" << '\n'
	
	#define CUTIL_DEBUG_PRINTF(_STR, ...)		printf(_STR, ##__VA_ARGS__)
	#define CUTIL_DEBUG_PRINTFLN(_STR, ...)		printf(_STR "\n", ##__VA_ARGS__)
	#define CUTIL_DEBUG_PRINTF_ERR(_STR, ...)	fprintf(stderr, CUTIL_COLOR_OPT(FLRed) _STR CUTIL_COLOR_OPT(CRst), ##__VA_ARGS__)
	#define CUTIL_DEBUG_PRINTFLN_ERR(_STR, ...)	fprintf(stderr, CUTIL_COLOR_OPT(FLRed) _STR CUTIL_COLOR_OPT(CRst) "\n", ##__VA_ARGS__)
	
	#define CUTIL_DEBUG_PRINT_ARGV(_argc, _argv) 	CUTIL_PRINT_ARGV(_argc, _argv)
	
#else // Do Nothing in Release Build
	#define CUTIL_DEBUG_PRINT(_STR, ...)
	#define CUTIL_DEBUG_PRINTLN(_STR, ...)
	#define CUTIL_DEBUG_PRINT_ERR(_STR, ...)
	#define CUTIL_DEBUG_PRINTLN_ERR(_STR, ...)
	
	#define CUTIL_DEBUG_COUT(...)
	#define CUTIL_DEBUG_COUTLN(...)
	#define CUTIL_DEBUG_CERR(...)
	#define CUTIL_DEBUG_CERRLN(...)
	
	#define CUTIL_DEBUG_PRINTF(_STR, ...)
	#define CUTIL_DEBUG_PRINTFLN(_STR, ...)
	#define CUTIL_DEBUG_PRINTF_ERR(_STR, ...)
	#define CUTIL_DEBUG_PRINTFLN_ERR(_STR, ...)
	
	#define CUTIL_DEBUG_PRINT_ARGV(_argc, _argv)
	
#endif // CUTIL_DEBUG_BUILD

#if (CONSOLE_UTIL_DO_NOT_USE_SHORTER_ALIAS == 0) //* shorter aliases
	#define CU_DBG_PRINT(_STR, ...)			CUTIL_DEBUG_PRINT(_STR, ##__VA_ARGS__)
	#define CU_DBG_PRINTLN(_STR, ...)		CUTIL_DEBUG_PRINTLN(_STR, ##__VA_ARGS__)
	#define CU_DBG_PRINT_ERR(_STR, ...)		CUTIL_DEBUG_PRINT_ERR(_STR, ##__VA_ARGS__)
	#define CU_DBG_PRINTLN_ERR(_STR, ...)	CUTIL_DEBUG_PRINTLN_ERR(_STR, ##__VA_ARGS__)

	#define CU_DBG_COUT(...)				CUTIL_DEBUG_COUT(__VA_ARGS__)
	#define CU_DBG_COUTLN(...)				CUTIL_DEBUG_COUTLN(__VA_ARGS__)
	#define CU_DBG_CERR(...)				CUTIL_DEBUG_CERR(__VA_ARGS__)
	#define CU_DBG_CERRLN(...)				CUTIL_DEBUG_CERRLN(__VA_ARGS__)

	#define CU_DBG_PRINTF(_STR, ...)		CUTIL_DEBUG_PRINTF(_STR, ##__VA_ARGS__)
	#define CU_DBG_PRINTFLN(_STR, ...)		CUTIL_DEBUG_PRINTFLN(_STR, ##__VA_ARGS__)
	#define CU_DBG_PRINTF_ERR(_STR, ...)	CUTIL_DEBUG_PRINTF_ERR(_STR, ##__VA_ARGS__)
	#define CU_DBG_PRINTFLN_ERR(_STR, ...)	CUTIL_DEBUG_PRINTFLN_ERR(_STR, ##__VA_ARGS__)
#endif // CONSOLE_UTIL_DO_NOT_USE_SHORTER_ALIAS
/* instruction:
	if you want to print some debug message to console, and only do this in DEBUG BUILD,
	use these macros above, they will do nothing in release build.
* example:
	CUTIL_DEBUG_COUT("this is: " << 5); // expand to std::cout in debug build, and nothing in release build
	CUTIL_DEBUG_COUTLN("");             // with a line break ( << '\n')
	CUTIL_DEBUG_PRINTLN("this is {}", 5); // expand to fmt::println(if you include fmtlib headers above
										this header include), or std::println(C++23)
	CUTIL_DEBUG_PRINTF("this is %d", 5); // expand to printf in debug build
	
	CUTIL_DEBUG_PRINTLN_ERR("err: cannot ...!"); // print to stderr
	CUTIL_DEBUG_PRINTLN(stderr, "err: cannot ...!"); // equivelent
	CUTIL_DEBUG_CERR("err: cannot ... !" << 2 << std::endl);
*/


#if defined(__cplusplus)
	#define CUTIL_COUT_VAR(_VAR)				std::cout << _VAR << "\n"
#endif // __cplusplus
#if defined(FMT_VERSION) && defined(__cplusplus) // fmt::print(), fmt::println()
	// note: "##__VA_ARGS__" is supported in gnu C++, and MSVC for version >= VS2015 update 3
	#define CUTIL_PRINT(_STR, ...)				fmt::print(_STR,   ##__VA_ARGS__)
	#define CUTIL_PRINTLN(_STR, ...)			fmt::println(_STR, ##__VA_ARGS__)
	#define CUTIL_PRINT_ERR(_STR, ...)			fmt::print(stderr,   CUTIL_COLOR_OPT(FLRed) _STR CUTIL_COLOR_OPT(CRst) ,##__VA_ARGS__)
	#define CUTIL_PRINTLN_ERR(_STR, ...)		fmt::println(stderr, CUTIL_COLOR_OPT(FLRed) _STR CUTIL_COLOR_OPT(CRst) ,##__VA_ARGS__)
	#define CUTIL_PRINT_VAR(_VAR)				fmt::println("{}", _VAR)
#elif defined(CUTIL_CPP23_SUPPORTED) // C++23 std::print(), std::println()
	#if __has_include(<print>) // C++17 support, && (defined(_PRINT_) || defined(_GLIBCXX_PRINT)
		#define CUTIL_PRINT(_STR, ...)			std::print(_STR,   ##__VA_ARGS__)
		#define CUTIL_PRINTLN(_STR, ...)		std::println(_STR, ##__VA_ARGS__)
		#define CUTIL_PRINT_ERR(_STR, ...)		std::print(stderr,   CUTIL_COLOR_OPT(FLRed) _STR CUTIL_COLOR_OPT(CRst), ##__VA_ARGS__)
		#define CUTIL_PRINTLN_ERR(_STR, ...)	std::println(stderr, CUTIL_COLOR_OPT(FLRed) _STR CUTIL_COLOR_OPT(CRst), ##__VA_ARGS__)
		#define CUTIL_PRINT_VAR(_VAR)			std::println("{}", _VAR)
	#else // no fmtlib, and after C++23
		#define CUTIL_PRINT(_STR, ...)
		#define CUTIL_PRINTLN(_STR, ...)
		#define CUTIL_PRINT_ERR(_STR, ...)
		#define CUTIL_PRINTLN_ERR(_STR, ...)
		#define CUTIL_PRINT_VAR(_VAR)			CUTIL_COUT_VAR(_VAR)
	#endif
#else // no fmtlib, and before C++23
	#define CUTIL_PRINT(_STR, ...)
	#define CUTIL_PRINTLN(_STR, ...)
	#define CUTIL_PRINT_ERR(_STR, ...)
	#define CUTIL_PRINTLN_ERR(_STR, ...)
	#define CUTIL_PRINT_VAR(_VAR)			CUTIL_COUT_VAR(_VAR)
#endif // _PRINT_

// for std::cout, and printf()
// #define CUTIL_COUT(...)			std::cout << __VA_ARGS__
// #define CUTIL_COUTLN(...)		std::cout << __VA_ARGS__ << '\n'
// #define CUTIL_CERR(...)			std::cerr << CUTIL_COLOR_OPT(FLRed) "" << __VA_ARGS__ << CUTIL_COLOR_OPT(CRst) ""
// #define CUTIL_CERRLN(...)		std::cerr << CUTIL_COLOR_OPT(FLRed) "" << __VA_ARGS__ << CUTIL_COLOR_OPT(CRst) "" << '\n'

// #define CUTIL_PRINTF(_STR, ...)		printf(_STR, ##__VA_ARGS__)
// #define CUTIL_PRINTFLN(_STR, ...)		printf(_STR "\n", ##__VA_ARGS__)
#define CUTIL_PRINTF_ERR(_STR, ...)		fprintf(stderr, CUTIL_COLOR_OPT(FLRed) _STR CUTIL_COLOR_OPT(CRst), ##__VA_ARGS__)
#define CUTIL_PRINTFLN_ERR(_STR, ...)	fprintf(stderr, CUTIL_COLOR_OPT(FLRed) _STR CUTIL_COLOR_OPT(CRst) "\n", ##__VA_ARGS__)



_CUTIL_NAMESPACE_END
#endif // CONSOLEUTIL_CONSOLE_UTIL_H__
