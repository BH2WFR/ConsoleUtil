# ConsoleUtil

一个可以对 C\C++ 命令行 更改颜色/移动光标 的**头文件**, 利用 ANSI 控制字符, 且含一些常见懒人包

A **HEADER FILE** with macros that can change text color/style and move corsor in CONSOLE by ANSI Escape Codes, and some utility macros for CUDA and Qt

WARNINT: for Windows system, **Only Windows 10/11 is supported**. These macros cannot work properly in Windows 8/7/vista/xp or prior versions.



### 主要功能 Major Features:

1. 向命令行 printf/cout 时 **设置输出文本的 颜色、背景颜色、特殊效果** （借助 ANSI 转义序列 命令行控制字符 `\033[**m`）

   **Set Front Color, Back Color, and font style** for messages to print by printf/cout.

   例 Sample:

   ```c++
   printf(SETCOLOR(BRed CGreen CQFlash, "test\n")); // 红底绿色, 并快速闪烁
   std::cout << SETCOLOR(CCyan, "test\n");   // 字符颜色为 暗青色
   fmt::println(SETCOLOR(CLYellow, "test")); // 字符颜色为 亮黄色
   ```

   

2. 控制命令行光标，部分擦除命令行内容（借助 ANSI 转义序列 命令行控制字符 `\033[**m`）

    **Control cursor location** in console, and erase text.

    

3. 设置命令行编码为 UTF-8、清空命令行、设置命令行窗口大小、标题、暂停程序、强行退出程序（借助 stdlib.h 中的 system() 函数, 部分功能需要 windows 操作系统下才能完成）

    **set console encoding to UTF-8**, console **window size** (in windows), or **console title**, also with pause program and force abort the program.

    

4. 按顺序打印 main 函数的 argc 和 argv 参数

    **print argc and argv arguments** of main(int argc, char* argv[]) function in sequence.

    

5. 打印错误信息，并输出当前文件名、行号、函数名

    **Print costom Error Message** with filename, line number and function name

    

6. 其他一系列 C/C++ 语法糖懒人包

    

7. CUDA 中，检测部分函数的返回状态，如 != cudaSuccess 则输出错误信息，或强行退出程序

    

8. Qt 中，部分语法糖懒人包，和 Qt5 GUI 程序中的高分屏适配\

    

**ANSI 转义序列 参考**：https://zh.wikipedia.org/wiki/ANSI%E8%BD%AC%E4%B9%89%E5%BA%8F%E5%88%97



### 使用样例 Example of using:

```cpp
int main(int argc, char* argv[]){
	CONSOLE_ENCODING_UTF8(); 	// switch console encoding to UTF-8 (windows)
	CONSOLE_TITLE("MyProject"); // set console window title
	CONSOLE_SIZE(100, 30);		// set console window size to with of 30 chars and height of 30 lines.
	CONSOLE_CLEAR();			// clear console (system("cls"))
	
	PRINT_ARGV(argc, argv);		// print all argc and argv[n] of main() function
	
	printf(FLGreen "Hello World!\n" CReset);   // print "Hello World" with light yellow console color formatting
												//	you should put "CReset" at the end of string to RESET console font color to DEFAULT
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
```



**控制台效果 Console Effects:**

![image-20231205152753735](./assets/image-20231205152753735.png)

![image-20240218101655956](./assets/image-20240218101655956.png)



# DllExportTemplate

使用说明:

1. 在 **动态库项目 (target)** 中 增加全局宏定义 `BUILD_DLL`
   CMake 样例: 添加到 target 项目中, `${PROJECT_NAME}` 改成自己的 target 项目名字

   ``cmake target_compile_definitions(${PROJECT_NAME} PRIVATE BUILD_DLL=1) ``
2. 将此文件复制到 DLL 项目中, 并确保 项目中 **所有头文件内都 include 这个文件**
   且必须**将这里的 `OS_` 改成自己项目的名字**, 防止出现动态库交叉引用时的问题
3. 在需要外部导出的类或函数中加入这个宏定义

#### 如, 在一个叫 "TestProject" 的动态库项目中:

1. 增加全局宏定义 `BUILD_DLL`，

   ```cmake
   target_compile_definitions(TestProject PRIVATE BUILD_DLL=1)
   ```
2. 需要创建一个单独的头文件 (这里叫 `TestProjectGlobal.h`)
3. 向这个头文件里面拷贝上面的宏定义, 并**将宏定义名称 `OS_API` 全部根据项目名改为 `TEST_PROJECT_API`**
4. 然后将 `TestProjectGlobal.h` **include 进动态库项目的所有头文件中**
5. 在动态库头文件中，向需要外部暴露的所有类名/函数名等符号加入 `TEST_PROJECT_API` 这个宏定义, 如:

   ```c++
   // 动态库中的所有头文件
   #include "TestProjectGlobal.h"
   
   class TEST_PROJECT_API MyClass {
   
   };
   
   void  TEST_PROJECT_API MyFunction();
   ```
