/* UTF-8 encoding
* Project URL: https://github.com/BH2WFR/ConsoleUtil
  Author:		BH2WFR
  Updated:		2 JAN 2025
  License:		MIT License
* You can include this header in header files.
*/
#ifndef CONSOLEUTIL_CPP_UTIL_H__
#define CONSOLEUTIL_CPP_UTIL_H__
#include <ConsoleUtil/Base.h>


#if defined(__cplusplus) && defined(CUTIL_CPP11_SUPPORTED)
#include <type_traits>
#include <algorithm>
#include <iterator>
#include <cassert>
#include <cmath>
#include <numeric>
#ifdef CUTIL_CPP20_SUPPORTED
	#include <bit>
#endif


_CUTIL_NAMESPACE_BEGIN


//* -----------  concepts
namespace internal {
	// concept in C++20 will make it easier
	
	template <typename T>
	struct is_uint : std::integral_constant<bool, std::is_integral<T>::value && std::is_unsigned<T>::value> {};
	
	template <typename T>
	struct is_int_or_float : std::integral_constant<bool, std::is_signed<T>::value || std::is_floating_point<T>::value> {};
	
	template <typename From, typename To = From>
	struct is_arithmetic_and_convertible : std::integral_constant<bool
				, std::is_arithmetic<From>::value && std::is_arithmetic<To>::value && std::is_convertible<From, To>::value
			>{};
	
	template <typename From, typename To = From>
	struct is_integral_and_convertible : std::integral_constant<bool
				, std::is_integral<From>::value && std::is_integral<To>::value && std::is_convertible<From, To>::value
			>{};
	
	template <typename T>
	struct has_iterators : std::integral_constant<bool
				, std::is_same<decltype(std::declval<T>().begin()), decltype(std::declval<T>().end())>::value
			>{};
	
	template <typename T, typename U>
	struct has_same_size : std::integral_constant<bool, sizeof(T) == sizeof(U)>{};
	
}

#define _CUTIL_CONCEPT_UNSIGNED(T) 			\
			typename std::enable_if<cutil::internal::is_uint<T>::value, bool>::type = false
#define _CUTIL_CONCEPT_INTEGRAL(T) 			\
			typename std::enable_if<std::is_integral<T>::value, bool>::type = false
#define _CUTIL_CONCEPT_FLOAT(T) 			\
			typename std::enable_if<std::is_floating_point<T>::value, bool>::type = false
#define _CUTIL_CONCEPT_SIGNED_OR_FLOAT(T) 	\
			typename std::enable_if<cutil::internal::is_int_or_float<T>::value, bool>::type = false
#define _CUTIL_CONCEPT_ARITHMETIC(T)		\
			typename std::enable_if<std::is_arithmetic<T>::value, bool>::type = false
#define _CUTIL_CONCEPT_ARITHMETIC_CONVERTIBLE(From, To) \
			typename std::enable_if<cutil::internal::is_arithmetic_and_convertible<From, To>::value, bool>::type = true
#define _CUTIL_CONCEPT_INTEGRAL_CONVERTIBLE(From, To) 	\
			typename std::enable_if<cutil::internal::is_integral_and_convertible<From, To>::value, bool>::type = true
#define _CUTIL_CONCEPT_POINTER(T) 			\
			typename std::enable_if<std::is_pointer<T>::value, bool>::type = false

// #define _CUTIL_CONCEPT_IS_SAME(T1, T2) 	\
			// typename std::enable_if<std::is_same<T1, T2>::value, bool>::type = true
#define _CUTIL_CONCEPT_COMPARABLE(T, U) 	\
			typename = decltype(std::declval<T>() == std::declval<U>())

#define _CUTIL_CONCEPT_MEMBER(T, Member) 	\
			typename = decltype(std::declval<T>().Member)
#define _CUTIL_CONCEPT_FUNCTION(T, Func) 	\
			typename = decltype(Func(std::declval<T>()))

#define _CUTIL_CONCEPT_HAS_ITERATOR(T)  	\
			typename std::enable_if<cutil::internal::has_iterators<T>::value, bool>::type = true

#define _CUTIL_CONCEPT_SAME_SIZE(T, U) 		\
			typename std::enable_if<cutil::internal::has_same_size<T, U>::value, bool>::type = true
	
	



//=================== Comparison Statements =======================
inline namespace compare {

template<typename T, typename Arg, _CUTIL_CONCEPT_COMPARABLE(T, Arg)> _CUTIL_NODISCARD
inline bool equal_any(T&& compared, Arg&& a1) { // end of recursion
	return (std::forward<T>(compared) == std::forward<Arg>(a1));
}
template<typename T, typename Arg, _CUTIL_CONCEPT_COMPARABLE(T, Arg)> _CUTIL_NODISCARD
inline bool equal_all(T&& compared, Arg&& a1) { // end of recursion
	return (std::forward<T>(compared) == std::forward<Arg>(a1));
}
template<typename T, typename Arg, _CUTIL_CONCEPT_COMPARABLE(T, Arg)> _CUTIL_NODISCARD
inline bool unequal_any(T&& compared, Arg&& a1) { // end of recursion
	return (std::forward<T>(compared) != std::forward<Arg>(a1));
}
template<typename T, typename Arg, _CUTIL_CONCEPT_COMPARABLE(T, Arg)> _CUTIL_NODISCARD
inline bool unequal_all(T&& compared, Arg&& a1) { // end of recursion
	return (std::forward<T>(compared) != std::forward<Arg>(a1));
}
template<typename T, typename Arg, _CUTIL_CONCEPT_COMPARABLE(T, Arg)> _CUTIL_NODISCARD
inline bool unequal_mutually(T&& a1, Arg&& a2) { // end of recursion
	return (std::forward<T>(a1) != std::forward<Arg>(a2));
}

//* bool statement: `(compared == arg1 || compared == arg2 || compared == arg3 || ...)`
//  if 1st param `compared` is equal to ANY of the following arguments, return `true`
template<typename T, typename U, typename... E, _CUTIL_CONCEPT_COMPARABLE(T, U)> _CUTIL_NODISCARD
inline bool equal_any(T&& compared, U&& a1, E&&... a) {
	return (std::forward<T>(compared) == std::forward<U>(a1))
			|| cutil::compare::equal_any(std::forward<T>(compared), std::forward<E>(a)...);
}

//* bool statement: `(compared == arg1 && compared == arg2 && compared == arg3 && ...)`
//  if 1st param `compared` is equal to ALL of the following arguments, return `true`
template<typename T, typename U, typename... E, _CUTIL_CONCEPT_COMPARABLE(T, U)> _CUTIL_NODISCARD
inline bool equal_all(T&& compared, U&& a1, E&&... a) {
	return ((std::forward<T>(compared) == std::forward<U>(a1))
			&& cutil::compare::equal_all(std::forward<T>(compared), std::forward<E>(a)...));
}

//* bool statement: `(compared != arg1 || compared != arg2 || compared != arg3 || ...)`
//  if 1st param `compared` is NOT equal to Any of the following arguments, return `true`
template<typename T, typename U, typename... E, _CUTIL_CONCEPT_COMPARABLE(T, U)> _CUTIL_NODISCARD
inline bool unequal_any(T&& compared, U&& a1, E&&... a) {
	return ((std::forward<T>(compared) != std::forward<U>(a1))
			|| cutil::compare::unequal_any(std::forward<T>(compared), std::forward<E>(a)...));
}

//* bool statement: `(compared != arg1 && compared != arg2 && compared != arg3 && ...)`
//  if 1st param `compared` is NOT equal to ALL of the following arguments, return `true`
template<typename T, typename U, typename... E, _CUTIL_CONCEPT_COMPARABLE(T, U)> _CUTIL_NODISCARD
inline bool unequal_all(T&& compared, U&& a1, E&&... a) {
	return ((std::forward<T>(compared) != std::forward<U>(a1))
			&& cutil::compare::unequal_all(std::forward<T>(compared), std::forward<E>(a)...));
}

//* check if all of the variables are mutually nonequal, not recommanded for large amount of arguments
// if you want to compare more arguments, pls use `std::set` or `std::unordered_set` (hashset)
template<typename T, typename U, typename... E, _CUTIL_CONCEPT_COMPARABLE(T, U)> _CUTIL_NODISCARD
inline bool unequal_mutually(T&& a1, U&& a2, E&&... a) {
	return (cutil::unequal_all(std::forward<T>(a1), std::forward<U>(a2), std::forward<E>(a)...)
			&& cutil::compare::unequal_mutually(std::forward<T>(a2), std::forward<E>(a)...));
}

//* check if all of the variables are mutually equal
template<typename T, typename... E> _CUTIL_NODISCARD
inline bool equal_mutually(T&& a, E&&... e) {
	return cutil::compare::equal_all(std::forward<T>(a), std::forward<E>(e)...);
}
/* Instruction:
	int var = 10;
	if(cutil::equal_any(var, 2, 4, 6, 8, 10)){
		// equivalent to `if(var == 2 || var == 4 || var == 6 || var == 8 || var == 10)`
		// equivalent to `if(!CUTIL_UNEQUAL_ALL(var, 2, 4, 6, 8, 10))`
	}
	if(cutil::equal_all(var, 2, 4, 6, 8, 10)){
		// equivalent to `if(var == 2 && var == 4 && var == 6 && var == 8 && var == 10)`
		// equivalent to `if(cutil::equal_mutually(var, 2, 4, 6, 8, 10))`
		// equivalent to `if(!cutil::unequal_any(var, 2, 4, 6, 8, 10))`
	}
	
	//*-------------------------------------------
	if(cutil::unequal_all(var, 2, 4, 6, 8, 10)){
		// equivalent to `if(var != 2 && var != 4 && var != 6 && var != 8 && var != 10)`
		// equivalent to `if(! cutil::equal_any(var, 2, 4, 6, 8, 10))`
	}
	if(cutil::unequal_any(var, 2, 4, 6, 8, 10)){
		// equivalent to `if(var != 2 || var != 4 || var != 6 || var != 8 || var != 10)`
		// equivalent to `if(! cutil::equal_all(var, 2, 4, 6, 8, 10))`
	}
	
	//*----------------------------------------------
	if(cutil::unequal_mutually(a1, a2, a3, a4);){ // is `a1`, `a2`, `a3`, `a4` mutually different?
		// (  ((a1) != (a2) && (a1) != (a3) && (a1) != (a4))
		// && ((a2) != (a3) && (a2) != (a4))
		// && ((a3) != (a4))   )
	}
	
	if(cutil::equal_mutually(a1, a2, a3, a4, a5)){
		// ((a1) == (a2) && (a1) == (a3) && (a1) == (a4) && (a1) == (a5))
		// equivalent to `if(cutil::equal_all(a1, a2, a3, a4, a5))`
	}
*/
} // namespace compare

