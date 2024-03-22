# ConsoleUtil

A **HEADER FILE** project with macros that can change text color/style and move cursor in CONSOLE by ANSI Escape Codes, and some utility macros for CUDA and Qt.



<img src="./assets/Example Effects.png" alt="image-20231205152753735" style="zoom: 50%;" />

**Homepage**:  https://github.com/BH2WFR/ConsoleUtil

**author**: 	BH2WFR

**LICENSE**: 	**MIT** License

Reference of Ansi Escape Codes: 

- https://en.wikipedia.org/wiki/ANSI_escape_code

- https://zh.wikipedia.org/wiki/ANSI%E8%BD%AC%E4%B9%89%E5%BA%8F%E5%88%97



----------

### WARNING:

- features using Ansi Escape code (like color customizing, or cursor moving macros in this header file) **DO NOT SUPPORT Windows version lower than Windows 10 1511**, otherwise it can't display properly in windows cmd.
    - If you are using these operating systems, pls `#define CONSOLE_UTIL_ANSI_UTIL_UNSUPPORTED  1` before `#include <ConsoleUtil/ConsoleUtil.h>` to disable features by printing Ansi Escape Code.

- Pls #include the header file <`ConsoleUtil/ConsoleUtil.h`> after other header files, especially those from libraries such as Qt/fmtlib. DO NOT #include <`ConsoleUtil/ConsoleUtil.h`> in header files.

- You can include <`ConsoleUtil/CppUtil.h`> in header files.  No need to include <`ConsoleUtil/CppUtil.h`> in source files if you already included <`ConsoleUtil/ConsoleUtil.h`>, because it has been included in <`ConsoleUtil/ConsoleUtil.h`>.





---

### Major Features:
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
    printf(CForward(2)); // move thr cursor 2 characters right
    printf(CCursorPos(15, 20)); // move the text cursor to (15, 20) position
    CUTIL_CONSOLE_CURSOR_POS(15, 20); // equivalent, calls SetConsoleCursorPosition() in win32.
    ```

    

3. **set console encoding**, console **window size** (in windows), or **console title**, also with pause program and force abort the program.

    ```c++
    CUTIL_CHCP_ENCODING_UTF8(); 	// switch console encoding to UTF-8 (windows)
    CUTIL_CONSOLE_TITLE("MyProject"); // set console window title
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

