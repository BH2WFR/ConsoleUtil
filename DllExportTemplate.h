#ifndef DLL_SYMBOL_EXPORT_TEMPLATE__
#define DLL_SYMBOL_EXPORT_TEMPLATE__


//#if defined(_WIN32) || defined(WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#if defined(_WIN32) //* Windows 操作系统限定, 需要在动态库项目中增加全局宏定义 BUILD_DLL
	#if defined(BUILD_DLL) || defined(PROJ_BUILD_DLL)
		//* 需要将这里的所有 "OS_" 改成自己项目的名字, 防止交叉引用动态库出现问题
		#define OS_API __declspec(dllexport) //dll 动态库工程中，导出符号 (针对 dll 项目)
	#else // BUILD_DLL
		#define OS_API __declspec(dllimport) //调用 dll 的工程中，导入符号
	#endif // BUILD_DLL
#else // unix, linux 下不使用这个东西, .so 中的函数和类不需要额外声明
	#define OS_API
#endif // WIN32
//#endif // USE_DLL_EXPORT


/* 
* ===================== 使用说明: ==================
1. 在 动态库项目 (target) 中 增加全局宏定义 "BUILD_DLL"
	CMake 样例: 添加到 target 项目中, "${PROJECT_NAME}" 改成自己的 target 项目名字
		target_compile_definitions(${PROJECT_NAME} PRIVATE BUILD_DLL=1)
		
2. 将此文件复制到 DLL 项目中, 并确保 项目所所有头文件内都 include 这个文件
	且必须将这里的 "OS" 改成自己项目的名字, 防止出现动态库交叉引用时的问题

3. 在需要外部导出的类或函数中加入这个宏定义

* 如, 在一个叫 "TestProject" 的动态库项目中:
	a. 需要创建一个单独的头文件 (这里叫 "TestProjectGlobal.h")
	b. 向这个头文件里面拷贝上面的宏定义, 并将宏定义名称 OS_API 全部根据项目名改为 TEST_PROJECT_API
	c. 然后将这个头文件 include 进动态库项目的所有头文件中
	d. 向需要外部暴露的所有类名/函数名等符号加入 "TEST_PROJECT_API" 这个宏定义, 如:
		class TEST_PROJECT_API MyClass {};
		void  TEST_PROJECT_API MyFunction() {}
		

*/

#endif //DLL_SYMBOL_EXPORT_TEMPLATE__