//======================== Repeat And Range Statements =========================
inline namespace range {
//* iterator utils
//* generate code like `it.begin(), it.end()`
#define CUTIL_IT_RANGE(_it) 		(_it).begin(), (_it).end()
//* generate code like `it.rbegin(), it.rend()`
#define CUTIL_CTI_RANGE(_it) 		(_it).cbegin(), (_it).cend()
//* generate code like `it.rbegin(), it.rend()`
#define CUTIL_RIT_RANGE(_it) 		(_it).rbegin(), (_it).rend()
//* generate code like `it.crbegin(), it.crend()`
#define CUTIL_CRIT_RANGE(_it) 		(_it).crbegin(), (_it).crend()
/* Example:
	std::vector<int> vec(10);
	std::iota(CUTIL_IT_RANGE(vec), 0); // fill vec with 0 to 9
*/


//* get if specified value is contained in the container, uses std::find() to compare as .end() iterator
//  unavailable for std::queue, std::priority_queue, std::deque
template<typename T, typename V, _CUTIL_CONCEPT_HAS_ITERATOR(T)> _CUTIL_NODISCARD
inline bool contains(const T& container, const V& value)
{ // value in std::find is const T&, no need to use std::forward<>()
	return (std::find(container.begin(), container.end(), value) != container.end());
}

// C++17 executionPolicy version
template<typename ExecutionPolicy, typename T, typename V, _CUTIL_CONCEPT_HAS_ITERATOR(T)>  _CUTIL_NODISCARD
inline bool contains(ExecutionPolicy&& policy, const T& container, const V& value) {
#ifdef CUTIL_CPP17_SUPPORTED
	return (std::find(std::forward<ExecutionPolicy>(policy), container.begin(), container.end(), value) != container.end());
#else
	return cutil::contains(container, value);
#endif
}
/*
	std::vector<int> vec = {1, 2, 3, 4, 5};
	if(cutil::contains(vec, 3)){
		// vec contains 3
	}
	if(cutil::contains(vec, 3)){
		// vec contains 3
	}
*/


//* erase all elements with specific value of `std::vector`/`std::deque`
template<typename T, typename V = T::value_type, _CUTIL_CONCEPT_HAS_ITERATOR(T), _CUTIL_CONCEPT_MEMBER(T, shrink_to_fit())>
inline size_t erase_vector(T& container, const V& value) {
// #ifdef CUTIL_CPP20_SUPPORTED
	// return std::erase(container, value);
// #else
	size_t count = 0;
	auto newIt = std::remove(container.begin(), container.end(), value);
	count = std::distance(newIt, container.end());
	container.erase(newIt, container.end());
	return count;
// #endif
}
/*
	std::vector<int> e1 = {1, 2, 2, 4, 2, 5, 4};
	size_t removed = cutil::erase_vector(e1, 2); // 4
	e1.clear();
	removed = cutil::erase_vector(e1, 6); // 0
*/




} // namespace range