4. **Print Text only in Debug Build**, and do Not Print in Release Build.

    pls make sure that macro "`_DEBUG`" is defined in Debug Build, or macro "`NDEBUG`" is defined in Release Build.

    ```c++
    int a{1};
    CUTIL_DEBUG_PRINTLN("debug text {}", a); 		// calls fmt::println()(fmtlib) or std::println()(C++23)
    CUTIL_DEBUG_COUT("debug text " << a << '\n'); 	// calls std::cout <<
    CUTIL_DEBUG_PRINTF("debug text %d", a); 		// calls printf()
    // these function-like macros will DO NOTHING IN RELEASE BUILD.
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

    

    

8. **Other useful C/C++ Macros**
   
    ```c++
    #include <ConsoleUtil/CppUtil.h>
    // already wrapped in <ConsoleUtil/ConsoleUtil.h>, you can include the latter instead in source files.
    // <ConsoleUtil/CppUtil.h> can be included in header files.
    ```
    - decide if the project is under debug build or Release build mode.
      
        in MSVC, macro `_DEBUG` is defined under debug build; in GCC, macro `NDEBUG` is defined under release build.
        
        you can add `add_compile_definitions("$<IF:$<CONFIG:Debug>,_DEBUG,NDEBUG>")` in CMake.
        
        ```c++
        #include <ConsoleUtil/CppUtil.h>
        #if CUTIL_DEBUG_BUILD // Debug
            //...
        #else // Release RelWithDebInfo MinSizeRel
            //...
        #endif
        ```
        
    - set bit to a unsigned integer variable in some hardware projects
    
        ```c++
        #include <ConsoleUtil/CppUtil.h>
        uint16_t num {0b00000000'00000001}; // C++14
        // the 2nd parameter is the index of bit, starts at 0
        CUTIL_BIT_SET(num, 0);		// equals to (num |=  (1u << 0));
        CUTIL_BIT_CLEAR(num, 2);	// equals to (num &= ~(1u << 2));
        CUTIL_BIT_TOGGLE(num, 3);	// equals to (num ^=  (1u << 3));
        
        if(CUTIL_BIT_GET(num, 0) != 0){ // reading bit, if bit is 1, returns (1<<BIT_IDX), NOT 1
        	printf("%x\n", num);
        }
        ```
    
    - swap variables in C (do not use in C++, pls replace with std::swap()), or get the maximum or minimum item between two numbers;
    
        ```c
        #include <ConsoleUtil/CppUtil.h>
        int a = 1, b = 2;
        CUTIL_SWAP_VARS(int, a, b); // declare type in 3rd arg.
        CUTIL_SWAP_VARS(typeof(a), a, b); // GNU C only
        CUTIL_SWAP_VARS_GNU(a, b); 			// GNU C only
        
        int max_ab = CUTIL_GET_MAX(a, b); // maximum number between a and b
        int min_ab = CUTIL_GET_MIN(a, b); // minimum number between a and b
        ```
    
    - count amount of arguments (up to 35)
    
        ```c
        #include <ConsoleUtil/CppUtil.h>
        int a = CUTIL_VA_CNT(); 			// -> 0
        int b = CUTIL_VA_CNT(b1); 			// -> 1
        int c = CUTIL_VA_CNT(c1, c2); 		// -> 2
        int c = CUTIL_VA_CNT(c1, c2, c3); 	// -> 3
        ```
    
    - match C++ language version, especially if you want to let the project build both by MSVC and G++.
    
        equals to "`_MSVC_LANG`" for MSVC, and "`__cplusplus`" for other compilers.
    
        ```c++
        #include <ConsoleUtil/CppUtil.h>
        #if CUTIL_CPP_VER >= 199711L	// C++98
        #if CUTIL_CPP_VER >= 201103L	// C++11
        #if CUTIL_CPP_VER >= 201402L	// C++14
        #if CUTIL_CPP_VER >= 201703L	// C++17
        #if CUTIL_CPP_VER >= 202002L	// C++20
        #if CUTIL_CPP_VER >= 202302L	// C++23 (temporary unsupported)
        ```
        
    -  set C++11 class constructor/moving/copying to disabled/default
        ```c++
        #include <ConsoleUtil/CppUtil.h>
        class MyClass{
        public:
            CUTIL_CLASS_DEFAULT_CONSTRUCTOR(MyClass) // generates MyClass(), ~MyClass() = default;
            
            CUTIL_CLASS_DISABLE_COPY_MOVE(MyClass) // cannot move or copy this class
            // =delete: MyClass(const MyClass&), operator=(const MyClass&), MyClass(MyClass&&), operator=(MyClass&&),
        }
        
        class MyClass{
        public:
            CUTIL_CLASS_DEFAULT_FUNCTIONS(MyClass)
            // generates 6 functions =default: MyClass(), ~MyClass(), MyClass(const MyClass&),
            //     operator=(const MyClass&), MyClass(MyClass&&), operator=(MyClass&&)
        }
        /* available macros:
        #define CUTIL_CLASS_DEFAULT_CONSTRUCTOR(_CLASS_NAME)
        #define CUTIL_CLASS_DISABLE_COPY(_CLASS_NAME)
        #define CUTIL_CLASS_DEFAULT_COPY(_CLASS_NAME)
        #define CUTIL_CLASS_DISABLE_MOVE(_CLASS_NAME)
        #define CUTIL_CLASS_DEFAULT_MOVE(_CLASS_NAME)
        #define CUTIL_CLASS_DISABLE_COPY_MOVE(_CLASS_NAME)
        #define CUTIL_CLASS_DEFAULT_COPY_MOVE(_CLASS_NAME)
        #define CUTIL_CLASS_DEFAULT_FUNCTIONS(_CLASS_NAME)
        */
        ```
        
    -  memory allocation and operations for C (wrapped `malloc()` `free()` `memset()` `memcpy()` with typename to macros)
    
        ```c
        #include <ConsoleUtil/CppUtil.h>
        
        const size_t length = 20; // length of numbers
        uint32_t* aD1 = CUTIL_TYPE_MALLOC(uint32_t, length);
        	// std::vector<uint32_t> v1(20); -> elements == 0xCDCDCDCD in heap
        uint32_t* aD2 = CUTIL_TYPE_CALLOC(uint32_t, length); // std::vector<uint32_t> v1(20, 0x00000000);
        uint32_t aD3[length]; // C99 VLA, unsupported in C++, -> elements == 0xCCCCCCCC in stack
        
        uint32_t* aD3 = CUTIL_TYPE_MEMSET(uint32_t, length, 0x66, aD1);
        	// set all elements of aD1 to 0x66666666, returns aD3 == aD1
        uint32_t* aD4 = CUTIL_TYPE_MEMMOVE(uint32_t, length, aD2, aD1);
        	// copy aD1 elements to aD2, returns aD4==aD2
        uint32_t* aD5 = CUTIL_TYPE_MEMCPY(uint32_t, length, aD2, aD1);  // equivalents to above.
        
        int compResult = CUTIL_TYPE_MEMCMP(uint32_t, length, aD1, aD2);
        	// returns 0, contents of mem blocks equal.
        
        CUTIL_TYPE_FREE(aD1); // element values -> 0xDDDDDDDD (deleted heap)
        CUTIL_TYPE_FREE(aD2);
        
        ```
        
        


9. **Some Macros for Qt Projects**:

    ```c++
    #include <ConsoleUtil/QtUtil.h>
    // already wrapped in <ConsoleUtil/ConsoleUtil.h>, you can include the latter instead.
    ```

    - Enable **High DPI Support for Qt5** programs (enable since Qt5.6.0, and fractional scaling since Qt5.14.0). Qt6 supports it by default.

    - Set **Qt5 TextCodec Encoding**, like UTF-8 or GBK to let qDebug() correctly displays Chinese characters with UTF-8 code page and MSVC compiler.

        ```c++
        #include <qglobal.h>
        #include <QApplication>
        #include <QDebug>
        #include <QTextCodec> // include Qt headers first
        
        #include <ConsoleUtil/ConsoleUtil.h> // <ConsoleUtil/QtUtil.h> has been wrapped in this header.
        
        int main(int argc, char* argv[])
        {
            CUTIL_QT5_HIGH_DPI(); 	  	//* enable Qt5 high DPI support
        
            CUTIL_CHCP_ENCODING_UTF8();
            CUTIL_QT5_TEXTCODEC_UTF8(); //* set Qt default text encoding to UTF-8
        
            QApplication app(argc, argv); // you must create QCoreApplication after these macros.
        
            return app.exec();
        }
        /* available encodings:
            CUTIL_QT5_TEXTCODEC_UTF8()
            CUTIL_QT5_TEXTCODEC_GBK()
            CUTIL_QT5_TEXTCODEC_BIG5()
            CUTIL_QT5_TEXTCODEC_EUCKR()
            CUTIL_QT5_TEXTCODEC_EUCJP()
            CUTIL_QT5_TEXTCODEC_JIS()
        */
        ```
        

    

9. **Some Macros for CUDA Programs**:

    ```c++
    #include <ConsoleUtil/CudaUtil.h>
    // already wrapped in <ConsoleUtil/ConsoleUtil.h>, you can include the latter instead.
    ```

    ...

     



----------------

### How To Use for CMake Projects:

1. use `find_package()` in `CMakeLists.txt` of your project to find "`ConsoleUtil`" CMake package.

    Set variable "`ConsoleUtil_DIR`" previously to the folder `ConsoleUtil/cmake`, with file `ConsoleUtilConfig.cmake` inside.

    ```cmake
    set(ConsoleUtil_DIR "D:/3rdlibs/ConsoleUtil/cmake") # there's file `ConsoleUtilConfig.cmake`
    find_package(ConsoleUtil REQUIRED) # find ConsoleUtil package
    ```

2. link "`ConsoleUtil::ConsoleUtil`" to your target.

   ```cmake
   project(myProject LANGUAGES CXX)
   add_executable( ${PROJECT_NAME} "main.cpp") # create a app target
   
   target_link_libraries( ${PROJECT_NAME}
   	ConsoleUtil::ConsoleUtil 	# this header-only Library
       # fmt::fmt-header-only 		# other 3rd libraries
   )
   ```

3. include "`ConsoleUtil/ConsoleUtil.h`" in your source file, and check if there's macro `CONSOLE_UTIL_VERSION` equals to version number.

     ```c++
     #include <ConsoleUtil/ConsoleUtil.h> // wrapped all 3 below inside
     // #include <ConsoleUtil/CppUtil.h> // you can include this alone within header files
     // #include <ConsoleUtil/QtUtil.h>
     // #include <ConsoleUtil/CudaUtil.h>
     ```



---

### Example 使用样例:

```cpp
#include <print.h>			// C++23
#include <windows.h>		// include other headers first
#include <fmt/core.h>		// include other headers first
	
#include <ConsoleUtil/ConsoleUtil.h> 	// include this header at last
	
int main(int argc, char* argv[]){
	CUTIL_CHCP_ENCODING_UTF8(); 	// switch console encoding to UTF-8 (windows)
	CUTIL_CONSOLE_TITLE("MyProject"); // set console window title
	CUTIL_CONSOLE_SIZE(100, 30);		// set console window size to with of 30 chars and height of 30 lines.
	CUTIL_CONSOLE_CLEAR();			// clear console (system("cls"))
	
	CUTIL_PRINT_ARGV(argc, argv);	// print all argc and argv[n] of main() function
	
	printf(FLGreen "Hello World!\n" CReset);   // print "Hello World" with light yellow console color formatting
													you should put "CReset" at the end of string to RESET console font color to DEFAULT
	printf(CStyle(FLGreen, "Hello World!\n")); // Equivalent
	
	std::cout << FLRed "ERROR\n" CReset;  // print "ERROR" with font color light red, "CReset" is also needed to revert font color to default
	std::cout << CStyle(FLRed, "ERROR\n");// Equivalent
	
	printf(BRed FGreen CQFlash "test\n" CReset);  // Print text with green font and red background, and quickly flashing
	printf(CStyle(BRed FGreen CQFlash, "test\n"));// Equivalent
	
	
	printf(CForward(2)); // move thr cursor 2 characters right
	
	
	CUTIL_PRINT_ERR("error occurred!"); // print an error message with filename, function name and line number ATTACHED.
	
	CUTIL_CONSOLE_PAUSE(); 			 // system("pause");
	
	return 0;
}
```



**Console Effects 控制台效果** :

![image-20231205152753735](./assets/Example Effects.png)

<img src="./assets/Color Effect.png" alt="image-20240218101655956" style="zoom:67%;" />
