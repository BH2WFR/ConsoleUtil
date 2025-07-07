# ConsoleUtil

A **HEADER FILE** project with useful macros and template functions for C++.

**一个只有头文件的，有许多实用宏和函数的 C++ 轮子库**



**Homepage**:  https://github.com/BH2WFR/ConsoleUtil

**author**: 	BH2WFR

**LICENSE**: 	**MIT** License **(except extern codes)**

Reference of Ansi Escape Codes:

- https://en.wikipedia.org/wiki/ANSI_escape_code

- https://zh.wikipedia.org/wiki/ANSI%E8%BD%AC%E4%B9%89%E5%BA%8F%E5%88%97



### Included Following External Header-Only Libraries & credits to:

| **name**    | **author**     | **link**                                 | **path**                | **license** |
| :---------- | :------------- | :--------------------------------------- | ----------------------- | :--------- |
| **scope_guard** | ricab      | https://github.com/ricab/scope_guard | `External/ScopeGuard.hpp` | Unlicense |
| **xorstr**  | JustasMasiulis | https://github.com/JustasMasiulis/xorstr | `External/XorStr.hpp` | Apache 2.0 |
| **span**    | tcbrindle  | https://github.com/tcbrindle/span    | `External/Span.hpp`   | BSL 1.0 |
| **strutil** | Shot511    | https://github.com/Shot511/strutil   | `External/StrUtil.h` | MIT    |
| **magic_enum** | Neargye        | https://github.com/Neargye/magic_enum | `External/MaginEnum/*.h` | MIT|


----------

### WARNING:

- features using ANSI Escape code (like color customizing, or cursor moving macros in this header file) **DO NOT SUPPORT Windows version lower than Windows 10 1511**, otherwise it can't display properly in windows cmd.
    - If you are using these operating systems, pls `#define CONSOLE_UTIL_ANSI_ESCAPE_UNSUPPORTED  1` before `#include <ConsoleUtil/ConsoleUtil.h>` to disable features by printing Ansi Escape Code.

- C language version `≥ C99`, C++ language `≥ C++14` (≥C++17 recommended)  , with `##__VA_ARGS__` extension support.

    (**MSVC supports `##__VA_ARGS__` since VS2015 Update 3**. if your MSVC or VS version is older, pls delete "`##`", MSVC eats trailing comma before `__VA_ARGS__` by default without `/Zc::preprocessor` command)

- Pls #include this header **after other header files,** especially those from libraries such as Qt/fmtlib, or OS API headers like `<windows.h>/<unistd.h>`. DO NOT #include <`ConsoleUtil/ConsoleUtil.h`> in header files.

- `#define CONSOLE_UTIL_ANSI_ESCAPE_UNSUPPORTED  1` **BEFORE** include of this header may turn off all the features with ANSI Escape Code.

- `#define CUTIL_FORCE_FUNCTION_STATIC 1` **BEFORE** include of `CppUtil.hpp` may let all the inline functions to be `static inline`

- `#define CUTIL_FORCE_UTF8  0` **BEFORE** include may turn off UTF-8 literal encoding checking (C++ Only). By Default, **if you are using MSVC, `/UTF-8` compiler param is REQUIRED**.


----------

## <CppUtils.h>

### Comparing features



### Memory Operations



### Others:

1. iterator macros:

2. contains:

3. erase_vector:

4. **bit_cast** for C++14/17 by memcpy:

5. enum utils:

6. function overload helper



-------

## <CppMath.hpp>

- **Mathematical Constants** like `pi` for C++14/17, similar as `std::numbers` in C++20

- **clamp** the value between a range, _(will be redirected to `std::clamp` since C++17)_.
- **increase or decrease** the number within a **range** (limit), or **increase or decrease rolling** within a **range**
- **Greatest Common Divisor (GCD)**, and **Lease Common Multiple (LCM)**, _(will be redirected to `std::gcd` and `std::lcm` since C++17)_.
- **midpoint** of two integer or floating point numbers, _(will be redirected to `std::midpoint` since C++20)_.
- **compare** if two **floating numbers** are equal by **epsilon** or **ULP**
- **power of a number, with integer exponent.** _(exponent could be template param since C++17)_
- **factorial** of an integer
- **Linear Interpolation** `(a + (b-a) * t)`, _(will be redirected to `std::lerp` since C++20)_.
- **convert** an angle between **deg** and **rad**