//======================= Bit Operations ============================
inline namespace bit { // inline
	//* get bits filtered by mask, `(num & mask)`
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD
	inline constexpr T get_bit_by_mask(T num, T bit_mask) noexcept {
		return (num & bit_mask);
	}
	//* set bits specified by mask, `(num | mask)`
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD
	inline constexpr T set_bit_by_mask(T num, T bit_mask) noexcept {
		return (num | bit_mask);
	}
	//* clear bits specified by mask, `(num & ~mask)`
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD
	inline constexpr T clear_bit_by_mask(T num, T bit_mask) noexcept {
		return (num & (~bit_mask));
	}
	//* flip bits specified by mask, `(num ^ mask)`
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD
	inline constexpr T flip_bit_by_mask(T num, T bit_mask) noexcept {
		return (num ^ bit_mask);
	}
	//* check if bits filtered by mask are zero or not, `(bool)(num & mask)`
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD
	inline constexpr bool check_bit_by_mask(T num, T bit_mask) noexcept {
		return static_cast<bool>(cutil::bit::get_bit_by_mask(num, bit_mask));
	}
	
	//* get the bit filtered by nth bit, `(num & (1<<bit_idx))`
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD
	inline constexpr T get_bit_by_idx(T num, size_t bit_idx) noexcept {
		_CUTIL_CONSTEXPR_ASSERT(bit_idx < (8u * sizeof(T)));
		return cutil::bit::get_bit_by_mask(num, (T)((T)(1u) << bit_idx));
	}
	//* set the bit specified by nth bit, `(num | (1<<bit_idx))`
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD
	inline constexpr T set_bit_by_idx(T num, size_t bit_idx) noexcept {
		_CUTIL_CONSTEXPR_ASSERT(bit_idx < (8u * sizeof(T)));
		return cutil::bit::set_bit_by_mask(num, (T)((T)(1u) << bit_idx));
	}
	//* clear the bit specified by nth bit, `(num & ~(1<<bit_idx))`
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD
	inline constexpr T clear_bit_by_idx(T num, size_t bit_idx) noexcept {
		_CUTIL_CONSTEXPR_ASSERT(bit_idx < (8u * sizeof(T)));
		return cutil::bit::clear_bit_by_mask(num, (T)((T)(1u) << bit_idx));
	}
	//* flip the bit specified by nth bit, `(num ^ (1<<bit_idx))`
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD
	inline constexpr T flip_bit_by_idx(T num, size_t bit_idx) noexcept {
		_CUTIL_CONSTEXPR_ASSERT(bit_idx < (8u * sizeof(T)));
		return cutil::bit::flip_bit_by_mask(num, (T)((T)(1u) << bit_idx));
	}
	//* check if the bit filtered by nth bit is zero or not, `(bool)(num & (1<<bit_idx))`
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD
	inline constexpr bool check_bit_by_idx(T num, size_t bit_idx) noexcept {
		_CUTIL_CONSTEXPR_ASSERT(bit_idx < (8u * sizeof(T)));
		return static_cast<bool>(cutil::bit::get_bit_by_idx(num, bit_idx));
	}
	
	//* rotate bit left by step, `((num << step) | (num >> (sizeof(T) - step)))`
	//  use std::rotl() since C++20
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD
	inline constexpr T rotate_bit_left(T num, size_t step = 1) noexcept {
		_CUTIL_CONSTEXPR_ASSERT(step <= 8u * sizeof(T));
	#ifdef CUTIL_CXX20_SUPPORTED
		return std::rotl(num, step); // x86 and ARM have CPU instructions for this
	#else
		return ((num << step) | (num >> (8u * sizeof(T) - step)));
	#endif
	}
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD
	inline constexpr T rotl(T num, size_t step = 1) noexcept {
		return cutil::bit::rotate_bit_left(num, step);
	}
	
	//* rotate bit right by step, `((num >> step) | (num << (sizeof(T) - step)))`
	//  use std::rotr() since C++20
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD
	inline constexpr T rotate_bit_right(T num, size_t step = 1) noexcept {
		_CUTIL_CONSTEXPR_ASSERT(step <= 8u * sizeof(T));
	#ifdef CUTIL_CXX20_SUPPORTED
		return std::rotr(num, step); // x86 and ARM have CPU instructions for this
	#else
		return ((num >> step) | (num << (8u * sizeof(T) - step)));
	#endif
	}
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD
	inline constexpr T rotr(T num, size_t step = 1) noexcept {
		return cutil::bit::rotate_bit_right(num, step);
	}
	
	//* insert bit to the left, then shift others to right. `(bit >> 1) | (inserted << (bitSize - 1))`
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD
	inline constexpr T insert_bit_left(T num, bool inserted = true) noexcept {
		return (num >> 1) | (static_cast<T>(inserted) << (8u * sizeof(T) - 1));
	}
	
	//* insert bit to the right, then shift others to left. `(bit << 1) | inserted`
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD
	inline constexpr T insert_bit_right(T num, bool inserted = true) noexcept {
		return (num << 1) | static_cast<T>(inserted);
	}
	
	//* get lsb (least significant bit, the rightmost bit)
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD
	inline constexpr T get_lsb(T num) noexcept {
		return (num & 1);
	}
	
	//* get msb (most significant bit, the leftmost bit)
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD
	inline constexpr T get_msb(T num) noexcept {
		return (num & (1u << (8u * sizeof(T) - 1)));
	}
	
	//* has_single_bit, check if the number is power of 2 ({1, 2, 4, 8...})
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD
	inline constexpr bool has_single_bit(T num) noexcept {
	#ifdef CUTIL_CPP20_SUPPORTED
		return std::has_single_bit(num);
	#else
		return num != 0 && (num & (num - 1)) == 0;
	#endif
	}
	// check if the number is power of 2 ({1, 2, 4, 8...})
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD
	inline constexpr bool is_power_of_2(T num) noexcept {
		return cutil::bit::has_single_bit(num);
	}
/*
	uint16_t num {0};
	// operate bit by index, starts at 0. use them in a seperate line, and returns nothing
	num = cutil::bit::set_bit_by_idx(num, 1);   // equals to {num = num |  (1u << 0));}
	num = cutil::bit::clear_bit_by_idx(num, 2); // equals to {num = num & ~(1u << 2));}
	num = cutil::bit::flip_bit_by_idx(num, 3);  // equals to {num = num ^  (1u << 3));}
	if(cutil::bit::get_bit_by_idx(num, 0) != 0x0000){ // reading bit, if bit is 1, returns `(1<<bitIdx)`, NOT `1`
		printf("%x\n", num);
	}
	if(cutil::bit::check_bit_by_idx(num, 0) == true){ // reading bit, if bit is 1, returns `true`
		printf("%x\n", num);
	}
	
	// operate bit by mask
	num = cutil::bit::set_bit_by_mask(num, 0x2B00);   // equals to {num = num |  0x2B00;}
	num = cutil::bit::clear_bit_by_mask(num, 0x2B00); // equals to {num = num & ~0x2B00;}
	num = cutil::bit::flip_bit_by_mask(num, 0x1100);  // equals to {num = num ^  0x1100;}
	if(cutil::bit::get_bit_by_mask(num, 0x0022) != 0x0000){
		printf("%x\n", num);
	}
	if(cutil::bit::check_bit_by_mask(num, 0x0022) == true){ // reading bit, if bit is 1, returns `true`
		printf("%x\n", num);
	}
	
	// rotate bits. use them in a seperate line, and returns nothing
	uint16_t var {0b0001'0010'0011'0100};
	var = cutil::bit::rotate_bit_left(var, 1);	-> 0b0010'0100'0110'1000
	var = cutil::bit::rotate_bit_right(var, 1);	-> 0b0001'0010'0011'0100
	var = cutil::bit::rotate_bit_left(var, 4);	-> 0b0010'0100'0110'1000
	fmt::println("var={:#016b}", var);
	
	// insert bit.
	uint16_t var2 {0b0001'0010'0011'0100};
	var2 = cutil::bit::insert_bit_left(var2, true);	  -> 0b1000'1001'0001'1010
	var2 = cutil::bit::insert_bit_right(var2, false); -> 0b0001'0010'0011'0100
	
	// get msb and lsb (liftmost and rightmost bit)
	var = cutil::bit::get_msb(0xFFFF); // get msb -> 0x8000
	var = cutil::bit::get_lsb(0xFFFF); // get lsb -> 0x0001
	
	// check if the number is power of 2 ({1, 2, 4, 8...})
	bool out = cutil::bit::has_single_bit(num));
	
*/
	inline constexpr _CUTIL_NODISCARD
	uint8_t get_word_low(uint16_t word) {
		return (uint8_t)(word & 0xFF);
	}
	inline constexpr _CUTIL_NODISCARD
	uint8_t get_word_high(uint16_t word) {
		return (uint8_t)(word >> 8u);
	}
	inline void set_word_low(uint16_t& word, uint8_t val) {
		word = ((word & 0xFF00) | val);
	}
	inline void set_word_high(uint16_t& word, uint8_t val) {
		word = ((word & 0x00FF) | ((uint16_t)val << 8u));
	}
/*
	uint16_t v {0x1234};
	std::cout << cutil::memory::get_word_high(0x1234); // -> 12
	std::cout << cutil::memory::get_word_low(0x1234);  // -> 34
	cutil::memory::set_word_high(v, 0x56); // -> 0x5634
*/

} // namespace bit



