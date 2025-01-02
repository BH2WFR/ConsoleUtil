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


int main(int argc, char* argv[])
{
	CUTIL_CHCP_ENCODING_UTF8();
	CUTIL_CONSOLE_TITLE("ConsoleUtil Test");
	CUTIL_CONSOLE_SIZE(100, 30);
	CUTIL_CONSOLE_CLEAR();
	
	CUTIL_PRINT_ARGV(argc, argv);
	
	printf(FLGreen "Hello World!\n" CReset);
	std::cout << FLRed "ERROR\n" CReset;
	
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

TEST(BoolStatement, equal_any)
{
	EXPECT_EQ(true, cutil::equal_any(1, 1));
	EXPECT_EQ(false, cutil::equal_any(1, 2));
	EXPECT_EQ(true, cutil::equal_any(1, 1, 2));
	EXPECT_EQ(false, cutil::equal_any(1, 2, 3));
	EXPECT_EQ(true, cutil::equal_any(1, 2, 1));
	EXPECT_EQ(true, cutil::equal_any(1, 1, 1));
	EXPECT_EQ(true, cutil::equal_any(1, 1, 2, 3));
	EXPECT_EQ(true, cutil::equal_any(1, 2, 3, 1));
	EXPECT_EQ(false, cutil::equal_any(1, 2, 3, 4));
}
TEST(BoolStatement, equal_all)
{
	EXPECT_EQ(true, cutil::equal_all(1, 1));
	EXPECT_EQ(false, cutil::equal_all(1, 2));
	EXPECT_EQ(false, cutil::equal_all(1, 1, 2));
	EXPECT_EQ(false, cutil::equal_all(1, 2, 3));
	EXPECT_EQ(false, cutil::equal_all(1, 2, 1));
	EXPECT_EQ(true, cutil::equal_all(1, 1, 1));
	EXPECT_EQ(false, cutil::equal_all(1, 1, 2, 3));
	EXPECT_EQ(false, cutil::equal_all(1, 2, 3, 1));
	EXPECT_EQ(false, cutil::equal_all(1, 2, 3, 4));
}
TEST(BoolStatement, unequal_any)
{
	EXPECT_EQ(false, cutil::unequal_any(1, 1));
	EXPECT_EQ(true, cutil::unequal_any(1, 2));
	EXPECT_EQ(true, cutil::unequal_any(1, 1, 2));
	EXPECT_EQ(true, cutil::unequal_any(1, 2, 3));
	EXPECT_EQ(true, cutil::unequal_any(1, 2, 1));
	EXPECT_EQ(false, cutil::unequal_any(1, 1, 1));
	EXPECT_EQ(true, cutil::unequal_any(1, 1, 2, 3));
	EXPECT_EQ(true, cutil::unequal_any(1, 2, 3, 1));
	EXPECT_EQ(true, cutil::unequal_any(1, 2, 3, 4));
}
TEST(BoolStatement, unequal_all)
{
	EXPECT_EQ(false, cutil::unequal_all(1, 1));
	EXPECT_EQ(true, cutil::unequal_all(1, 2));
	EXPECT_EQ(false, cutil::unequal_all(1, 1, 2));
	EXPECT_EQ(true, cutil::unequal_all(1, 2, 3));
	EXPECT_EQ(false, cutil::unequal_all(1, 2, 1));
	EXPECT_EQ(false, cutil::unequal_all(1, 1, 1));
	EXPECT_EQ(false, cutil::unequal_all(1, 1, 2, 3));
	EXPECT_EQ(false, cutil::unequal_all(1, 2, 3, 1));
	EXPECT_EQ(true, cutil::unequal_all(1, 2, 3, 4));
	EXPECT_EQ(true, cutil::unequal_all(1, 2, 2, 2));
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
	// EXPECT_EQ(true, cutil::contains(st1, 2));
	// EXPECT_EQ(false, cutil::contains(st1, 0));
	// EXPECT_EQ(true, cutil::contains(q1, 2));
	// EXPECT_EQ(false, cutil::contains(q1, 0));
	
}

TEST(Bit, simple)
{
	EXPECT_EQ(0b10000000, cutil::get_bit_by_mask(0b10101010, 0b10000000));
	EXPECT_EQ(0b00000000, cutil::get_bit_by_mask(0b10101010, 0b01000000));
	EXPECT_EQ(0b10000010, cutil::get_bit_by_mask(0b10101010, 0b11000011));
	EXPECT_EQ(0b00000000, cutil::get_bit_by_idx(0b10101010, 0));
	EXPECT_EQ(0b00000010, cutil::get_bit_by_idx(0b10101010, 1));
	EXPECT_EQ(0b00000000, cutil::get_bit_by_idx(0b10101010, 2));
	EXPECT_EQ(true, cutil::check_bit_by_mask(0b10101010, 0b10000000));
	EXPECT_EQ(false, cutil::check_bit_by_mask(0b10101010, 0b01000000));
	EXPECT_EQ(true, cutil::check_bit_by_mask(0b10101010, 0b11000011));
	EXPECT_EQ(false, cutil::check_bit_by_idx(0b10101010, 0));
	EXPECT_EQ(true, cutil::check_bit_by_idx(0b10101010, 1));
	EXPECT_EQ(false, cutil::check_bit_by_idx(0b10101010, 2));
	
	uint8_t byte = 0b10101010;
	EXPECT_EQ(0b10101010, cutil::set_bit_by_mask(0b10101010, 0b10000000));
	EXPECT_EQ(0b11101010, cutil::set_bit_by_mask(0b10101010, 0b11000000));
	EXPECT_EQ(0b11101011, cutil::set_bit_by_mask(0b10101010, 0b01000011));
	EXPECT_EQ(0b10101011, cutil::set_bit_by_idx(0b10101010, 0));
	EXPECT_EQ(0b10101010, cutil::set_bit_by_idx(0b10101010, 1));
	EXPECT_EQ(0b10101110, cutil::set_bit_by_idx(0b10101010, 2));
	EXPECT_EQ(0b10101010, cutil::set_bit_by_idx(0b10101010, 3));
	
	EXPECT_EQ(0b00101010, cutil::clear_bit_by_mask(0b10101010, 0b10000000));
	EXPECT_EQ(0b00101010, cutil::clear_bit_by_mask(0b10101010, 0b11000000));
	EXPECT_EQ(0b10101000, cutil::clear_bit_by_mask(0b10101010, 0b01000011));
	EXPECT_EQ(0b10101010, cutil::clear_bit_by_idx(0b10101010, 0));
	EXPECT_EQ(0b10101000, cutil::clear_bit_by_idx(0b10101010, 1));
	EXPECT_EQ(0b10101010, cutil::clear_bit_by_idx(0b10101010, 2));
	EXPECT_EQ(0b10100010, cutil::clear_bit_by_idx(0b10101010, 3));
	
	EXPECT_EQ(0b00101010, cutil::flip_bit_by_mask(0b10101010, 0b10000000));
	EXPECT_EQ(0b01101010, cutil::flip_bit_by_mask(0b10101010, 0b11000000));
	EXPECT_EQ(0b11101001, cutil::flip_bit_by_mask(0b10101010, 0b01000011));
	EXPECT_EQ(0b10101011, cutil::flip_bit_by_idx(0b10101010, 0));
	EXPECT_EQ(0b10101000, cutil::flip_bit_by_idx(0b10101010, 1));
	EXPECT_EQ(0b10101110, cutil::flip_bit_by_idx(0b10101010, 2));
	EXPECT_EQ(0b10100010, cutil::flip_bit_by_idx(0b10101010, 3));
	
}

TEST(Bit, rotate)
{
	EXPECT_EQ(0b10101010, cutil::rotate_bit_left((uint8_t)0b10101010, 0));
	EXPECT_EQ(0b01010101, cutil::rotate_bit_left((uint8_t)0b10101010, 1));
	EXPECT_EQ(0b10101010, cutil::rotate_bit_left((uint8_t)0b10101010, 2));
	
	EXPECT_EQ(0b00100100, cutil::rotate_bit_left((uint8_t)0b00100100, 0));
	EXPECT_EQ(0b01001000, cutil::rotate_bit_left((uint8_t)0b00100100, 1));
	EXPECT_EQ(0b10010000, cutil::rotate_bit_left((uint8_t)0b00100100, 2));
	EXPECT_EQ(0b00100001, cutil::rotate_bit_left((uint8_t)0b00100100, 3));
	EXPECT_EQ(0b01000010, cutil::rotate_bit_left((uint8_t)0b00100100, 4));
	
	EXPECT_EQ(0b10101010, cutil::rotate_bit_right((uint8_t)0b10101010, 0));
	EXPECT_EQ(0b01010101, cutil::rotate_bit_right((uint8_t)0b10101010, 1));
	EXPECT_EQ(0b10101010, cutil::rotate_bit_right((uint8_t)0b10101010, 2));
	
	EXPECT_EQ(0b00100100, cutil::rotate_bit_right((uint8_t)0b00100100, 0));
	EXPECT_EQ(0b00010010, cutil::rotate_bit_right((uint8_t)0b00100100, 1));
	EXPECT_EQ(0b00001001, cutil::rotate_bit_right((uint8_t)0b00100100, 2));
	EXPECT_EQ(0b10000100, cutil::rotate_bit_right((uint8_t)0b00100100, 3));
	EXPECT_EQ(0b01000010, cutil::rotate_bit_right((uint8_t)0b00100100, 4));
	
}

TEST(Bit, memcpy)
{
	uint32_t i = 0x12345678;
	float f1 = 0.0f;
	float f2 = 0.0f;
	cutil::bitwise_memcpy(f1, i);
	// f2 = CUTIL_BITWISE_MEMCPY(float, f1, i);
	std::cout << f1 << " " << f2 << std::endl;
	// EXPECT_EQ(f1, f2);
}

TEST(Math, range)
{
	EXPECT_EQ(15, cutil::clamp(15, 10, 20));
	EXPECT_EQ(17, cutil::clamp(15, 17, 20));
	EXPECT_EQ(13, cutil::clamp(15, 10, 13));
	EXPECT_EQ(15.0, cutil::clamp(15.0, 10.0, 20.0));
	EXPECT_EQ(17.0, cutil::clamp(15.0, 17.0, 20.0));
	EXPECT_EQ(13.0, cutil::clamp(15.0, 10.0, 13.0));
	
	EXPECT_EQ(true,  cutil::num_in_range(15.0, 10.0, 20.0));
	EXPECT_EQ(false, cutil::num_in_range(15.0, 17.0, 20.0));
	EXPECT_EQ(false, cutil::num_in_range(15.0, 10.0, 13.0));
	EXPECT_EQ(true,  cutil::num_in_range(10.0, 10.0, 20.0));
	EXPECT_EQ(true,  cutil::num_in_range(20.0, 10.0, 20.0));
	
	EXPECT_EQ(true,  cutil::num_in_open_range(15.0, 10.0, 20.0));
	EXPECT_EQ(false, cutil::num_in_open_range(15.0, 17.0, 20.0));
	EXPECT_EQ(false, cutil::num_in_open_range(15.0, 10.0, 13.0));
	EXPECT_EQ(false, cutil::num_in_open_range(10.0, 10.0, 20.0));
	EXPECT_EQ(false, cutil::num_in_open_range(20.0, 10.0, 20.0));
	
#if CUTIL_CPP17_SUPPORTED
	EXPECT_EQ(true,  (cutil::num_in_range<true, false>(10.0, 10.0, 20.0)));
	EXPECT_EQ(false, (cutil::num_in_range<true, false>(20.0, 10.0, 20.0)));
	EXPECT_EQ(false, (cutil::num_in_range<false, true>(10.0, 10.0, 20.0)));
	EXPECT_EQ(true,  (cutil::num_in_range<false, true>(20.0, 10.0, 20.0)));
	EXPECT_EQ(false, (cutil::num_in_range<false, false>(10.0, 10.0, 20.0)));
	EXPECT_EQ(false, (cutil::num_in_range<false, false>(20.0, 10.0, 20.0)));
	EXPECT_EQ(true,  (cutil::num_in_range<true, true>(10.0, 10.0, 20.0)));
	EXPECT_EQ(true,  (cutil::num_in_range<true, true>(20.0, 10.0, 20.0)));
#endif
}

TEST(Math, increase)
{
	int16_t i6 = 250;
	cutil::increase_under_limit(i6, 255, 1);
	EXPECT_EQ(251, i6);
	cutil::increase_under_limit(i6, 255, 1);
	EXPECT_EQ(252, i6);
	cutil::increase_under_limit(i6, 255, 2);
	EXPECT_EQ(254, i6);
	cutil::increase_under_limit(i6, 255);
	EXPECT_EQ(255, i6);
	cutil::increase_under_limit(i6, 255, 1);
	EXPECT_EQ(255, i6);
	cutil::increase_under_limit(i6, 255);
	EXPECT_EQ(255, i6);
	cutil::increase_under_limit(i6, 255, 100);
	EXPECT_EQ(255, i6);
	cutil::increase_under_limit(i6, 255, 99999999);
	EXPECT_EQ(255, i6);
	i6 = 250;
	cutil::increase_under_limit(i6, 255, 6);
	EXPECT_EQ(250, i6);
	
	i6 = 255;
	cutil::decrease_above_limit(i6, 250, 2);
	EXPECT_EQ(253, i6);
	cutil::decrease_above_limit(i6, 250);
	EXPECT_EQ(252, i6);
	cutil::decrease_above_limit(i6, 2505);
	EXPECT_EQ(252, i6);
}
