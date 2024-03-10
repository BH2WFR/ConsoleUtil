/* UTF-8 encoding
* Project URL: https://github.com/BH2WFR/ConsoleUtil
  Author:		BH2WFR
*/
#ifndef CONSOLEUTIL_CUDA_UTIL_H__
#define CONSOLEUTIL_CUDA_UTIL_H__

#include <ConsoleUtil/CppUtil.h>
#include <ConsoleUtil/ConsoleUtil.h>


//==================== CUDA Utils ==========================
#ifdef __CUDACC__ //* CUDA 错误检查与退出机制

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

#endif // __CUDACC__





#endif // CONSOLEUTIL_CUDA_UTIL_H__