//======================= Math Constants =========================

inline namespace numbers { // inline
	template <typename T, typename = std::enable_if_t<std::is_floating_point<T>::value>>
	struct Numbers {
		static constexpr T e 			= static_cast<T>(2.71828182845904523536); // e
		static constexpr T log2e 		= static_cast<T>(1.44269504088896340736); // log2(e)
		static constexpr T log10e 		= static_cast<T>(0.43429448190325182765); // log10(e)
		static constexpr T ln2 			= static_cast<T>(0.69314718055994530942); // ln(2)
		static constexpr T ln10 		= static_cast<T>(2.30258509299404568402); // ln(10)

		static constexpr T pi 			= static_cast<T>(3.14159265358979323846); // pi
		static constexpr T two_pi 		= static_cast<T>(6.28318530717958647692); // 2*pi
		static constexpr T three_pi 	= static_cast<T>(9.42477796076937971538); // 3*pi
		static constexpr T pi_2 		= static_cast<T>(1.57079632679489661923); // pi/2
		static constexpr T pi_3 		= static_cast<T>(1.04719755119659774615); // pi/3
		static constexpr T pi_4 		= static_cast<T>(0.78539816339744830962); // pi/4
		static constexpr T inv_pi 		= static_cast<T>(0.31830988618379067154); // 1/pi
		static constexpr T inv_sqrt_pi 	= static_cast<T>(0.56418958354775628694); // 1/sqrt(pi)
		static constexpr T two_inv_pi 	= static_cast<T>(0.63661977236758134308); // 2/pi
		static constexpr T two_sqrt_pi 	= static_cast<T>(1.12837916709551257390); // 2/sqrt(pi)

		static constexpr T sqrt2 		= static_cast<T>(1.41421356237309504880); // sqrt(2)
		static constexpr T inv_sqrt2 	= static_cast<T>(0.70710678118654752440); // 1/sqrt(2)
		static constexpr T sqrt3 		= static_cast<T>(1.73205080756887729353); // sqrt(3)
		static constexpr T inv_sqrt3 	= static_cast<T>(0.57735026918962576451); // 1/sqrt(3)

		static constexpr T phi 			= static_cast<T>(1.61803398874989484820); // (1 + sqrt(5)) / 2, golden ratio
		static constexpr T inv_phi 		= static_cast<T>(0.61803398874989484820); // 2 / (1 + sqrt(5)), inversed golden ratio

		static constexpr T egamma 		= static_cast<T>(0.57721566490153286060); // Euler-Mascheroni constant
	};
	//* alternatives for C++20 std::numbers
	//* double versions
	constexpr double e 				= Numbers<double>::e;
	constexpr double log2e 			= Numbers<double>::log2e;
	constexpr double log10e 		= Numbers<double>::log10e;
	constexpr double ln2 			= Numbers<double>::ln2;
	constexpr double ln10			= Numbers<double>::ln10;
		
	constexpr double pi 			= Numbers<double>::pi;
	constexpr double two_pi 		= Numbers<double>::two_pi;
	constexpr double three_pi 		= Numbers<double>::three_pi;
	constexpr double pi_2 			= Numbers<double>::pi_2;
	constexpr double pi_3 			= Numbers<double>::pi_3;
	constexpr double pi_4 			= Numbers<double>::pi_4;
	constexpr double inv_pi 		= Numbers<double>::inv_pi;
	constexpr double inv_sqrt_pi 	= Numbers<double>::inv_sqrt_pi;
	constexpr double two_inv_pi 	= Numbers<double>::two_inv_pi;
	constexpr double two_sqrt_pi 	= Numbers<double>::two_sqrt_pi;
	
	constexpr double sqrt2 			= Numbers<double>::sqrt2;
	constexpr double inv_sqrt2 		= Numbers<double>::inv_sqrt2;
	constexpr double sqrt3 			= Numbers<double>::sqrt3;
	constexpr double inv_sqrt3 		= Numbers<double>::inv_sqrt3;
	
	constexpr double phi 			= Numbers<double>::phi;
	constexpr double inv_phi 		= Numbers<double>::inv_phi;
		
	constexpr double egamma 		= Numbers<double>::egamma;
	
	//* float versions
	constexpr float e_f 			= Numbers<float>::e;
	constexpr float log2e_f 		= Numbers<float>::log2e;
	constexpr float log10e_f 		= Numbers<float>::log10e;
	constexpr float ln2_f 			= Numbers<float>::ln2;
	constexpr float ln10_f 			= Numbers<float>::ln10;
	
	constexpr float pi_f 			= Numbers<float>::pi;
	constexpr float two_pi_f 		= Numbers<float>::two_pi;
	constexpr float three_pi_f 		= Numbers<float>::three_pi;
	constexpr float pi_2_f 			= Numbers<float>::pi_2;
	constexpr float pi_3_f 			= Numbers<float>::pi_3;
	constexpr float pi_4_f 			= Numbers<float>::pi_4;
	constexpr float inv_pi_f 		= Numbers<float>::inv_pi;
	constexpr float inv_sqrt_pi_f 	= Numbers<float>::inv_sqrt_pi;
	constexpr float two_inv_pi_f 	= Numbers<float>::two_inv_pi;
	constexpr float two_sqrt_pi_f 	= Numbers<float>::two_sqrt_pi;
	
	constexpr float sqrt2_f 		= Numbers<float>::sqrt2;
	constexpr float inv_sqrt2_f 	= Numbers<float>::inv_sqrt2;
	constexpr float sqrt3_f 		= Numbers<float>::sqrt3;
	constexpr float inv_sqrt3_f 	= Numbers<float>::inv_sqrt3;
	
	constexpr float phi_f 			= Numbers<float>::phi;
	constexpr float inv_phi_f 		= Numbers<float>::inv_phi;
		
	constexpr float egamma_f 		= Numbers<float>::egamma;
	
	//* long double versions
	constexpr long double e_ld 				= Numbers<long double>::e;
	constexpr long double log2e_ld 			= Numbers<long double>::log2e;
	constexpr long double log10e_ld 		= Numbers<long double>::log10e;
	constexpr long double ln2_ld 			= Numbers<long double>::ln2;
	constexpr long double ln10_ld 			= Numbers<long double>::ln10;
	
	constexpr long double pi_ld 			= Numbers<long double>::pi;
	constexpr long double two_pi_ld 		= Numbers<long double>::two_pi;
	constexpr long double three_pi_ld 		= Numbers<long double>::three_pi;
	constexpr long double pi_2_ld 			= Numbers<long double>::pi_2;
	constexpr long double pi_3_ld 			= Numbers<long double>::pi_3;
	constexpr long double pi_4_ld 			= Numbers<long double>::pi_4;
	constexpr long double inv_pi_ld 		= Numbers<long double>::inv_pi;
	constexpr long double inv_sqrt_pi_ld 	= Numbers<long double>::inv_sqrt_pi;
	constexpr long double two_inv_pi_ld 	= Numbers<long double>::two_inv_pi;
	constexpr long double two_sqrt_pi_ld 	= Numbers<long double>::two_sqrt_pi;
	
	constexpr long double sqrt2_ld 			= Numbers<long double>::sqrt2;
	constexpr long double inv_sqrt2_ld 		= Numbers<long double>::inv_sqrt2;
	constexpr long double sqrt3_ld 			= Numbers<long double>::sqrt3;
	constexpr long double inv_sqrt3_ld 		= Numbers<long double>::inv_sqrt3;
	
	constexpr long double phi_ld 			= Numbers<long double>::phi;
	constexpr long double inv_phi_ld 		= Numbers<long double>::inv_phi;
	
	constexpr long double egamma_ld 		= Numbers<long double>::egamma;
}