-------

## <CppBit.hpp>

`<bit>` alternatives for C++14/17

in C++20, some functions will redirect to functions in standard library `<bit>` to get better performence.



--------

## <CppScopeGuard.hpp>

refers to:   https://github.com/ricab/scope_guard

[namespace modified to `cutil::`]

- execute any lambda expression while the object destructs (RAII defer lock)
- useful for resource cleaning



------

## <CppStringUtil.hpp>

refers to: https://github.com/Shot511/strutil

[namespace modified to `cutil::str::`]

**additional functions added:**

1. Sanitize Filename
2. convert std::string to numbers



-----

### <Base.h>

1. Get compiler type and version:
2. Get CPU architecture, bit width, features and endian type:
3. Get OS Type:
4. Get C and C++ Language standard:
5. Get if build mode is Debug or Release (`NDEBUG` should be defined):

6. Overload C macros:



--------

## <External/Span.hpp>

refers to: https://github.com/tcbrindle/span

[namespace modified to `cutil::`]



-------

## <External/XorStr.hpp>

refers to: https://github.com/qis/xorstr

​	**≥ C++17 REAUIRED.** only supports intel x86 and ARM architectures

[namespace modified to `cutil::xorstr::`]





-------

## <External/MagicEnum/magic_enum_all.hpp>

refers to: https://github.com/Neargye/magic_enum

​	**≥ C++17 REAUIRED.**

[namespace remained `magic_enum::`]

​	provides **static reflection** for **enums** by special macros provided by MSVC/G++/Clang








---

## <ConsoleUtil.h>:

​	Useful **ANSI Escape code** macros, and some functions for **console output**.

```c++
#include <ConsoleUtil/ConsoleUtil.h> // already wrapped in <ConsoleUtil/ConsoleUtil.h>
```

1. **Set Front Color, Back Color, and font style** for messages to print by printf/cout.

   Forecolors: `FBlack`, `FRed`, `FGreen`, `FYellow`, `FBlue`, `FMagenta`, `FCyan`, `FWhite`, `FDefault`, `FRgb(66, 66, 66)`

   Bright Forecolors: `FGray(=FGrey,FLBlack)`, `FLRed`, `FLGreen`, `FLYellow`, `FLBlue`, `FLMagenta`, `FLCyan`, `FLWhite`;

   Backcolors: `BBlack`, `BRed`, `BGreen`, `BYellow`, `BBlue`, `BMagenta`, `BCyan`, `BWhite`, `BDefault`, `BRgb(66, 66, 66)`;

   Bright Backcolors: `BGray(=BGrey,BLBlack)`, `BLRed`, `BLGreen`, `BLYellow`, `BLBlue`, `BLMagenta`, `BLCyan`, `BLWhite`;

   Font Styles: `CBold`, `CWeak`, `CItalic`, `CUnderLine`, `CFlash`, `CQFlash`, `CInvert`(swap fg and bg colors), `CHide`;

   Reset to Default: `CRst` or `CReset`, you must append this to the end of the string literal to revert console style back to default.

   ```c++
   printf(BRed FLGreen CQFlash "test" CReset "\n");
   	// Red Background, Light Green Text Forecolor, and flashing quickly
   std::cout << CCyan "test" CReset << "\n"; // Text forecolor: cyan
   fmt::println(CYellow "test" CReset);      // Text forecolor: yellow
   ```

   <img src="./assets/Color Effect.png" alt="image-20240218101655956" style="zoom: 60%;" />

   

2. **Control text cursor location** in console, or erase text.

    Move cursor: `CUp(2)`, `CDown(3)`, `CFwd(4)`, `CBack(5)`, `CNextLn(1)`, `CPrevLn(1)`,

    ​	`CHorzPos(12)`(column X, absolute), `CPos(44, 55)`(move the cursor to row 44, column 55)

    Just print them, use individual or append to string literals.

    ```c++
    printf(CForward(2)); // move thr cursor 2 characters right, equals to `CRight(2)` or `CFwd(2)`.
    printf(CCursorPos(15, 20)); // move the text cursor to (15, 20) position
    CUTIL_CONSOLE_CURSOR_POS(15, 20); // equivalent, calls SetConsoleCursorPosition() in win32.
    
    ```

    

