#include <iostream>

#include "ConsoleUtil/ConsoleUtil.h"
#include <gtest/gtest.h>


TEST(Console, Console){
	std::cout << FLYellow "Hello World!" CReset << std::endl;
}