//======================= Numeric and Math Operations =========================

inline namespace math { // inline
	//* limit the numeric variable to the range [_MIN, _MAX], same as `std::clamp(var, min, max)` in C++17
	template<typename T, typename R = T, _CUTIL_CONCEPT_ARITHMETIC_CONVERTIBLE(R, T)> _CUTIL_NODISCARD
	inline constexpr T clamp(T var, R min, R max) {
		_CUTIL_CONSTEXPR_ASSERT(min < max);
	#ifdef CUTIL_CPP17_SUPPORTED
		return std::clamp(var, min, max);
	#else
		return (var < min) ? min : (var > max) ? max : var;
	#endif
	}
	//* limit the numeric variable to the range [_MIN, _MAX], same as `var = std::clamp(var, min, max)` in C++17
	template<typename T, typename R = T, _CUTIL_CONCEPT_ARITHMETIC_CONVERTIBLE(R, T)>
	inline void limit(T& var, R min, R max) {
		var = math::clamp(var, min, max);
	}
	
	//* get if a numeric variable is within the interval [_MIN, _MAX]
	template<typename T, typename R = T, _CUTIL_CONCEPT_ARITHMETIC_CONVERTIBLE(R, T)> _CUTIL_NODISCARD
	inline constexpr bool num_in_interval(T var, R min, R max) {
		_CUTIL_CONSTEXPR_ASSERT(min < max);
		return (var >= min) && (var <= max);
	}
	//* get if a numeric variable is within the interval (_MIN, _MAX)
	template<typename T, typename R = T, _CUTIL_CONCEPT_ARITHMETIC_CONVERTIBLE(R, T)> _CUTIL_NODISCARD
	inline constexpr bool num_in_open_interval(T var, R min, R max) {
		_CUTIL_CONSTEXPR_ASSERT(min < max);
		return (var > min) && (var < max);
	}
	
#ifdef CUTIL_CPP17_SUPPORTED //* >= C++17
	//* Comparison function to check if a value is within a specified interval
	template <bool LeftClosed, bool RightClosed, typename T, typename R = T
			, _CUTIL_CONCEPT_ARITHMETIC_CONVERTIBLE(R, T)> _CUTIL_NODISCARD
	inline constexpr bool num_in_interval(T var, R min, R max) {
		_CUTIL_CONSTEXPR_ASSERT((min < max));
		if constexpr (LeftClosed && RightClosed) {
			return (var >= min) && (var <= max); // [min, max]
		} else if constexpr (LeftClosed && !RightClosed) {
			return (var >= min) && (var < max);  // [min, max)
		} else if constexpr (!LeftClosed && RightClosed) {
			return (var > min) && (var <= max);  // (min, max]
		} else {
			return (var > min) && (var < max);   // (min, max)
		}
	}
#else
	
#endif
/*
	int a = 35, b = 26, c = 19, d = 35;
	d = std::clamp(d, 20, 30);  		// C++17, equivalent to above
	d = cutil::math::clamp(d, 20, 30); 	// C++11, equivalent to above
	cutil::limit(d, 20, 30);			// d: 30, only modify value
	printf("%d %d %d\n", a, b, c); // output: 30 26 20
	

	bool ret = cutil::math::num_in_interval(a, 20, 40);				  // whether a is in [20, 40]
	bool ret = cutil::math::num_in_open_interval(c, 20, 30);		  // whether c is in (20, 30)
	bool ret = cutil::math::num_in_interval<true, true>(a, 20, 40);	  // whether a is in [20, 40], C++17
	bool ret = cutil::math::num_in_interval<true, false>(a, 20, 40);  // whether a is in [20, 40), C++17
	bool ret = cutil::math::num_in_interval<false, false>(a, 20, 40); // whether a is in [20, 40], C++17
*/


	//* increase the value of variable, but if the result exceeds the limit(>=), it will not be increased
	//  if exceeded, returns true.
	template<typename T, typename L = T, _CUTIL_CONCEPT_ARITHMETIC_CONVERTIBLE(L, T)>
	inline bool increase_under_limit(T& var, L max, int inc) noexcept {
		_CUTIL_ASSERT(var <= max && inc > 0);
		if((var + (T)inc) <= (T)max) {
			var += (T)inc;
			return false;
		}
		return true;
	}
	template<typename T, typename L = T, _CUTIL_CONCEPT_ARITHMETIC_CONVERTIBLE(L, T)>
	inline bool increase_under_limit(T& var, L max) noexcept {
		_CUTIL_ASSERT(var <= max);
		if(var < (T)max) {
			++var;
			return false;
		}
		return true;
	}
	// increase the value of variable, but if the result exceeds the limit(>=), it will be clamped to the limit
	// if clamped, returns true.
	template<typename T, typename L = T, _CUTIL_CONCEPT_ARITHMETIC_CONVERTIBLE(L, T)>
	inline bool increase_under_limit_clamp(T& var, L max, int inc) noexcept {
		if(cutil::math::increase_under_limit(var, max, inc)) {
			var = (T)max;
			return true;
		}
		return false;
	}
	
	//* decrease the value of variable, but if the result is less than the limit(<=), it will not be decreased
	//  if exceeded, returns true.
	template<typename T, typename L = T, _CUTIL_CONCEPT_ARITHMETIC_CONVERTIBLE(L, T)>
	inline bool decrease_above_limit(T& var, L min, int dec) noexcept {
		_CUTIL_ASSERT(var >= min && dec > 0);
		if((var - (T)dec) >= (T)min){
			var -= (T)dec;
			return false;
		}
		return true;
	}
	template<typename T, typename L = T, _CUTIL_CONCEPT_ARITHMETIC_CONVERTIBLE(L, T)>
	inline bool decrease_above_limit(T& var, L min) noexcept {
		_CUTIL_ASSERT(var >= min);
		if(var > (T)min){
			--var;
			return false;
		}
		return true;
	}
	// decrease the value of variable, but if the result is less than the limit(<=), it will be clamped to the limit
	// if clamped, returns true.
	template<typename T, typename L = T, _CUTIL_CONCEPT_ARITHMETIC_CONVERTIBLE(L, T)>
	inline bool decrease_above_limit_clamp(T& var, L min, int dec) noexcept {
		if(cutil::math::decrease_above_limit(var, min, dec)){
			var = (T)min;
			return true;
		}
		return false;
	}
	
	//* increase the value of variable, and rolling within the range [_MIN, _MAX]
	//  if rolled, returns true.
	template<typename T, typename R = T, _CUTIL_CONCEPT_ARITHMETIC_CONVERTIBLE(R, T)>
	inline bool increase_rolling(T& var, R min, R max, int inc) noexcept {
		_CUTIL_ASSERT(min < max && cutil::num_in_interval(var, min, max) && inc > 0);
		if((var + (T)inc) <= max){
			var += (T)inc;
			return false;
		}
		var = (T)min;
		return true;
	}
	template<typename T, typename R = T, _CUTIL_CONCEPT_ARITHMETIC_CONVERTIBLE(R, T)>
	inline bool increase_rolling(T& var, R min, R max) noexcept {
		_CUTIL_ASSERT(min < max && cutil::num_in_interval(var, min, max));
		if(var < (T)max){
			var++;
			return false;
		}
		var = (T)min;
		return true;
	}
	
	//* decrease the value of variable, and rolling within the range [_MIN, _MAX]
	//  if rolled, returns true.
	template<typename T, typename R = T, _CUTIL_CONCEPT_ARITHMETIC_CONVERTIBLE(R, T)>
	inline bool decrease_rolling(T& var, R min, R max, int dec) noexcept {
		_CUTIL_ASSERT(min < max && cutil::num_in_interval(var, min, max) && dec > 0);
		if((var - dec) >= min){
			var -= dec;
			return false;
		}
		var = max;
		return true;
	}
	template<typename T, typename R = T, _CUTIL_CONCEPT_ARITHMETIC_CONVERTIBLE(R, T)>
	inline bool decrease_rolling(T& var, R min, R max) noexcept {
		_CUTIL_ASSERT(min < max && cutil::num_in_interval(var, min, max));
		if(var > min){
			var--;
			return false;
		}
		var = max;
		return true;
	}
	
	//* increase the value of variable, and prevent overflowing,
	// if it is near to be overflowed, it will not increased any more and return true.
	template<typename T, _CUTIL_CONCEPT_ARITHMETIC(T)>
	inline bool increase_no_overflow(T& var, int inc = 1) noexcept {
		_CUTIL_ASSERT(inc > 0);
		return (static_cast<T>(var + inc) > var) ? (var += inc, false) : (true);
	}
	//* decrease the value of variable, and prevent underflowing,
	// if it is near to be underflowed, it will not decreased any more and return true.
	template<typename T, _CUTIL_CONCEPT_ARITHMETIC(T)>
	inline bool decrease_no_underflow(T& var, int dec = 1) noexcept {
		_CUTIL_ASSERT(dec > 0);
		return (static_cast<T>(var - dec) < var) ? (var -= dec, false) : (true);
	}
/*
	int8_t num = 0;
	cutil::math::increase_under_limit(num, 5, 1); // step:1, result: 1 2 3 4 5 5 5 5 5 5 5 5
	cutil::math::increase_under_limit(num, 5);    // step:1, result: 1 2 3 4 5 5 5 5 5 5 5 5
	cutil::math::decrease_above_limit(num, 0, 1); // step:1, result: 1 2 3 4 5 5 5 5 5 5 5 5
	cutil::math::decrease_above_limit(num, 0);    // step:1, result: 5 4 3 2 1 0 0 0 0 0 0 0

	cutil::math::increase_rolling(num, 0, 5, 1);  // step:1, result: 1 2 3 4 5 0 1 2 3 4 5 0
	cutil::math::increase_rolling(num, 0, 5);     // step:1, result: 1 2 3 4 5 0 1 2 3 4 5 0
	cutil::math::decrease_rolling(num, 0, 5, 1);  // step:1, result: 5 4 3 2 1 0 5 4 3 2 1 0
	cutil::math::decrease_rolling(num, 0, 5);     // step:1, result: 5 4 3 2 1 0 5 4 3 2 1 0
	
	num = 124;
	bool isOverflowed  = cutil::math::increase_no_overflow(num, 1); // prevent overflowing, 125 126 127 127 127 127, returns true if near to overflow
	bool isOverflowed2 = cutil::math::increase_no_overflow(num);    // equivelent
	num = -125;
	bool isOverflowed3 = cutil::math::decrease_no_underflow(num, 1); // prevent underflowing, -126 -127 -128 -128 -128 -128, returns true if near to overflow
	bool isOverflowed4 = cutil::math::decrease_no_underflow(num);    // equivelent

*/
	//* constexpr abs of an number, overloaded for unsigned integer types
	template<typename T, _CUTIL_CONCEPT_SIGNED_OR_FLOAT(T)> _CUTIL_NODISCARD constexpr
	inline T abs(T num) noexcept { // for signed intergers and `float`, `double`, `long double`
	#ifdef CUTIL_CPP23_SUPPORTED
		return std::abs(num);	// std::abs() is constexpr since C++23
	#else
		return (num < 0) ? -num : num;
	#endif
	}
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD constexpr
	inline T abs(T num) noexcept { // for `uint8_t`, `uint16_t`, `uint32_t`, `uint64_t`, `size_t`
		return num;
	}
	
	
	//* get gcd (greatest common divisor)
	template<typename T, _CUTIL_CONCEPT_INTEGRAL(T)> _CUTIL_NODISCARD _CUTIL_CONSTEXPR_CPP14
	inline T gcd(T a, T b) {
	#ifdef CUTIL_CPP17_SUPPORTED
		return std::gcd(a, b);
	#else
		if(b == 0) return cutil::math::abs(a);
		if(a == 0) return cutil::math::abs(b);
		return cutil::math::gcd(b, a % b);
	#endif
	}
	
	//* get lcm (least common multiple)
	template<typename T, _CUTIL_CONCEPT_INTEGRAL(T)> _CUTIL_NODISCARD _CUTIL_CONSTEXPR_CPP14
	inline T lcm(T a, T b) {
	#ifdef CUTIL_CPP17_SUPPORTED
		return std::lcm(a, b);
	#else
		return cutil::math::abs(a * b / cutil::math::gcd(a, b));
	#endif
	}
	
	
	//* Compares two floating-point numbers for equality within a specified epsilon.
	template<typename T, _CUTIL_CONCEPT_FLOAT(T)> _CUTIL_NODISCARD
	inline constexpr bool fequal(T a, T b, T epsilon = std::numeric_limits<T>::epsilon()) noexcept {
		_CUTIL_CONSTEXPR_ASSERT(epsilon >= 0);
		// _CUTIL_CONSTEXPR_ASSERT(std::isfinite(a) && std::isfinite(b) && std::isfinite(epsilon));
		return (std::abs(a - b) <= epsilon); // overloaded abs() for floating number in <cstdlib>
	}
/*
	bool isEqual4 = cutil::math::fequal(a, b); // (abs(a - b) <= std::numeric_limits<decltype(a)>::epsilon())
	bool isEqual5 = cutil::math::fequal(c, d, 0.0001); // equivelent
*/
	
	
	//* convert degrees to radians, (degree * M_PI / 180.0)
	// `cutil::fequal(cutil::numbers::pi_3, cutil::math::deg2rad(60.0)) == true`
	template<typename T, _CUTIL_CONCEPT_FLOAT(T)> _CUTIL_NODISCARD
	inline constexpr T deg2rad(T degree) noexcept {
		// _CUTIL_CONSTEXPR_ASSERT(std::isfinite(degree));
		return (degree * cutil::numbers::Numbers<T>::pi / (T)(180.0));
	}
	
	//* convert radians to degrees, (radian * 180.0 / M_PI)
	// `cutil::fequal(60.0, cutil::math::rad2deg(cutil::numbers::pi_3)) == true`
	template<typename T, _CUTIL_CONCEPT_FLOAT(T)> _CUTIL_NODISCARD
	inline constexpr T rad2deg(T radian) noexcept {
		// _CUTIL_CONSTEXPR_ASSERT(std::isfinite(radian));
		return (radian * (T)(180.0) / cutil::numbers::Numbers<T>::pi);
	}
	
	//* linear interpolation, (a + (b - a) * t)
	//  t should be in the range [0, 1]. if t = 0, returns a; if t == 1, returns b.
	//  use std::lerp() since C++20
	template<typename A, typename T, _CUTIL_CONCEPT_FLOAT(T), _CUTIL_CONCEPT_ARITHMETIC(A)> _CUTIL_NODISCARD
	inline constexpr T lerp(A a, A b, T t) noexcept {
		_CUTIL_CONSTEXPR_ASSERT(a <= b);
		// _CUTIL_CONSTEXPR_ASSERT(std::isfinite(t));
	#ifdef CUTIL_CPP20_SUPPORTED
		return std::lerp((T)a, (T)b, t);
	#else
		return ((T)a + t * ((T)b - (T)a));
	#endif
	}
	
	//* get midpoint of two numbers
	// if a and b are integers, the result is also truncated to an integer.
	template<typename T, _CUTIL_CONCEPT_ARITHMETIC(T)> _CUTIL_NODISCARD
	inline constexpr T midpoint(T a, T b) noexcept {
	#ifdef CUTIL_CPP20_SUPPORTED
		return std::midpoint(a, b);
	#else
		return (a + b) / 2;
	#endif
	}
	

	//* int ret = cutil::pow_int(2, 3); // 2^3 = 8
	//  size_t ret = cutil::pow_int<int, size_t>(2, 3); // return as size_t
	//  from https://stackoverflow.com/questions/1505675/power-of-an-integer-in-c
	template <typename T, typename R = T, _CUTIL_CONCEPT_INTEGRAL(T), _CUTIL_CONCEPT_INTEGRAL(R)> _CUTIL_NODISCARD
	inline _CUTIL_CONSTEXPR_CPP14 R pow_int(const T base, const size_t exp) {
		_CUTIL_CONSTEXPR_ASSERT(exp >= 0);
		if(exp == 0){
			return static_cast<R>(1);
		}
		if(exp == 1){
			return static_cast<R>(base);
		}
		if(exp == 2){
			return static_cast<R>(base * base);
		}
		if(exp == 3){
			return static_cast<R>(base * base * base);
		}
		int tmp = cutil::math::pow_int(base, exp/2);
		if (exp % 2 == 0){
			return static_cast<R>(tmp * tmp);
		}else{
			return static_cast<R>(base * tmp * tmp);
		}
	}

	//* int ret = cutil::factorial(3); // 3! = 6
	//  size_t ret = cutil::factorial<int, size_t>(3); // return as size_t
	template <typename T, typename R = T, _CUTIL_CONCEPT_INTEGRAL(T), _CUTIL_CONCEPT_INTEGRAL(R)> _CUTIL_NODISCARD
	inline _CUTIL_CONSTEXPR_CPP14 R factorial(const T base) {
		_CUTIL_CONSTEXPR_ASSERT(cutil::math::num_in_interval(base, 0, 40));
		if (base <= 1) {
			return static_cast<R>(1);
		}else if(base == 2){
			return static_cast<R>(2);
		}else if(base == 3){
			return static_cast<R>(6);
		}
		R result = base;
		for(T i = (base - 1); i > 1; --i){
			result *= i;
		}
		return result;
	}
	
#ifdef CUTIL_CPP17_SUPPORTED
	//* int ret = cutil::pow_int<3>(2); // 2^3 = 8, 需要 >=C++17
	//  size_t ret = cutil::pow_int<3, int, size_t>(2); // return as size_t
	//  from https://stackoverflow.com/questions/1505675/power-of-an-integer-in-c
	template <const size_t exp, typename T, typename R = T, _CUTIL_CONCEPT_INTEGRAL(T), _CUTIL_CONCEPT_INTEGRAL(R)> _CUTIL_NODISCARD
	inline constexpr R pow_int(const T base) {
		if constexpr (exp == 0) {
			return static_cast<R>(1);
		}else if constexpr (exp == 1) {
			return static_cast<R>(base);
		}else if constexpr (exp == 2) {
			return static_cast<R>(base * base);
		}else if constexpr (exp == 3) {
			return static_cast<R>(base * base * base);
		}
		R tmp = cutil::math::pow_int<exp / 2, T, R>(base);
		if (exp % 2 == 0){
			return static_cast<R>(tmp * tmp);
		}else{
			return static_cast<R>(base * tmp * tmp);
		}
	}
	
	//* int ret = cutil::factorial<3>(); // 3! = 6
	//  size_t ret = cutil::factorial<3, size_t>(); // return as size_t
	template <const size_t base, typename R = size_t, _CUTIL_CONCEPT_INTEGRAL(R)> _CUTIL_NODISCARD
	inline constexpr R factorial() {
		if constexpr (base <= 1) {
			return static_cast<R>(1);
		}else if constexpr (base == 2) {
			return static_cast<R>(2);
		}else if constexpr (base == 3) {
			return static_cast<R>(6);
		}else{
			return static_cast<R>(base) * cutil::math::factorial<base - 1, R>();
		}
	}
	
#else
	template <const size_t exp, typename T, typename R = T> _CUTIL_NODISCARD
	inline constexpr R pow_int(const T base) {
		return cutil::math::pow_int(base, exp);
	}
	
	template <const size_t base, typename R = size_t> _CUTIL_NODISCARD
	inline constexpr R factorial() {
		return cutil::math::factorial<R>(base);
	}
#endif // C++17
	
	
} // namespace math







