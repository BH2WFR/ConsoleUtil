#include <iostream>
#include <windows.h>

#include <ConsoleUtil/All.h>

#include <gtest/gtest.h>

#include <vector>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <array>
#include <deque>
#include <list>
#include <forward_list>
#include <stack>
#include <queue>
#include <algorithm>
#include <bit>
#include <execution>

int main(int argc, char* argv[])
{
	CUTIL_CHCP_ENCODING_UTF8();
	CUTIL_CONSOLE_TITLE("ConsoleUtil Test");
	CUTIL_CONSOLE_SIZE(100, 30);
	CUTIL_CONSOLE_CLEAR();
	
	CUTIL_PRINT_ARGV(argc, argv);
	
	printf(FLGreen "Hello World!\n" CReset);
	std::cout << FLRed "ERROR\n" CReset;
	
	std::atexit([]{printf("cpp lang=%d\n", CUTIL_CPP_LANG);});
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

TEST(BoolStatement, equal_any)
{
	EXPECT_EQ(true,  cutil::equal_any(1, 1));
	EXPECT_EQ(false, cutil::equal_any(1, 2));
	EXPECT_EQ(true,  cutil::equal_any(1, 1, 2));
	EXPECT_EQ(false, cutil::equal_any(1, 2, 3));
	EXPECT_EQ(true,  cutil::equal_any(1, 2, 1));
	EXPECT_EQ(true,  cutil::equal_any(1, 1, 1));
	EXPECT_EQ(true,  cutil::equal_any(1, 1, 2, 3));
	EXPECT_EQ(true,  cutil::equal_any(1, 2, 3, 1));
	EXPECT_EQ(false, cutil::equal_any(1, 2, 3, 4));
	
	EXPECT_EQ(true,  CUTIL_EQUAL_ANY(1, 1));
	EXPECT_EQ(false, CUTIL_EQUAL_ANY(1, 2));
	EXPECT_EQ(true,  CUTIL_EQUAL_ANY(1, 1, 2));
	EXPECT_EQ(false, CUTIL_EQUAL_ANY(1, 2, 3));
	EXPECT_EQ(true,  CUTIL_EQUAL_ANY(1, 2, 1));
	EXPECT_EQ(true,  CUTIL_EQUAL_ANY(1, 1, 1));
	EXPECT_EQ(true,  CUTIL_EQUAL_ANY(1, 1, 2, 3));
	EXPECT_EQ(true,  CUTIL_EQUAL_ANY(1, 2, 3, 1));
	EXPECT_EQ(false, CUTIL_EQUAL_ANY(1, 2, 3, 4));
}
TEST(BoolStatement, equal_all)
{
	EXPECT_EQ(true,  cutil::equal_all(1, 1));
	EXPECT_EQ(false, cutil::equal_all(1, 2));
	EXPECT_EQ(false, cutil::equal_all(1, 1, 2));
	EXPECT_EQ(false, cutil::equal_all(1, 2, 3));
	EXPECT_EQ(false, cutil::equal_all(1, 2, 1));
	EXPECT_EQ(true,  cutil::equal_all(1, 1, 1));
	EXPECT_EQ(false, cutil::equal_all(1, 1, 2, 3));
	EXPECT_EQ(false, cutil::equal_all(1, 2, 3, 1));
	EXPECT_EQ(false, cutil::equal_all(1, 2, 3, 4));
	EXPECT_EQ(false, cutil::equal_all(1, 2, 1, 1));
	EXPECT_EQ(true,  cutil::equal_all(1, 1, 1, 1));
	
	EXPECT_EQ(true,  CUTIL_EQUAL_ALL(1, 1));
	EXPECT_EQ(false, CUTIL_EQUAL_ALL(1, 2));
	EXPECT_EQ(false, CUTIL_EQUAL_ALL(1, 1, 2));
	EXPECT_EQ(false, CUTIL_EQUAL_ALL(1, 2, 3));
	EXPECT_EQ(false, CUTIL_EQUAL_ALL(1, 2, 1));
	EXPECT_EQ(true,  CUTIL_EQUAL_ALL(1, 1, 1));
	EXPECT_EQ(false, CUTIL_EQUAL_ALL(1, 1, 2, 3));
	EXPECT_EQ(false, CUTIL_EQUAL_ALL(1, 2, 3, 1));
	EXPECT_EQ(false, CUTIL_EQUAL_ALL(1, 2, 3, 4));
	EXPECT_EQ(false, CUTIL_EQUAL_ALL(1, 2, 1, 1));
	EXPECT_EQ(true,  CUTIL_EQUAL_ALL(1, 1, 1, 1));
}
TEST(BoolStatement, unequal_any)
{
	EXPECT_EQ(false, cutil::unequal_any(1, 1));
	EXPECT_EQ(true,  cutil::unequal_any(1, 2));
	EXPECT_EQ(true,  cutil::unequal_any(1, 1, 2));
	EXPECT_EQ(true,  cutil::unequal_any(1, 2, 3));
	EXPECT_EQ(true,  cutil::unequal_any(1, 2, 1));
	EXPECT_EQ(false, cutil::unequal_any(1, 1, 1));
	EXPECT_EQ(true,  cutil::unequal_any(1, 1, 2, 3));
	EXPECT_EQ(true,  cutil::unequal_any(1, 2, 3, 1));
	EXPECT_EQ(true,  cutil::unequal_any(1, 2, 3, 4));
	EXPECT_EQ(true,  cutil::unequal_any(1, 2, 1, 1));
	EXPECT_EQ(false, cutil::unequal_any(1, 1, 1, 1));
	
	EXPECT_EQ(false, CUTIL_UNEQUAL_ANY(1, 1));
	EXPECT_EQ(true,  CUTIL_UNEQUAL_ANY(1, 2));
	EXPECT_EQ(true,  CUTIL_UNEQUAL_ANY(1, 1, 2));
	EXPECT_EQ(true,  CUTIL_UNEQUAL_ANY(1, 2, 3));
	EXPECT_EQ(true,  CUTIL_UNEQUAL_ANY(1, 2, 1));
	EXPECT_EQ(false, CUTIL_UNEQUAL_ANY(1, 1, 1));
	EXPECT_EQ(true,  CUTIL_UNEQUAL_ANY(1, 1, 2, 3));
	EXPECT_EQ(true,  CUTIL_UNEQUAL_ANY(1, 2, 3, 1));
	EXPECT_EQ(true,  CUTIL_UNEQUAL_ANY(1, 2, 3, 4));
	EXPECT_EQ(true,  CUTIL_UNEQUAL_ANY(1, 2, 1, 1));
	EXPECT_EQ(false, CUTIL_UNEQUAL_ANY(1, 1, 1, 1));
	
}
TEST(BoolStatement, unequal_all)
{
	EXPECT_EQ(false, cutil::unequal_all(1, 1));
	EXPECT_EQ(true,  cutil::unequal_all(1, 2));
	EXPECT_EQ(false, cutil::unequal_all(1, 1, 2));
	EXPECT_EQ(true,  cutil::unequal_all(1, 2, 3));
	EXPECT_EQ(false, cutil::unequal_all(1, 2, 1));
	EXPECT_EQ(false, cutil::unequal_all(1, 1, 1));
	EXPECT_EQ(false, cutil::unequal_all(1, 1, 2, 3));
	EXPECT_EQ(false, cutil::unequal_all(1, 2, 3, 1));
	EXPECT_EQ(true,  cutil::unequal_all(1, 2, 3, 4));
	EXPECT_EQ(true, cutil::unequal_all(1, 2, 2, 2));
	
	EXPECT_EQ(false, CUTIL_UNEQUAL_ALL(1, 1));
	EXPECT_EQ(true,  CUTIL_UNEQUAL_ALL(1, 2));
	EXPECT_EQ(false, CUTIL_UNEQUAL_ALL(1, 1, 2));
	EXPECT_EQ(true,  CUTIL_UNEQUAL_ALL(1, 2, 3));
	EXPECT_EQ(false, CUTIL_UNEQUAL_ALL(1, 2, 1));
	EXPECT_EQ(false, CUTIL_UNEQUAL_ALL(1, 1, 1));
	EXPECT_EQ(false, CUTIL_UNEQUAL_ALL(1, 1, 2, 3));
	EXPECT_EQ(false, CUTIL_UNEQUAL_ALL(1, 2, 3, 1));
	EXPECT_EQ(true,  CUTIL_UNEQUAL_ALL(1, 2, 3, 4));
	EXPECT_EQ(true,  CUTIL_UNEQUAL_ALL(1, 2, 2, 2));
}
TEST(BoolStatement, unequal_mutually)
{
	EXPECT_EQ(false, cutil::unequal_mutually(1, 1));
	EXPECT_EQ(true, cutil::unequal_mutually(1, 2));
	EXPECT_EQ(false, cutil::unequal_mutually(1, 1, 2));
	EXPECT_EQ(true, cutil::unequal_mutually(1, 2, 3));
	EXPECT_EQ(false, cutil::unequal_mutually(1, 2, 1));
	EXPECT_EQ(false, cutil::unequal_mutually(1, 1, 1));
	EXPECT_EQ(false, cutil::unequal_mutually(1, 1, 2, 3));
	EXPECT_EQ(false, cutil::unequal_mutually(1, 2, 3, 1));
	EXPECT_EQ(true, cutil::unequal_mutually(1, 2, 3, 4));
	EXPECT_EQ(false, cutil::unequal_mutually(1, 2, 2, 4));
	EXPECT_EQ(false, cutil::unequal_mutually(1, 2, 3, 3));
	
	EXPECT_EQ(false, CUTIL_UNEQUAL_MUTUALLY(1, 1));
	EXPECT_EQ(true, CUTIL_UNEQUAL_MUTUALLY(1, 2));
	EXPECT_EQ(false, CUTIL_UNEQUAL_MUTUALLY(1, 1, 2));
	EXPECT_EQ(true, CUTIL_UNEQUAL_MUTUALLY(1, 2, 3));
	EXPECT_EQ(false, CUTIL_UNEQUAL_MUTUALLY(1, 2, 1));
	EXPECT_EQ(false, CUTIL_UNEQUAL_MUTUALLY(1, 1, 1));
	EXPECT_EQ(false, CUTIL_UNEQUAL_MUTUALLY(1, 1, 2, 3));
	EXPECT_EQ(false, CUTIL_UNEQUAL_MUTUALLY(1, 2, 3, 1));
	EXPECT_EQ(true, CUTIL_UNEQUAL_MUTUALLY(1, 2, 3, 4));
	EXPECT_EQ(false, CUTIL_UNEQUAL_MUTUALLY(1, 2, 2, 4));
	EXPECT_EQ(false, CUTIL_UNEQUAL_MUTUALLY(1, 2, 3, 3));
	
}


TEST(Range, contains)
{
	std::vector<int> v1 = {1, 2, 3, 4, 5};
	std::map<int, int> m1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
	std::set<int> s1 = {1, 2, 3, 4, 5};
	std::unordered_map<int, int> um1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
	std::unordered_set<int> us1 = {1, 2, 3, 4, 5};
	std::array<int, 5> a1 = {1, 2, 3, 4, 5};
	std::deque<int> d1 = {1, 2, 3, 4, 5};
	std::list<int> l1 = {1, 2, 3, 4, 5};
	std::forward_list<int> fl1 = {1, 2, 3, 4, 5};
	std::stack<int> st1;
	st1.push(1); st1.push(2); st1.push(3); st1.push(4); st1.push(5);
	std::queue<int> q1;
	q1.push(1); q1.push(2); q1.push(3); q1.push(4); q1.push(5);
	
	EXPECT_EQ(true, cutil::contains(v1, 2));
	EXPECT_EQ(false, cutil::contains(v1, 0));
	EXPECT_EQ(true, cutil::contains(m1, std::pair<int, int>(2, 2)));
	EXPECT_EQ(false, cutil::contains(m1, std::pair<int, int>(2, 3)));
	EXPECT_EQ(true, cutil::contains(s1, 2));
	EXPECT_EQ(false, cutil::contains(s1, 0));
	EXPECT_EQ(true, cutil::contains(um1, std::pair<int, int>(2, 2)));
	EXPECT_EQ(false, cutil::contains(um1, std::pair<int, int>(2, 3)));
	EXPECT_EQ(true, cutil::contains(us1, 3));
	EXPECT_EQ(false, cutil::contains(us1, 0));
	EXPECT_EQ(true, cutil::contains(a1, 2));
	EXPECT_EQ(false, cutil::contains(a1, 0));
	EXPECT_EQ(true, cutil::contains(d1, 2));
	EXPECT_EQ(false, cutil::contains(d1, 0));
	EXPECT_EQ(true, cutil::contains(l1, 2));
	EXPECT_EQ(false, cutil::contains(l1, 0));
	EXPECT_EQ(true, cutil::contains(fl1, 2));
	EXPECT_EQ(false, cutil::contains(fl1, 0));
	
#ifdef CUTIL_CPP17_SUPPORTED
	EXPECT_EQ(true, cutil::contains(std::execution::seq, v1, 2));
	EXPECT_EQ(false, cutil::contains(std::execution::seq, v1, 0));
#endif
	
	// EXPECT_EQ(true, cutil::contains(st1, 2));
	// EXPECT_EQ(false, cutil::contains(st1, 0));
	// EXPECT_EQ(true, cutil::contains(q1, 2));
	// EXPECT_EQ(false, cutil::contains(q1, 0));
	
}

TEST(Bit, simple)
{
	EXPECT_EQ(0b10000000, cutil::get_bit_by_mask((uint8_t)0b10101010, (uint8_t)0b10000000));
	EXPECT_EQ(0b00000000, cutil::get_bit_by_mask((uint8_t)0b10101010, (uint8_t)0b01000000));
	EXPECT_EQ(0b10000010, cutil::get_bit_by_mask((uint8_t)0b10101010, (uint8_t)0b11000011));
	EXPECT_EQ(0b00000000, cutil::get_bit_by_idx((uint8_t)0b10101010, 0));
	EXPECT_EQ(0b00000010, cutil::get_bit_by_idx((uint8_t)0b10101010, 1));
	EXPECT_EQ(0b00000000, cutil::get_bit_by_idx((uint8_t)0b10101010, 2));
	EXPECT_EQ(true, cutil::check_bit_by_mask((uint8_t)0b10101010, (uint8_t)0b10000000));
	EXPECT_EQ(false, cutil::check_bit_by_mask((uint8_t)0b10101010, (uint8_t)0b01000000));
	EXPECT_EQ(true, cutil::check_bit_by_mask((uint8_t)0b10101010, (uint8_t)0b11000011));
	EXPECT_EQ(false, cutil::check_bit_by_idx((uint8_t)0b10101010, 0));
	EXPECT_EQ(true, cutil::check_bit_by_idx((uint8_t)0b10101010, 1));
	EXPECT_EQ(false, cutil::check_bit_by_idx((uint8_t)0b10101010, 2));
	
	EXPECT_EQ(0b10000000, CUTIL_BIT_GET_MASK(0b10101010, 0b10000000));
	EXPECT_EQ(0b00000000, CUTIL_BIT_GET_MASK(0b10101010, 0b01000000));
	EXPECT_EQ(0b10000010, CUTIL_BIT_GET_MASK(0b10101010, 0b11000011));
	EXPECT_EQ(0b00000000, CUTIL_BIT_GET_IDX(0b10101010, 0));
	EXPECT_EQ(0b00000010, CUTIL_BIT_GET_IDX(0b10101010, 1));
	EXPECT_EQ(0b00000000, CUTIL_BIT_GET_IDX(0b10101010, 2));
	EXPECT_EQ(1, CUTIL_BIT_CHECK_MASK(0b10101010, 0b10000000));
	EXPECT_EQ(0, CUTIL_BIT_CHECK_MASK(0b10101010, 0b01000000));
	EXPECT_EQ(1, CUTIL_BIT_CHECK_MASK(0b10101010, 0b11000011));
	EXPECT_EQ(0, CUTIL_BIT_CHECK_IDX(0b10101010, 0));
	EXPECT_EQ(1, CUTIL_BIT_CHECK_IDX(0b10101010, 1));
	EXPECT_EQ(0, CUTIL_BIT_CHECK_IDX(0b10101010, 2));
	
	uint8_t byte = 0b10101010;
	EXPECT_EQ(0b10101010, cutil::set_bit_by_mask((uint8_t)0b10101010, (uint8_t)0b10000000));
	EXPECT_EQ(0b11101010, cutil::set_bit_by_mask((uint8_t)0b10101010, (uint8_t)0b11000000));
	EXPECT_EQ(0b11101011, cutil::set_bit_by_mask((uint8_t)0b10101010, (uint8_t)0b01000011));
	EXPECT_EQ(0b10101011, cutil::set_bit_by_idx((uint8_t)0b10101010, 0));
	EXPECT_EQ(0b10101010, cutil::set_bit_by_idx((uint8_t)0b10101010, 1));
	EXPECT_EQ(0b10101110, cutil::set_bit_by_idx((uint8_t)0b10101010, 2));
	EXPECT_EQ(0b10101010, cutil::set_bit_by_idx((uint8_t)0b10101010, 3));
	
	EXPECT_EQ(0b10101010, CUTIL_BIT_SET_MASK(0b10101010, 0b10000000));
	EXPECT_EQ(0b11101010, CUTIL_BIT_SET_MASK(0b10101010, 0b11000000));
	EXPECT_EQ(0b11101011, CUTIL_BIT_SET_MASK(0b10101010, 0b01000011));
	EXPECT_EQ(0b10101011, CUTIL_BIT_SET_IDX(0b10101010, 0));
	EXPECT_EQ(0b10101010, CUTIL_BIT_SET_IDX(0b10101010, 1));
	EXPECT_EQ(0b10101110, CUTIL_BIT_SET_IDX(0b10101010, 2));
	EXPECT_EQ(0b10101010, CUTIL_BIT_SET_IDX(0b10101010, 3));
	
	EXPECT_EQ(0b00101010, cutil::clear_bit_by_mask((uint8_t)0b10101010, (uint8_t)0b10000000));
	EXPECT_EQ(0b00101010, cutil::clear_bit_by_mask((uint8_t)0b10101010, (uint8_t)0b11000000));
	EXPECT_EQ(0b10101000, cutil::clear_bit_by_mask((uint8_t)0b10101010, (uint8_t)0b01000011));
	EXPECT_EQ(0b10101010, cutil::clear_bit_by_idx((uint8_t)0b10101010, 0));
	EXPECT_EQ(0b10101000, cutil::clear_bit_by_idx((uint8_t)0b10101010, 1));
	EXPECT_EQ(0b10101010, cutil::clear_bit_by_idx((uint8_t)0b10101010, 2));
	EXPECT_EQ(0b10100010, cutil::clear_bit_by_idx((uint8_t)0b10101010, 3));
	
	EXPECT_EQ(0b00101010, CUTIL_BIT_CLEAR_MASK(0b10101010, 0b10000000));
	EXPECT_EQ(0b00101010, CUTIL_BIT_CLEAR_MASK(0b10101010, 0b11000000));
	EXPECT_EQ(0b10101000, CUTIL_BIT_CLEAR_MASK(0b10101010, 0b01000011));
	EXPECT_EQ(0b10101010, CUTIL_BIT_CLEAR_IDX(0b10101010, 0));
	EXPECT_EQ(0b10101000, CUTIL_BIT_CLEAR_IDX(0b10101010, 1));
	EXPECT_EQ(0b10101010, CUTIL_BIT_CLEAR_IDX(0b10101010, 2));
	EXPECT_EQ(0b10100010, CUTIL_BIT_CLEAR_IDX(0b10101010, 3));
	
	EXPECT_EQ(0b00101010, cutil::flip_bit_by_mask((uint8_t)0b10101010, (uint8_t)0b10000000));
	EXPECT_EQ(0b01101010, cutil::flip_bit_by_mask((uint8_t)0b10101010, (uint8_t)0b11000000));
	EXPECT_EQ(0b11101001, cutil::flip_bit_by_mask((uint8_t)0b10101010, (uint8_t)0b01000011));
	EXPECT_EQ(0b10101011, cutil::flip_bit_by_idx((uint8_t)0b10101010, 0));
	EXPECT_EQ(0b10101000, cutil::flip_bit_by_idx((uint8_t)0b10101010, 1));
	EXPECT_EQ(0b10101110, cutil::flip_bit_by_idx((uint8_t)0b10101010, 2));
	EXPECT_EQ(0b10100010, cutil::flip_bit_by_idx((uint8_t)0b10101010, 3));
	
	EXPECT_EQ(0b00101010, CUTIL_BIT_FLIP_MASK(0b10101010, 0b10000000));
	EXPECT_EQ(0b01101010, CUTIL_BIT_FLIP_MASK(0b10101010, 0b11000000));
	EXPECT_EQ(0b11101001, CUTIL_BIT_FLIP_MASK(0b10101010, 0b01000011));
	EXPECT_EQ(0b10101011, CUTIL_BIT_FLIP_IDX(0b10101010, 0));
	EXPECT_EQ(0b10101000, CUTIL_BIT_FLIP_IDX(0b10101010, 1));
	EXPECT_EQ(0b10101110, CUTIL_BIT_FLIP_IDX(0b10101010, 2));
	EXPECT_EQ(0b10100010, CUTIL_BIT_FLIP_IDX(0b10101010, 3));
}

TEST(Bit, rotate)
{
	EXPECT_EQ(0b10101010, cutil::rotate_bit_left((uint8_t)0b10101010, 0));
	EXPECT_EQ(0b01010101, cutil::rotate_bit_left((uint8_t)0b10101010, 1));
	EXPECT_EQ(0b10101010, cutil::rotate_bit_left((uint8_t)0b10101010, 2));
	
	EXPECT_EQ(0b10101010, CUTIL_BIT_ROTATE_LEFT((uint8_t)0b10101010, 0));
	EXPECT_EQ(0b01010101, CUTIL_BIT_ROTATE_LEFT((uint8_t)0b10101010, 1));
	EXPECT_EQ(0b10101010, CUTIL_BIT_ROTATE_LEFT((uint8_t)0b10101010, 2));
	
	EXPECT_EQ(0b00100100, cutil::rotate_bit_left((uint8_t)0b00100100, 0));
	EXPECT_EQ(0b01001000, cutil::rotate_bit_left((uint8_t)0b00100100, 1));
	EXPECT_EQ(0b10010000, cutil::rotate_bit_left((uint8_t)0b00100100, 2));
	EXPECT_EQ(0b00100001, cutil::rotate_bit_left((uint8_t)0b00100100, 3));
	EXPECT_EQ(0b01000010, cutil::rotate_bit_left((uint8_t)0b00100100, 4));
	
	EXPECT_EQ(0b00100100, CUTIL_BIT_ROTATE_LEFT((uint8_t)0b00100100, 0));
	EXPECT_EQ(0b01001000, CUTIL_BIT_ROTATE_LEFT((uint8_t)0b00100100, 1));
	EXPECT_EQ(0b10010000, CUTIL_BIT_ROTATE_LEFT((uint8_t)0b00100100, 2));
	EXPECT_EQ(0b00100001, CUTIL_BIT_ROTATE_LEFT((uint8_t)0b00100100, 3));
	EXPECT_EQ(0b01000010, CUTIL_BIT_ROTATE_LEFT((uint8_t)0b00100100, 4));
	
	EXPECT_EQ(0b10101010, cutil::rotate_bit_right((uint8_t)0b10101010, 0));
	EXPECT_EQ(0b01010101, cutil::rotate_bit_right((uint8_t)0b10101010, 1));
	EXPECT_EQ(0b10101010, cutil::rotate_bit_right((uint8_t)0b10101010, 2));
	
	EXPECT_EQ(0b10101010, CUTIL_BIT_ROTATE_RIGHT((uint8_t)0b10101010, 0));
	EXPECT_EQ(0b01010101, CUTIL_BIT_ROTATE_RIGHT((uint8_t)0b10101010, 1));
	EXPECT_EQ(0b10101010, CUTIL_BIT_ROTATE_RIGHT((uint8_t)0b10101010, 2));
	
	EXPECT_EQ(0b00100100, cutil::rotate_bit_right((uint8_t)0b00100100, 0));
	EXPECT_EQ(0b00010010, cutil::rotate_bit_right((uint8_t)0b00100100, 1));
	EXPECT_EQ(0b00001001, cutil::rotate_bit_right((uint8_t)0b00100100, 2));
	EXPECT_EQ(0b10000100, cutil::rotate_bit_right((uint8_t)0b00100100, 3));
	EXPECT_EQ(0b01000010, cutil::rotate_bit_right((uint8_t)0b00100100, 4));
	
	EXPECT_EQ(0b00100100, CUTIL_BIT_ROTATE_RIGHT((uint8_t)0b00100100, 0));
	EXPECT_EQ(0b00010010, CUTIL_BIT_ROTATE_RIGHT((uint8_t)0b00100100, 1));
	EXPECT_EQ(0b00001001, CUTIL_BIT_ROTATE_RIGHT((uint8_t)0b00100100, 2));
	EXPECT_EQ(0b10000100, CUTIL_BIT_ROTATE_RIGHT((uint8_t)0b00100100, 3));
	EXPECT_EQ(0b01000010, CUTIL_BIT_ROTATE_RIGHT((uint8_t)0b00100100, 4));
	
	EXPECT_EQ(0b10010010, cutil::insert_bit_left((uint8_t)0b00100100, true));
	EXPECT_EQ(0b00010010, cutil::insert_bit_left((uint8_t)0b00100100, false));
	EXPECT_EQ(0b01001001, cutil::insert_bit_right((uint8_t)0b00100100, true));
	EXPECT_EQ(0b01001000, cutil::insert_bit_right((uint8_t)0b00100100, false));
	
	EXPECT_EQ(0b10010010, CUTIL_BIT_INSERT_LEFT((uint8_t)0b00100100, true));
	EXPECT_EQ(0b00010010, CUTIL_BIT_INSERT_LEFT((uint8_t)0b00100100, false));
	EXPECT_EQ(0b01001001, CUTIL_BIT_INSERT_RIGHT((uint8_t)0b00100100, true));
	EXPECT_EQ(0b01001000, CUTIL_BIT_INSERT_RIGHT((uint8_t)0b00100100, false));
	

}



TEST(Bit, Others)
{
	EXPECT_EQ(0b00000001, cutil::get_lsb((uint8_t)0b00100101));
	EXPECT_EQ(0b00000000, cutil::get_lsb((uint8_t)0b00100100));
	EXPECT_EQ(0b00000001, cutil::get_lsb((uint8_t)0b00000001));
	EXPECT_EQ(0b00000000, cutil::get_lsb((uint8_t)0b00000000));
	EXPECT_EQ(0b00000000, cutil::get_msb((uint8_t)0b00100101));
	EXPECT_EQ(0b10000000, cutil::get_msb((uint8_t)0b10100101));
	
	EXPECT_EQ(0b00000001, CUTIL_BIT_GET_LSB((uint8_t)0b00100101));
	EXPECT_EQ(0b00000000, CUTIL_BIT_GET_LSB((uint8_t)0b00100100));
	EXPECT_EQ(0b00000001, CUTIL_BIT_GET_LSB((uint8_t)0b00000001));
	EXPECT_EQ(0b00000000, CUTIL_BIT_GET_LSB((uint8_t)0b00000000));
	EXPECT_EQ(0b00000000, CUTIL_BIT_GET_MSB((uint8_t)0b00100101));
	EXPECT_EQ(0b10000000, CUTIL_BIT_GET_MSB((uint8_t)0b10100101));
	
	
	
	EXPECT_EQ(false, cutil::has_single_bit(0u));
	EXPECT_EQ(true, cutil::has_single_bit(1u));
	EXPECT_EQ(true, cutil::has_single_bit(2u));
	EXPECT_EQ(false, cutil::has_single_bit(3u));
	EXPECT_EQ(true, cutil::has_single_bit(4u));
	EXPECT_EQ(false, cutil::has_single_bit(6u));
	EXPECT_EQ(true, cutil::has_single_bit(8u));
	
	EXPECT_EQ(false, CUTIL_HAS_SINGLE_BIT(0u));
	EXPECT_EQ(true, CUTIL_HAS_SINGLE_BIT(1u));
	EXPECT_EQ(true, CUTIL_HAS_SINGLE_BIT(2u));
	EXPECT_EQ(false, CUTIL_HAS_SINGLE_BIT(3u));
	EXPECT_EQ(true, CUTIL_HAS_SINGLE_BIT(4u));
	EXPECT_EQ(false, CUTIL_HAS_SINGLE_BIT(6u));
	EXPECT_EQ(true, CUTIL_HAS_SINGLE_BIT(8u));
}

TEST(Math, range)
{
	EXPECT_EQ(100, CUTIL_MAX(100, 50));
	EXPECT_EQ(50, CUTIL_MIN(100, 50));
	EXPECT_EQ(100, CUTIL_MAX(50, 100));
	EXPECT_EQ(50, CUTIL_MIN(50, 100));
	
	EXPECT_EQ(100, CUTIL_ABS(100));
	EXPECT_EQ(100, CUTIL_ABS(-100));
	EXPECT_EQ(100, CUTIL_ABS(100.0));
	EXPECT_EQ(100, CUTIL_ABS(-100.0));
	
	EXPECT_EQ(15, cutil::clamp(15, 10, 20));
	EXPECT_EQ(17, cutil::clamp(15, 17, 20));
	EXPECT_EQ(13, cutil::clamp(15, 10, 13));
	EXPECT_EQ(15.0, cutil::clamp(15.0, 10.0, 20.0));
	EXPECT_EQ(17.0, cutil::clamp(15.0, 17.0, 20.0));
	EXPECT_EQ(13.0, cutil::clamp(15.0, 10.0, 13.0));
	EXPECT_EQ(15, CUTIL_CLAMP(15, 10, 20));
	EXPECT_EQ(17, CUTIL_CLAMP(15, 17, 20));
	EXPECT_EQ(13, CUTIL_CLAMP(15, 10, 13));
	EXPECT_EQ(15.0, CUTIL_CLAMP(15.0, 10.0, 20.0));
	EXPECT_EQ(17.0, CUTIL_CLAMP(15.0, 17.0, 20.0));
	EXPECT_EQ(13.0, CUTIL_CLAMP(15.0, 10.0, 13.0));
	
	{
		int a = 15;
		cutil::limit(a, 10, 20);
		EXPECT_EQ(15, a);
		a = 15;
		cutil::limit(a, 17, 20);
		EXPECT_EQ(17, a);
		a = 15;
		cutil::limit(a, 10, 13);
		EXPECT_EQ(13, a);
		a = 15;
		CUTIL_LIMIT(a, 10, 20);
		EXPECT_EQ(15, a);
		a = 15;
		CUTIL_LIMIT(a, 17, 20);
		EXPECT_EQ(17, a);
		a = 15;
		CUTIL_LIMIT(a, 10, 13);
		EXPECT_EQ(13, a);
	}
	
	EXPECT_EQ(true,  cutil::num_in_interval(15.0, 10.0, 20.0));
	EXPECT_EQ(false, cutil::num_in_interval(15.0, 17.0, 20.0));
	EXPECT_EQ(false, cutil::num_in_interval(15.0, 10.0, 13.0));
	EXPECT_EQ(true,  cutil::num_in_interval(10.0, 10.0, 20.0));
	EXPECT_EQ(true,  cutil::num_in_interval(20.0, 10.0, 20.0));
	EXPECT_EQ(true,  CUTIL_NUM_IN_INTERVAL(15.0, 10.0, 20.0));
	EXPECT_EQ(false, CUTIL_NUM_IN_INTERVAL(15.0, 17.0, 20.0));
	EXPECT_EQ(false, CUTIL_NUM_IN_INTERVAL(15.0, 10.0, 13.0));
	EXPECT_EQ(true,  CUTIL_NUM_IN_INTERVAL(10.0, 10.0, 20.0));
	EXPECT_EQ(true,  CUTIL_NUM_IN_INTERVAL(20.0, 10.0, 20.0));
	
	EXPECT_EQ(true,  cutil::num_in_open_interval(15.0, 10.0, 20.0));
	EXPECT_EQ(false, cutil::num_in_open_interval(15.0, 17.0, 20.0));
	EXPECT_EQ(false, cutil::num_in_open_interval(15.0, 10.0, 13.0));
	EXPECT_EQ(false, cutil::num_in_open_interval(10.0, 10.0, 20.0));
	EXPECT_EQ(false, cutil::num_in_open_interval(20.0, 10.0, 20.0));
	EXPECT_EQ(true,  CUTIL_NUM_IN_OPEN_INTERVAL(15.0, 10.0, 20.0));
	EXPECT_EQ(false, CUTIL_NUM_IN_OPEN_INTERVAL(15.0, 17.0, 20.0));
	EXPECT_EQ(false, CUTIL_NUM_IN_OPEN_INTERVAL(15.0, 10.0, 13.0));
	EXPECT_EQ(false, CUTIL_NUM_IN_OPEN_INTERVAL(10.0, 10.0, 20.0));
	EXPECT_EQ(false, CUTIL_NUM_IN_OPEN_INTERVAL(20.0, 10.0, 20.0));
	
#if CUTIL_CPP17_SUPPORTED
	double min = 10.0;
	double max = 20.0;
	EXPECT_EQ(true,  (cutil::num_in_interval<true, false>(10.0, 10.0, 20.0)));
	EXPECT_EQ(false, (cutil::num_in_interval<true, false>(20.0, 10.0, 20.0)));
	EXPECT_EQ(false, (cutil::num_in_interval<false, true>(10.0, min, max)));
	EXPECT_EQ(true,  (cutil::num_in_interval<false, true>(20.0, min, max)));
	EXPECT_EQ(false, (cutil::num_in_interval<false, false>(10.0, 10.0, 20.0)));
	EXPECT_EQ(false, (cutil::num_in_interval<false, false>(20.0, 10.0, 20.0)));
	EXPECT_EQ(true,  (cutil::num_in_interval<true, true>(10.0, 10.0, 20.0)));
	EXPECT_EQ(true,  (cutil::num_in_interval<true, true>(20.0, 10.0, 20.0)));
#endif
}


TEST(Math, increase)
{
	using numType_t = int16_t;
	std::vector<numType_t> aNums;
	aNums.reserve(10);
	auto test = [&](numType_t initial, size_t times, std::function<void(numType_t&)> f){
		numType_t num = initial;
		aNums.clear();
		for(size_t i = 0; i < times; i++){
			f(num);
			aNums.push_back(num);
		}
	};
	
	test(100, 10, [](numType_t& num){cutil::increase_under_limit(num, 105, 1);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{101, 102, 103, 104, 105, 105, 105, 105, 105, 105}));
	test(100, 10, [](numType_t& num){cutil::increase_under_limit(num, 105);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{101, 102, 103, 104, 105, 105, 105, 105, 105, 105}));
	test(100, 10, [](numType_t& num){cutil::increase_under_limit(num, 105, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{102, 104, 104, 104, 104, 104, 104, 104, 104, 104}));
	test(100, 10, [](numType_t& num){cutil::increase_under_limit_clamp(num, 105, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{102, 104, 105, 105, 105, 105, 105, 105, 105, 105}));
	test(100, 10, [](numType_t& num){cutil::increase_under_limit(num, 106, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{102, 104, 106, 106, 106, 106, 106, 106, 106, 106}));
	test(100, 10, [](numType_t& num){cutil::increase_under_limit_clamp(num, 106, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{102, 104, 106, 106, 106, 106, 106, 106, 106, 106}));
	
	test(100, 10, [](numType_t& num){CUTIL_INCREASE_UNDER_LIMIT(num, 105, 1);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{101, 102, 103, 104, 105, 105, 105, 105, 105, 105}));
	test(100, 10, [](numType_t& num){CUTIL_INCREASE_UNDER_LIMIT(num, 105, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{102, 104, 104, 104, 104, 104, 104, 104, 104, 104}));
	test(100, 10, [](numType_t& num){CUTIL_INCREASE_UNDER_LIMIT_CLAMP(num, 105, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{102, 104, 105, 105, 105, 105, 105, 105, 105, 105}));
	test(100, 10, [](numType_t& num){CUTIL_INCREASE_UNDER_LIMIT_CLAMP(num, 106, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{102, 104, 106, 106, 106, 106, 106, 106, 106, 106}));
	
	
	test(105, 10, [](numType_t& num){cutil::decrease_above_limit(num, 100, 1);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{104, 103, 102, 101, 100, 100, 100, 100, 100, 100}));
	test(105, 10, [](numType_t& num){cutil::decrease_above_limit(num, 100);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{104, 103, 102, 101, 100, 100, 100, 100, 100, 100}));
	test(105, 10, [](numType_t& num){cutil::decrease_above_limit(num, 100, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{103, 101, 101, 101, 101, 101, 101, 101, 101, 101}));
	test(105, 10, [](numType_t& num){cutil::decrease_above_limit_clamp(num, 100, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{103, 101, 100, 100, 100, 100, 100, 100, 100, 100}));
	test(105, 10, [](numType_t& num){cutil::decrease_above_limit(num, 99, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{103, 101, 99, 99, 99, 99, 99, 99, 99, 99}));
	test(105, 10, [](numType_t& num){cutil::decrease_above_limit_clamp(num, 99, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{103, 101, 99, 99, 99, 99, 99, 99, 99, 99}));
	
	test(105, 10, [](numType_t& num){CUTIL_DECREASE_ABOVE_LIMIT(num, 100, 1);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{104, 103, 102, 101, 100, 100, 100, 100, 100, 100}));
	test(105, 10, [](numType_t& num){CUTIL_DECREASE_ABOVE_LIMIT(num, 100, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{103, 101, 101, 101, 101, 101, 101, 101, 101, 101}));
	test(105, 10, [](numType_t& num){CUTIL_DECREASE_ABOVE_LIMIT_CLAMP(num, 100, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{103, 101, 100, 100, 100, 100, 100, 100, 100, 100}));
	test(105, 10, [](numType_t& num){CUTIL_DECREASE_ABOVE_LIMIT_CLAMP(num, 99, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{103, 101, 99, 99, 99, 99, 99, 99, 99, 99}));
	
	test(102, 10, [](numType_t& num){cutil::increase_rolling(num, 100, 105);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{103, 104, 105, 100, 101, 102, 103, 104, 105, 100}));
	test(102, 10, [](numType_t& num){cutil::increase_rolling(num, 100, 105, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{104, 100, 102, 104, 100, 102, 104, 100, 102, 104}));
	test(102, 10, [](numType_t& num){cutil::increase_rolling(num, 100, 106, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{104, 106, 100, 102, 104, 106, 100, 102, 104, 106}));
	test(102, 10, [](numType_t& num){cutil::decrease_rolling(num, 100, 105);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{101, 100, 105, 104, 103, 102, 101, 100, 105, 104}));
	test(102, 10, [](numType_t& num){cutil::decrease_rolling(num, 100, 105, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{100, 105, 103, 101, 105, 103, 101, 105, 103, 101}));
	test(102, 10, [](numType_t& num){cutil::decrease_rolling(num, 100, 106, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{100, 106, 104, 102, 100, 106, 104, 102, 100, 106}));
	
	test(102, 10, [](numType_t& num){CUTIL_INCREASE_ROLLING(num, 100, 105, 1);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{103, 104, 105, 100, 101, 102, 103, 104, 105, 100}));
	test(102, 10, [](numType_t& num){CUTIL_INCREASE_ROLLING(num, 100, 105, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{104, 100, 102, 104, 100, 102, 104, 100, 102, 104}));
	test(102, 10, [](numType_t& num){CUTIL_INCREASE_ROLLING(num, 100, 106, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{104, 106, 100, 102, 104, 106, 100, 102, 104, 106}));
	test(102, 10, [](numType_t& num){CUTIL_DECREASE_ROLLING(num, 100, 105, 1);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{101, 100, 105, 104, 103, 102, 101, 100, 105, 104}));
	test(102, 10, [](numType_t& num){CUTIL_DECREASE_ROLLING(num, 100, 105, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{100, 105, 103, 101, 105, 103, 101, 105, 103, 101}));
	test(102, 10, [](numType_t& num){CUTIL_DECREASE_ROLLING(num, 100, 106, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{100, 106, 104, 102, 100, 106, 104, 102, 100, 106}));
	
	
	test(32763, 6, [](numType_t& num){cutil::increase_no_overflow(num, 1);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{32764, 32765, 32766, 32767, 32767, 32767}));
	test(32762, 6, [](numType_t& num){cutil::increase_no_overflow(num, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{32764, 32766, 32766, 32766, 32766, 32766}));
	test(32761, 6, [](numType_t& num){cutil::increase_no_overflow(num, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{32763, 32765, 32767, 32767, 32767, 32767}));
	
	test(32763, 6, [](numType_t& num){CUTIL_INCREASE_NO_OVERFLOW(num, 1);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{32764, 32765, 32766, 32767, 32767, 32767}));
	test(32762, 6, [](numType_t& num){CUTIL_INCREASE_NO_OVERFLOW(num, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{32764, 32766, 32766, 32766, 32766, 32766}));
	test(32761, 6, [](numType_t& num){CUTIL_INCREASE_NO_OVERFLOW(num, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{32763, 32765, 32767, 32767, 32767, 32767}));
	
	
	test(-32763, 6, [](numType_t& num){cutil::decrease_no_underflow(num, 1);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{-32764, -32765, -32766, -32767, -32768, -32768}));
	test(-32762, 6, [](numType_t& num){cutil::decrease_no_underflow(num, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{-32764, -32766, -32768, -32768, -32768, -32768}));
	test(-32761, 6, [](numType_t& num){cutil::decrease_no_underflow(num, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{-32763, -32765, -32767, -32767, -32767, -32767}));
	
	test(-32763, 6, [](numType_t& num){CUTIL_DECREASE_NO_UNDERFLOW(num, 1);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{-32764, -32765, -32766, -32767, -32768, -32768}));
	test(-32762, 6, [](numType_t& num){CUTIL_DECREASE_NO_UNDERFLOW(num, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{-32764, -32766, -32768, -32768, -32768, -32768}));
	test(-32761, 6, [](numType_t& num){CUTIL_DECREASE_NO_UNDERFLOW(num, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{-32763, -32765, -32767, -32767, -32767, -32767}));
	
	
}

TEST(Math, others)
{
	EXPECT_EQ(true,  cutil::fequal(0.00001, 0.00002, 0.0001));
	EXPECT_EQ(false, cutil::fequal(0.00001, 0.00002, 0.0000001));
	EXPECT_EQ(true,  cutil::fequal(0.0000000000001f, 0.0000000000002f));
	EXPECT_EQ(false, cutil::fequal(0.0000000000001, 0.0000000000002));
	
	EXPECT_EQ(true, CUTIL_EQUAL(0.00001, 0.00002, 0.0001));
	EXPECT_EQ(false, CUTIL_EQUAL(0.00001, 0.00002, 0.0000001));
	EXPECT_EQ(true, CUTIL_EQUAL_F(0.0000000000001, 0.0000000000002));
	EXPECT_EQ(false, CUTIL_EQUAL_D(0.0000000000001, 0.0000000000002));
	
	EXPECT_EQ(true, (cutil::fequal(cutil::numbers::pi_3, cutil::math::deg2rad(60.0))));
	EXPECT_EQ(false, (cutil::numbers::pi_3 == cutil::math::deg2rad(60.0)));

	EXPECT_EQ(true, (cutil::fequal(60.0, cutil::math::rad2deg(cutil::numbers::pi_3), 1e-14)));
	EXPECT_EQ(false, (60.0 == cutil::math::rad2deg(cutil::numbers::pi_3)));
	
	EXPECT_EQ(true, (CUTIL_EQUAL(CUTIL_PI_3, CUTIL_DEG_TO_RAD(60.0), 1e-14)));
	EXPECT_EQ(false, (CUTIL_PI_3 == CUTIL_DEG_TO_RAD(60.0)));

	EXPECT_EQ(true, (CUTIL_EQUAL(60.0, CUTIL_RAD_TO_DEG(CUTIL_PI_3), 1e-14)));
	EXPECT_EQ(false, (60.0 == CUTIL_RAD_TO_DEG(CUTIL_PI_3)));
	
	EXPECT_EQ(true, (cutil::fequal(15.0, cutil::math::lerp(10, 20, 0.5), 1e-14)) );
	EXPECT_EQ(true, (cutil::fequal(17.5, cutil::math::lerp(10, 20, 0.75), 1e-14)) );
	EXPECT_EQ(true, (cutil::fequal(12.5, cutil::math::lerp(10, 20, 0.25), 1e-14)) );
	EXPECT_EQ(true, (cutil::fequal(10.0, cutil::math::lerp(10, 20, 0.0), 1e-14)) );
	EXPECT_EQ(true, (cutil::fequal(20.0, cutil::math::lerp(10, 20, 1.0), 1e-14)) );
	EXPECT_EQ(true, (cutil::fequal(20.0, cutil::math::lerp(10, 20, 1.0), 1e-14)) );
	EXPECT_EQ(true, (cutil::fequal(5.0, cutil::math::lerp(10, 20, -0.5), 1e-14)) );
	EXPECT_EQ(true, (cutil::fequal(25.0, cutil::math::lerp(10, 20, 1.5), 1e-14)) );
	EXPECT_EQ(true, (cutil::fequal(10.0, cutil::math::lerp(10, 10, 0.5), 1e-14)) );
	
	EXPECT_EQ(true, (CUTIL_EQUAL(15.0, CUTIL_LERP(10, 20 ,0.5), 1e-14)));
	EXPECT_EQ(true, (CUTIL_EQUAL(17.5, CUTIL_LERP(10, 20 ,0.75), 1e-14)));
	EXPECT_EQ(true, (CUTIL_EQUAL(12.5, CUTIL_LERP(10, 20 ,0.25), 1e-14)));
	EXPECT_EQ(true, (CUTIL_EQUAL(10.0, CUTIL_LERP(10, 20 ,0.0), 1e-14)));
	EXPECT_EQ(true, (CUTIL_EQUAL(20.0, CUTIL_LERP(10, 20 ,1.0), 1e-14)));
	EXPECT_EQ(true, (CUTIL_EQUAL(20.0, CUTIL_LERP(10, 20 ,1.0), 1e-14)));
	EXPECT_EQ(true, (CUTIL_EQUAL(5.0, CUTIL_LERP(10, 20 ,-0.5), 1e-14)));
	EXPECT_EQ(true, (CUTIL_EQUAL(25.0, CUTIL_LERP(10, 20 ,1.5), 1e-14)));
	EXPECT_EQ(true, (CUTIL_EQUAL(10.0, CUTIL_LERP(10, 10 ,0.5), 1e-14)));
	
#ifdef CUTIL_CPP20_SUPPORTED
	EXPECT_EQ(true, (cutil::fequal(15.0, std::lerp(10, 20, 0.5), 1e-14)) );
	EXPECT_EQ(true, (cutil::fequal(17.5, std::lerp(10, 20, 0.75), 1e-14)) );
	EXPECT_EQ(true, (cutil::fequal(12.5, std::lerp(10, 20, 0.25), 1e-14)) );
	EXPECT_EQ(true, (cutil::fequal(10.0, std::lerp(10, 20, 0.0), 1e-14)) );
	EXPECT_EQ(true, (cutil::fequal(20.0, std::lerp(10, 20, 1.0), 1e-14)) );
	EXPECT_EQ(true, (cutil::fequal(20.0, std::lerp(10, 20, 1.0), 1e-14)) );
	EXPECT_EQ(true, (cutil::fequal(5.0, std::lerp(10, 20, -0.5), 1e-14)) );
	EXPECT_EQ(true, (cutil::fequal(25.0, std::lerp(10, 20, 1.5), 1e-14)) );
	EXPECT_EQ(true, (cutil::fequal(10.0, std::lerp(10, 10, 0.5), 1e-14)) );
#endif


	EXPECT_EQ(2, (cutil::math::gcd(6, 10)) );
	EXPECT_EQ(2, (cutil::math::gcd(10, 6)) );
	EXPECT_EQ(2, (cutil::math::gcd(6, -10)) );
	EXPECT_EQ(2, (cutil::math::gcd(-6, -10)) );
	EXPECT_EQ(2, (cutil::math::gcd(-6, 10)) );
	EXPECT_EQ(24, (cutil::math::gcd(0, 24)) );
	EXPECT_EQ(24, (cutil::math::gcd(0, -24)) );
	EXPECT_EQ(2, (cutil::math::gcd(6u, 10u)) );
	
	// static_assert(cutil::math::lcm(6, 10) == 30);
	EXPECT_EQ(cutil::math::lcm(6, 10), 30);
	EXPECT_EQ(cutil::math::lcm(10, 6), 30);
	EXPECT_EQ(cutil::math::lcm(6, -10), 30);
	EXPECT_EQ(cutil::math::lcm(-6, -10), 30);
	EXPECT_EQ(cutil::math::lcm(-6, 10), 30);
	
	
	EXPECT_EQ(cutil::math::midpoint(6.0, 9.0), 7.5);
	EXPECT_EQ(cutil::math::midpoint(6, 9), 7);
	EXPECT_EQ(CUTIL_MIDPOINT(6, 9), 7);

	// constexpr auto zzzz = cutil::pow_int<30>(2lu);
	EXPECT_EQ(cutil::math::pow_int(2, 0), 1);
	EXPECT_EQ(cutil::math::pow_int(2, 1), 2);
	EXPECT_EQ(cutil::math::pow_int(2, 2), 4);
	EXPECT_EQ(cutil::math::pow_int(2, 3), 8);
	EXPECT_EQ(cutil::math::pow_int(2, 4), 16);
	EXPECT_EQ(cutil::math::pow_int(3, 1), 3);
	EXPECT_EQ(cutil::math::pow_int(3, 2), 9);
	EXPECT_EQ(cutil::math::pow_int(3, 3), 27);
	EXPECT_EQ(cutil::math::pow_int<1>(3), 3);
	EXPECT_EQ(cutil::math::pow_int<2>(3), 9);
	EXPECT_EQ(cutil::math::pow_int<3>(3), 27);
	
	uint64_t z = 2;
	EXPECT_EQ(cutil::math::pow_int(z++, 2), 4);
	EXPECT_EQ(cutil::math::pow_int(z++, 2), 9);
	EXPECT_EQ(cutil::math::pow_int(z++, 2), 16);
	z = 2;
	EXPECT_EQ(cutil::math::pow_int<2>(z++), 4);
	EXPECT_EQ(cutil::math::pow_int<2>(z++), 9);
	EXPECT_EQ(cutil::math::pow_int<2>(z++), 16);
	
	EXPECT_EQ(cutil::math::factorial(1), 1);
	EXPECT_EQ(cutil::math::factorial(2), 2);
	EXPECT_EQ(cutil::math::factorial(3), 6);
	EXPECT_EQ(cutil::math::factorial(4), 24);
	EXPECT_EQ(cutil::math::factorial(5), 120);
	EXPECT_EQ(cutil::math::factorial<1>(), 1);
	EXPECT_EQ(cutil::math::factorial<2>(), 2);
	EXPECT_EQ(cutil::math::factorial<3>(), 6);
	EXPECT_EQ(cutil::math::factorial<4>(), 24);
	EXPECT_EQ(cutil::math::factorial<5>(), 120);
	
}

TEST(Memory, Basic)
{
	uint16_t num = 0x1234;
	EXPECT_EQ(0x34, cutil::get_word_low(num));
	EXPECT_EQ(0x12, cutil::get_word_high(num));
	
	EXPECT_EQ(0x1234, cutil::read_memory<uint16_t>(&num));
	cutil::write_memory(&num, (uint16_t)0x5678);
	EXPECT_EQ(0x5678, num);
	
}
TEST(Memory, Bitwise)
{
	uint32_t i = 0x12345678;
	std::array<float, 15> f;
	std::fill(f.begin(), f.end(), 0.0f);
	cutil::bitwise_memcpy(f[0], i);
	cutil::bitwise_memcpy(f[1], 0x12345678);
	CUTIL_BITWISE_MEMCPY(&f[2], &i);
	CUTIL_BITWISE_ASSIGN(f[3], i);
	f[4] = CUTIL_BITWISE_CAST(float, i);
	f[5] = cutil::bit_cast<float>(i);
	f[6] = cutil::bit_cast<float>(0x12345678);
	
#ifdef CUTIL_CPP20_SUPPORTED
	f[13] = std::bit_cast<float>(i);
	f[14] = std::bit_cast<float>(0x12345678);
#endif
	EXPECT_EQ(f[0], f[1]);
	EXPECT_EQ(f[0], f[2]);
	EXPECT_EQ(f[0], f[3]);
	EXPECT_EQ(f[0], f[4]);
	EXPECT_EQ(f[0], f[5]);
	EXPECT_EQ(f[0], f[6]);
	
#ifdef CUTIL_CPP20_SUPPORTED
	EXPECT_EQ(f[0], f[13]);
	EXPECT_EQ(f[0], f[14]);
#endif
}



TEST(Memory, Field)
{
	struct MyStruct {
		uint8_t 	a;	// 0    (+0)
		uint8_t 	b;	// 1      |--(+1)
		uint32_t 	c;	// 4    (+4)
		uint8_t 	d;	// 8    (+4)
		uint8_t 	e;	// 9      |--(+1)
		uint8_t 	f;	// 10     |--(+1)
		uint64_t 	g;	// 16   (+8)
		uint32_t 	h;	// 24   (+8)
	};
	int a;
	int b;
	int* c;
	int* d;
	auto zzz = &a - &b;
	
	EXPECT_EQ(0, CUTIL_STRUCT_FIELD_OFFSET(MyStruct, a));
	EXPECT_EQ(1, CUTIL_STRUCT_FIELD_OFFSET(MyStruct, b));
	EXPECT_EQ(4, CUTIL_STRUCT_FIELD_OFFSET(MyStruct, c));
	EXPECT_EQ(8, CUTIL_STRUCT_FIELD_OFFSET(MyStruct, d));
	EXPECT_EQ(9, CUTIL_STRUCT_FIELD_OFFSET(MyStruct, e));
	EXPECT_EQ(10, CUTIL_STRUCT_FIELD_OFFSET(MyStruct, f));
	EXPECT_EQ(16, CUTIL_STRUCT_FIELD_OFFSET(MyStruct, g));
	EXPECT_EQ(24, CUTIL_STRUCT_FIELD_OFFSET(MyStruct, h));
	
	EXPECT_EQ(0, cutil::get_member_offset(&MyStruct::a));
	EXPECT_EQ(1, cutil::get_member_offset(&MyStruct::b));
	EXPECT_EQ(4, cutil::get_member_offset(&MyStruct::c));
	EXPECT_EQ(8, cutil::get_member_offset(&MyStruct::d));
	EXPECT_EQ(9, cutil::get_member_offset(&MyStruct::e));
	EXPECT_EQ(10, cutil::get_member_offset(&MyStruct::f));
	EXPECT_EQ(16, cutil::get_member_offset(&MyStruct::g));
	EXPECT_EQ(24, cutil::get_member_offset(&MyStruct::h));
	
	EXPECT_EQ(1, CUTIL_STRUCT_FIELD_SIZE(MyStruct, a));
	EXPECT_EQ(1, CUTIL_STRUCT_FIELD_SIZE(MyStruct, b));
	EXPECT_EQ(4, CUTIL_STRUCT_FIELD_SIZE(MyStruct, c));
	EXPECT_EQ(1, CUTIL_STRUCT_FIELD_SIZE(MyStruct, d));
	EXPECT_EQ(1, CUTIL_STRUCT_FIELD_SIZE(MyStruct, e));
	EXPECT_EQ(1, CUTIL_STRUCT_FIELD_SIZE(MyStruct, f));
	EXPECT_EQ(8, CUTIL_STRUCT_FIELD_SIZE(MyStruct, g));
	EXPECT_EQ(4, CUTIL_STRUCT_FIELD_SIZE(MyStruct, h));
	
	
	
	MyStruct s;
	EXPECT_EQ(8, CUTIL_PTR_OFFSET(&s.h, &s.g));
	EXPECT_EQ(8, cutil::get_ptr_offset(&s.h, &s.g));
	EXPECT_EQ(&s, CUTIL_STRUCT_FIELD_CONTAINER(MyStruct, b, &s.b));
	
}