3. **set console encoding**, console **window size** (in windows), or **console title**, also with pause program and force abort the program.

    ```c++
    CUTIL_CHCP_ENCODING_UTF8(); 	// switch console encoding to UTF-8 (windows)
    CUTIL_CONSOLE_TITLE("MyProject"); // set console window title (calls SetConsoleTitleA() or SetConsoleTitleW() for windows, and print ansi escape code "\033]0;%s\007" for linux)
    // CUTIL_CONSOLE_TITLE(_TEXT("MyProgram"));
    // CUTIL_CONSOLE_TITLE_A("MyProgram");
    // CUTIL_CONSOLE_TITLE_W(L"MyProgram");
    
    CUTIL_CONSOLE_SIZE(100, 30);	// set console window size to with of 30 chars and height of 30 lines (only available in windows)
    CUTIL_CONSOLE_CLEAR();			// clear console (calls system("cls") )
    
    printf("中文한글\n");	// you can correctly display this when the code saved in UTF-8 Encoding, especially in MSVC Compiler.
    
    ```

    ```c++
    // available encodings:
        CUTIL_CHCP_ENCODING_UTF8();
        CUTIL_CHCP_ENCODING_GB2312();
        CUTIL_CHCP_ENCODING_BIG5();
        CUTIL_CHCP_ENCODING_KOR();
        CUTIL_CHCP_ENCODING_JIS();
        CUTIL_CHCP_ENCODING_LATIN1();
        CUTIL_CHCP_ENCODING_LATIN2();
        CUTIL_CHCP_ENCODING_CYR();
        CUTIL_CHCP_ENCODING_WIN1250();
        CUTIL_CHCP_ENCODING_WIN1251();
        CUTIL_CHCP_ENCODING_WIN1252();
    ```

    - set program locale to `UTF-8`

    ```c++
    CUTIL_LOCALE_UTF8();            // setlocale(LC_ALL, ".UTF-8")
    CUTIL_LOCALE_DEFAULT()			// setlocale(LC_ALL, "")
    CUTIL_LOCALE_UTF8_PRINT()		// print if succeed or not
    ```

    

4. **Print Text only in Debug Build**, and do Not Print in Release Build.

    pls make sure that macro "`_DEBUG`" is defined in Debug Build, or macro "`NDEBUG`" is defined in Release Build.

    ```c++
    int a{1};
    CUTIL_DEBUG_PRINTLN("debug text {}", a); 		// calls fmt::println()(fmtlib) or std::println()(C++23)
    CUTIL_DEBUG_COUT("debug text " << a << '\n'); 	// calls std::cout <<
    CUTIL_DEBUG_PRINTF("debug text %d", a); 		// calls printf()
    // these function-like macros will DO NOTHING IN RELEASE BUILD.
    
    CUTIL_DEBUG_PRINTLN_ERR("debug stderr text {}", a); // print to stderr
    CUTIL_DEBUG_CERR("debug stderr text " << a << '\n');
    CUTIL_DEBUG_PRINTF_ERR("debug stderr text %d", a);
    
    ```



5. Flush the input buffer to ensure that subsequent "scanf()" or "cin" calls receive valid input.

    (吸收输入缓存区内的其余字符, 以便下次 scanf 或 cin 时能够获取到正确的输入内容)

    ```c++
    // #define CUTIL_FLUSH_INPUT_BUFFER()	{char ch; while((ch = getchar()) != '\n') continue;}
    int num1, num2;
    scanf("%d", &num1); // you inputed "123ss", then still remains characters "ss" in the input buffer
    CUTIL_CONSOLE_FLUSH_INPUTBUFFER(); // flush input buffer (clear)
    scanf("%d", &num2); // you can normally input other contents.
    ```



6. **print argc and argv arguments** of main(int argc, char* argv[]) function in sequence.

    ```c++
    int main(int argc, char* argv[]){
    CUTIL_PRINT_ARGV(argc, argv);// print all argc and argv[n] of main() function
    	return 0;
    }
    ```

    <img src="./assets/image-20240224195512767.png" alt="image-20240224195512767" style="zoom:67%;" />

    