//======================= Memory Operations =========================
inline namespace memory {
	
	//* assign bitwise, `(memcpy(&out, &in, sizeof(T)))`
	template<typename Out, typename In>
	inline void bitwise_memcpy(Out& out, In&& in) {
		// static_assert(std::is_trivially_copyable<Out>::value, "Out and In must be a trivially copyable type");
		// static_assert(std::is_trivially_copyable<std::decay<In>::type>::value, "In must be a trivially copyable type");
		static_assert(sizeof(Out) == sizeof(In), "Out and In must have same size");
		std::memcpy(&out, &in, sizeof(Out));
	}
	
	//* cast bitwise, `(reinterpret_cast<volatile Out*>(&in))`
	template<typename Out, typename In> _CUTIL_NODISCARD
	inline constexpr Out bit_cast(In&& in) noexcept {
		static_assert(sizeof(Out) == sizeof(In), "Out and In must have same size");
	#ifdef CUTIL_CPP20_SUPPORTED
		return std::bit_cast<Out>(in);
	#else
		return *reinterpret_cast<volatile Out*>(&in);
	#endif
	}
/*
	cutil::bitwise_memcpy(f, i) // i -> f, bitwise memcpy
	f = bit_cast<float>(i);   				// equivelent
	f = *reinterpret_cast<volatile float*>(&i); // equivelent
	std::memcpy(&f, &i, sizeof(f)); 			// equivelent
	f = std::bit_cast<float>(i) 				// C++20
*/



	
	
	//* get offset of two pointers in bytes
	template <typename T, typename U> _CUTIL_NODISCARD
	inline ptrdiff_t get_ptr_offset(T* higher, U* lower){
		return reinterpret_cast<uintptr_t>(higher) - reinterpret_cast<uintptr_t>(lower);
	}
	
	// get offset of the struct member to the struct base address
	template <typename U, typename T> _CUTIL_NODISCARD
	inline ptrdiff_t get_member_offset(T U::* member){
		return static_cast<ptrdiff_t>(reinterpret_cast<uintptr_t>(&(reinterpret_cast<U*>(0)->*member)));
	}
/*
	struct S { int a; int b; };
	ptrdiff_t offset = cutil::memory::get_member_offset(&A::b); // offset of b in struct S
	
	S s;
	ptrdiff_t offset = cutil::memory::get_ptr_offset(&s.a, &s.b); // offset of two pointers
	
*/

	// (UB) get value from the memory address in the specific type
	template<typename T, typename P, _CUTIL_CONCEPT_POINTER(P)> _CUTIL_NODISCARD _CUTIL_DEPRECATED _CUTIL_MAYBE_UNUSED
	inline T& read_memory(P ptr) {
		return *reinterpret_cast<T*>(ptr);
	}
	
	// (UB) set memory at the specific location in the specific type
	template<typename T, typename P, _CUTIL_CONCEPT_POINTER(P)> _CUTIL_DEPRECATED _CUTIL_MAYBE_UNUSED
	inline void write_memory(P ptr, T&& val) {
		static_assert(sizeof(T) == sizeof(*ptr), "Size of T must be equal to the size of the memory at ptr");
		*reinterpret_cast<T*>(ptr) = val;
	}
/*
	uint16_t num = 0x1234;
	// uint16_t num2 = cutil::read_memory<uint16_t>(&num); // 0x1234
	// cutil::write_memory<uint16_t>(&num, 0x5678); // num: 0x5678
*/

	
	//* wrapper for C memory functions, but specify amount of elements, not bytes
	template<typename T> _CUTIL_MAYBE_UNUSED
	inline T* memcpy_type(T* out, const T* in, size_t amount = 1) {
		return std::memcpy(out, in, sizeof(T) * amount);
	}
	template<typename T> _CUTIL_MAYBE_UNUSED
	inline T* memmove_type(T* out, const T* in, size_t amount = 1) {
		return std::memmove(out, in, sizeof(T) * amount);
	}
	template<typename T> _CUTIL_MAYBE_UNUSED
	inline T* memset_type(T& out, int value, size_t amount = 1) {
		return std::memset(&out, value, sizeof(T) * amount);
	}
	template<typename T> _CUTIL_MAYBE_UNUSED
	inline int memcmp_type(const T* ptr1, const T* ptr2, size_t amount = 1) {
		return std::memcmp(ptr1, ptr2, sizeof(T) * amount);
	}
	template<typename T> _CUTIL_MAYBE_UNUSED
	inline T* malloc_type(size_t amount = 1) {
		return static_cast<T*>(std::malloc(sizeof(T) * amount));
	}
	template <typename T> _CUTIL_MAYBE_UNUSED
	inline T* calloc_type(size_t amount = 1) {
		return static_cast<T*>(std::calloc(amount, sizeof(T)));
	}
	template<typename T> _CUTIL_MAYBE_UNUSED
	inline T* realloc_type(T* ptr, size_t amount = 1) {
		return static_cast<T*>(std::realloc(ptr, sizeof(T) * amount));
	}
	
	//* delete heap pointer and set it to nullptr
	template<typename T>
	inline void free_ptr(T*& ptr) {
		if(ptr != nullptr){
			std::free(ptr);
			ptr = nullptr;
		}
	}
	template<typename T>
	inline void delete_ptr(T*& p) {
		if(p != nullptr){
			delete p;
			p = nullptr;
		}
	}
	template<typename T>
	inline void delete_array(T*& p) {
		if(p != nullptr){
			delete[] p;
			p = nullptr;
		}
	}

	
} // namespace





//==================== C++ Class Utilities ========================

//* set C++11 class constructor/moving/copying to disabled/default
// Default Constructor(no params) and Destructor
#define CUTIL_CLASS_DEFAULT_CONSTRUCTOR(_CLASS_NAME) \
	_CLASS_NAME() = default; \
	~_CLASS_NAME() = default;

// Disable copy constructor and copy operator=
#define CUTIL_CLASS_DISABLE_COPY(_CLASS_NAME) \
	_CLASS_NAME(const _CLASS_NAME & ) = delete;\
	_CLASS_NAME& operator=(const _CLASS_NAME & ) = delete;

// Default copy constructor and copy operator=
#define CUTIL_CLASS_DEFAULT_COPY(_CLASS_NAME) \
	_CLASS_NAME(const _CLASS_NAME & ) = default;\
	_CLASS_NAME& operator=(const _CLASS_NAME & ) = default;

// Disable move constructor and move operator=
#define CUTIL_CLASS_DISABLE_MOVE(_CLASS_NAME) \
	_CLASS_NAME(_CLASS_NAME && ) noexcept = delete; \
	_CLASS_NAME& operator=(_CLASS_NAME && ) noexcept = delete;

// Default move constructor and move operator=
#define CUTIL_CLASS_DEFAULT_MOVE(_CLASS_NAME) \
	_CLASS_NAME(_CLASS_NAME && ) noexcept = default; \
	_CLASS_NAME& operator=(_CLASS_NAME && ) noexcept = default;