7. **Print custom Error Message** with filename, line number and function name

    打印错误信息，并输出当前文件名、行号、函数名

    

8. **EXAMPLES for C**:

    ```c
    #include <locale.h>
    #include <stdio.h>
    #include <windows.h>		// include other headers first
    #include <fmt/core.h>		// include other headers first
    	
    #include <ConsoleUtil/ConsoleUtil.h> 	// include this header at last
    	
    int main(int argc, char* argv[]){
    	CUTIL_CHCP_ENCODING_UTF8(); 		// switch console encoding to UTF-8 (windows)
    	CUTIL_LOCALE_UTF8_PRINT();			// set locale to UTF-8, and print the current locale
    	CUTIL_ENABLE_VIRTUAL_TERMINAL(); 	// enable virtual terminal processing in Windows console, so that ANSI escape codes can be used.
    	CUTIL_CONSOLE_TITLE(_TEXT("MyProject")); 	// set console window title
    	CUTIL_CONSOLE_SIZE(100, 30);		// set console window size to with of 30 chars and height of 30 lines.
    	CUTIL_CONSOLE_CLEAR();				// clear console (system("cls"))
    	
    	CUTIL_PRINT_ARGV(argc, argv);		// print all argc and argv[n] of main() function
    	
    	printf(FLGreen "Hello World!\n" CRst);   	// print "Hello World" with light yellow console color formatting
    													you should put "CRst" at the end of string to RESET console font color to DEFAULT
    	printf(CStyle(FLGreen, "Hello World!\n")); 	// Equivalent
    	
    	fprintf(stderr, FLRed "ERROR\n" CRst);  	// print "ERROR" with font color light red, "CRst" is also needed to revert font color to default
    	fprintf(stderr, CStyle(FLRed, "ERROR\n"));	// Equivalent
    	
    	printf(BRed FGreen CQFlash "test\n" CRst);  // Print text with green font and red background, and quickly flashing
    	printf(CStyle(BRed FGreen CQFlash, "test\n"));// Equivalent
    	
    	printf(CForward(2)); 					// move thr cursor 2 characters right, equals to `CRight(2)` or `CFwd(2)`.
    	
    	CUTIL_ERROR_MESSAGE("error occured!"); 	// print an error message with filename, function name and line number ATTACHED.
    	
    	CUTIL_CONSOLE_PAUSE(); 			 		// system("pause");
    	return 0;
    }
    ```

9. **EXAMPLES for C++**:

   ```c++
   #include <clocale>
   #include <iostream>
   #include <fmt/core.h> // optional
   #include <windows.h>  // windows only
   #include <ConsoleUtil/ConsoleUtil.h> 	// include this header at last
   	
   int main(int argc, char* argv[]){
   	cutil::console::set_locale_utf8(); 			// set locale to UTF-8
   	cutil::console::set_chcp_encoding(cutil::console::Encodings::UTF8); // set console encoding to UTF-8, you can also use `set_chcp_encoding_utf8()`
   	cutil::console::enable_virtual_terminal();	// enable virtual terminal processing in Windows console, so that ANSI escape codes can be used.
   	cutil::console::set_title("MyProject"); 	// set console window title
   	cutil::console::set_size(100, 30); 			// set console window size to with of 30 chars and height of 30 lines.
   	cutil::console::clear(); 					// clear console (system("cls"))
   	
   	cutil::console::print_argv(argc, argv); 	// print all argc and argv[n] of main() function
   	
   	fmt::println(FLGreen "Hello World!" CRst); 	// print "Hello World" with light green console color formatting
   	fmt::println(stderr, FLRed "ERROR" CRst); 	// print "ERROR" with font color light red
   	
   	fmt::println(BRed FGreen CQFlash "test" CRst); // Print text with green font and red background, and quickly flashing
   	
   	cutil::console::pause(); 					// system("pause");
   	return 0;
   }
   ```

   

10. **Console Effects 控制台效果** :

<img src="./assets/Example Effects.png" alt="image-20231205152753735" style="zoom:67%;" />

<img src="./assets/Color Effect.png" alt="image-20240218101655956" style="zoom:67%;" />