// Disable moving and copying
#define CUTIL_CLASS_DISABLE_COPY_MOVE(_CLASS_NAME) \
	CUTIL_CLASS_DISABLE_COPY(_CLASS_NAME) \
	CUTIL_CLASS_DISABLE_MOVE(_CLASS_NAME)

// Default moving and copying
#define CUTIL_CLASS_DEFAULT_COPY_MOVE(_CLASS_NAME) \
	CUTIL_CLASS_DEFAULT_COPY(_CLASS_NAME) \
	CUTIL_CLASS_DEFAULT_MOVE(_CLASS_NAME)

// Default Constructor, Destructor, Copying, Moving
#define CUTIL_CLASS_DEFAULT_FUNCTIONS(_CLASS_NAME) \
	CUTIL_CLASS_DEFAULT_CONSTRUCTOR(_CLASS_NAME) \
	CUTIL_CLASS_DEFAULT_COPY_MOVE(_CLASS_NAME)



//* generate getter and setter (>= C++11)
// generate getter and setter with specific type (not recommended after C++11, and do not add `const` to the first parameter)
#define CUTIL_GETTER_TYPE(_type, _name, _getter) 	public: _type _getter() {return this->_name;}
#define CUTIL_SETTER_TYPE(_type, _name, _setter) 	public: void _setter(const _type& _val)	{this->_name = _val;}
#define CUTIL_MEMBER_TYPE(_type, _name, ...)		CUTIL_EXPAND(CUTIL_OVERLOAD_IDX(_CUTIL_MEMBER_TYPE_, CUTIL_VA_CNT(__VA_ARGS__))(_type, _name, __VA_ARGS__))
#define _CUTIL_MEMBER_TYPE_2(_type, _name, _getter, _setter)	CUTIL_GETTER_TYPE(_type, _name, _getter) CUTIL_SETTER_TYPE(_type, _name, _setter)
#define _CUTIL_MEMBER_TYPE_1(_type, _name, _func)				_CUTIL_MEMBER_TYPE_2(_type, _name, _func, _func)

// generate getter and setter with type deducing (>=C++11, uses `std::decay<decltype(_name)>::type`)
#define CUTIL_GETTER(_name, _getter) 		CUTIL_GETTER_TYPE(CUTIL_TYPEOF(_name), _name, _getter)
#define CUTIL_SETTER(_name, _setter) 		CUTIL_SETTER_TYPE(CUTIL_TYPEOF(_name), _name, _setter)
#define CUTIL_MEMBER(_name, ...) 			CUTIL_EXPAND(CUTIL_MEMBER_TYPE(CUTIL_TYPEOF(_name), _name, __VA_ARGS__))
/* example:
	class Test {
		private: int m_a {};
		CUTIL_GETTER(m_a, getA) // public: int  getA() {return this->m_a;}
		CUTIL_SETTER(m_a, setA) // public: void setA(const int& _val) {this->m_a = _val;}
		
		private: double m_b {};
		CUTIL_MEMBER(m_b, getB, setB)
		// public: double getB() {return this->m_b;}
		// public:  void  setB(const double& _val) {this->m_b = _val;}

		private: std::string m_c {};
		CUTIL_MEMBER(m_c, c)
		// public: std::string c() {return this->m_c;}
		// public:      void   c(const std::string& _val) {this->m_c = _val;}
	};
	Test test;
	
	// print
	fmt::println("Test::m_a = {}", test.getA());
	
	test.setB(3.1615925);
	fmt::println("Test::m_b = {}", test.getB());

	test.c("hello world!");
	fmt::println("Test::m_c = {}", test.c());
*/






_CUTIL_NAMESPACE_END
#endif // __cplusplus
#endif // CONSOLEUTIL_CPP_UTIL_H__
