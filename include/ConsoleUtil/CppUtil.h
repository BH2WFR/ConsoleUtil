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
_CUTIL_NAMESPACE_BEGIN



//===================== Bool Statements =========================

template<typename T, typename Arg> _CUTIL_NODISCARD
inline bool equal_any(const T& compared, const Arg& a1) { // end of recursion
	return (compared == a1);
}
template<typename T, typename Arg> _CUTIL_NODISCARD
inline bool equal_all(const T& compared, const Arg& a1) { // end of recursion
	return (compared == a1);
}
template<typename T, typename Arg> _CUTIL_NODISCARD
inline bool unequal_any(const T& compared, const Arg& a1) { // end of recursion
	return (compared != a1);
}
template<typename T, typename Arg> _CUTIL_NODISCARD
inline bool unequal_all(const T& compared, const Arg& a1) { // end of recursion
	return (compared != a1);
}
template<typename T, typename Arg> _CUTIL_NODISCARD
inline bool unequal_mutually(const T& a1, const Arg& a2) { // end of recursion
	return (a1 != a2);
}

//* bool statement: `(compared == arg1 || compared == arg2 || compared == arg3 || ...)`
//  if 1st param `compared` is equal to ANY of the following arguments, return `true`
template<typename T, typename Arg1, typename... ArgElse> _CUTIL_NODISCARD
inline bool equal_any(const T& compared, const Arg1& a1, const ArgElse&... a) {
	return (compared == a1) || equal_any(compared, a...);
}

//* bool statement: `(compared == arg1 && compared == arg2 && compared == arg3 && ...)`
//  if 1st param `compared` is equal to ALL of the following arguments, return `true`
template<typename T, typename Arg1, typename... ArgElse> _CUTIL_NODISCARD
inline bool equal_all(const T& compared, const Arg1& a1, const ArgElse&... a) {
	return ((compared == a1) && equal_all(compared, a...));
}

//* bool statement: `(compared != arg1 || compared != arg2 || compared != arg3 || ...)`
//  if 1st param `compared` is NOT equal to Any of the following arguments, return `true`
template<typename T, typename Arg1, typename... ArgElse> _CUTIL_NODISCARD
inline bool unequal_any(const T& compared, const Arg1& a1, const ArgElse&... a) {
	return ((compared != a1) || unequal_any(compared, a...));
}

//* bool statement: `(compared != arg1 && compared != arg2 && compared != arg3 && ...)`
//  if 1st param `compared` is NOT equal to ALL of the following arguments, return `true`
template<typename T, typename Arg1, typename... ArgElse> _CUTIL_NODISCARD
inline bool unequal_all(const T& compared, const Arg1& a1, const ArgElse&... a) {
	return ((compared != a1) && unequal_all(compared, a...));
}

//* check if all of the variables are mutually nonequal, not recommanded for large amount of arguments
// if you want to compare more arguments, pls use `std::set` or `std::unordered_set` (hashset)
template<typename T, typename Arg1, typename... ArgElse> _CUTIL_NODISCARD
inline bool unequal_mutually(const T& a1, const Arg1& a2, const ArgElse&... a) {
	return (unequal_all(a1, a2, a...) && unequal_all(a2, a...));
}

//* check if all of the variables are mutually equal
template<typename T, typename... Args> _CUTIL_NODISCARD
inline bool equal_mutually(const T& a, const Args&... args) {
	return equal_all(a, args...);
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


//======================== Repeat And Range Statements =========================
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
template<typename T, typename V> inline _CUTIL_NODISCARD
bool contains(const T& container, const V& value) {
	return (std::find(container.begin(), container.end(), value) != container.end());
}
/*
	std::vector<int> vec = {1, 2, 3, 4, 5};
	if(cutil::contains(vec, 3)){
		// vec contains 3
	}
*/




//======================= Bit Operations ============================
inline namespace bit { // inline
	//* get bits filtered by mask, (num & mask)
	template<typename T> _CUTIL_NODISCARD
	inline constexpr T get_bit_by_mask(T num, T bit_mask) {
		static_assert(std::is_integral<T>::value, "T must be an integral type");
		return (num & bit_mask);
	}
	//* set bits specified by mask, (num |= mask)
	template<typename T> _CUTIL_NODISCARD
	inline constexpr T set_bit_by_mask(T num, T bit_mask) {
		static_assert(std::is_integral<T>::value, "T must be an integral type");
		return (num |= bit_mask);
	}
	//* clear bits specified by mask, (num &= ~mask)
	template<typename T> _CUTIL_NODISCARD
	inline constexpr T clear_bit_by_mask(T num, T bit_mask) {
		static_assert(std::is_integral<T>::value, "T must be an integral type");
		return (num &= (~bit_mask));
	}
	//* flip bits specified by mask, (num ^= mask)
	template<typename T> _CUTIL_NODISCARD
	inline constexpr T flip_bit_by_mask(T num, T bit_mask) {
		static_assert(std::is_integral<T>::value, "T must be an integral type");
		return (num ^= bit_mask);
	}
	//* check if bits filtered by mask are zero or not, (bool)(num & mask)
	template<typename T> _CUTIL_NODISCARD
	inline constexpr bool check_bit_by_mask(T num, T bit_mask) {
		static_assert(std::is_integral<T>::value, "T must be an integral type");
		return static_cast<bool>(get_bit_by_mask(num, bit_mask));
	}
	
	//* get the bit filtered by nth bit, (num & (1<<bit_idx))
	template<typename T> _CUTIL_NODISCARD
	inline constexpr T get_bit_by_idx(T num, size_t bit_idx) {
		static_assert(std::is_integral<T>::value, "T must be an integral type");
		return get_bit_by_mask(num, (1u << bit_idx));
	}
	//* set the bit specified by nth bit, (num |= (1<<bit_idx))
	template<typename T> _CUTIL_NODISCARD
	inline constexpr T set_bit_by_idx(T num, size_t bit_idx) {
		static_assert(std::is_integral<T>::value, "T must be an integral type");
		return set_bit_by_mask(num, (1u << bit_idx));
	}
	//* clear the bit specified by nth bit, (num &= ~(1<<bit_idx))
	template<typename T> _CUTIL_NODISCARD
	inline constexpr T clear_bit_by_idx(T num, size_t bit_idx) {
		static_assert(std::is_integral<T>::value, "T must be an integral type");
		return bit_clear_mask(num, (1u << bit_idx));
	}
	//* flip the bit specified by nth bit, (num ^= (1<<bit_idx))
	template<typename T> _CUTIL_NODISCARD
	inline constexpr T flip_bit_by_idx(T num, size_t bit_idx) {
		static_assert(std::is_integral<T>::value, "T must be an integral type");
		return bit_flip_mask(num, (1u << bit_idx));
	}
	//* check if the bit filtered by nth bit is zero or not, (bool)(num & (1<<bit_idx))
	template<typename T> _CUTIL_NODISCARD
	inline constexpr bool check_bit_by_idx(T num, size_t bit_idx) {
		static_assert(std::is_integral<T>::value, "T must be an integral type");
		return static_cast<bool>(get_bit_by_idx(num, bit_idx));
	}
	
	//* rotate bit left by step, (num = ((num << step) | (num >> (sizeof(T) - step))))
	template<typename T> _CUTIL_NODISCARD
	inline constexpr T rotate_bit_left(T bit, const size_t step = 1) {
		static_assert(std::is_integral<T>::value, "T must be an integral type");
		return bit = ((bit << step) | (bit >> (8u * sizeof(T) - step)));
	}
	//* rotate bit right by step, (num = ((num >> step) | (num << (sizeof(T) - step))))
	template<typename T> _CUTIL_NODISCARD
	inline constexpr T rotate_bit_right(T bit, const size_t step = 1) {
		static_assert(std::is_integral<T>::value, "T must be an integral type");
		return bit = ((bit >> step) | (bit << (8u * sizeof(T) - step)));
	}
} // namespace
/*
	uint16_t num {0};
	// operate bit by index, starts at 0. use them in a seperate line, and returns nothing
	num = cutil::bit::set_bit_by_idx(num, 1);   // equals to {num |=  (1u << 0));}
	num = cutil::bit::clear_bit_by_idx(num, 2); // equals to {num &= ~(1u << 2));}
	num = cutil::bit::flip_bit_by_idx(num, 3);  // equals to {num ^=  (1u << 3));}
	if(cutil::bit::get_bit_by_idx(num, 0) != 0x0000){ // reading bit, if bit is 1, returns `(1<<bitIdx)`, NOT `1`
		printf("%x\n", num);
	}
	if(cutil::bit::check_bit_by_idx(num, 0) == true){ // reading bit, if bit is 1, returns `true`
		printf("%x\n", num);
	}
	
	// operate bit by mask
	num = cutil::bit::set_bit_by_mask(num, 0x2B00);   // equals to {num |=  0x2B00;}
	num = cutil::bit::clear_bit_by_mask(num, 0x2B00); // equals to {num &= ~0x2B00;}
	num = cutil::bit::flipByMask(num, 0x1100);  // equals to {num ^=  0x1100;}
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
	
*/




//* assign bitwise, (memcpy(&out, &in, sizeof(T)))
template<typename Out, typename In>
inline void bitwise_memcpy(Out& out, const In& in) {
	static_assert(std::is_trivially_copyable<Out>::value, "Out and In must be a trivially copyable type");
	static_assert(std::is_trivially_copyable<In>::value, "In must be a trivially copyable type");
	static_assert(sizeof(Out) == sizeof(In), "Out and In must have same size");
	std::memcpy(&out, &in, sizeof(Out));
}
/*
	cutil::bitwise_memcpy(f, i) // i -> f, bitwise memcpy
	f = reinterpret_cast<decltype(f)>(i);   // equivelent
	// auto f = std::bit_cast<float>(i) // C++20
*/



//======================= Numeric and Math Operations =========================
inline namespace math { // inline
	//* limit the numeric variable to the range [_MIN, _MAX], same as `std::clamp(var, min, max)` in C++17
	template<typename T, typename R> _CUTIL_NODISCARD
	inline constexpr T clamp(T var, R min, R max) {
		// static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
		return (var < min) ? min : (var > max) ? max : var;
	}
	//* limit the numeric variable to the range [_MIN, _MAX], same as `var = std::clamp(var, min, max)` in C++17
	template<typename T, typename R>
	inline void limit(T& var, R min, R max) {
		// static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
		if (var < min) var = min;
		if (var > max) var = max;
	}
	
	//* get if a numeric variable is within the range [_MIN, _MAX]
	template<typename T, typename R> _CUTIL_NODISCARD
	inline constexpr bool num_in_range(T var, R min, R max) {
		// static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
		return (var >= min) && (var <= max);
	}
	//* get if a numeric variable is within the range (_MIN, _MAX)
	template<typename T, typename R> _CUTIL_NODISCARD
	inline constexpr bool num_in_open_range(T var, R min, R max) {
		// static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
		return (var > min) && (var < max);
	}
	
#ifdef CUTIL_CPP17_SUPPORTED //* >= C++17
	//* Comparison function to check if a value is within a specified range
	template <bool LeftClosed, bool RightClosed, typename T> _CUTIL_NODISCARD
	inline constexpr bool num_in_range(T var, T min, T max) {
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
#endif
/*
	int a = 35, b = 26, c = 19, d = 35;
	d = std::clamp(d, 20, 30);  		// C++17, equivalent to above
	d = cutil::math::clamp(d, 20, 30); 	// C++11, equivalent to above
	cutil::limit(d, 20, 30);			// d: 30, only modify value
	printf("%d %d %d\n", a, b, c); // output: 30 26 20
	

	bool ret = cutil::math::num_in_range(a, 20, 40);				  // whether a is in [20, 40]
	bool ret = cutil::math::num_in_open_range(c, 20, 30);			  // whether c is in (20, 30)
	bool ret = cutil::math::num_in_range<true, true>(a, 20, 40);	  // whether a is in [20, 40], C++17
	bool ret = cutil::math::num_in_range<true, false>(a, 20, 40);  // whether a is in [20, 40), C++17
	bool ret = cutil::math::num_in_range<false, false>(a, 20, 40); // whether a is in [20, 40], C++17
*/


	//* increase the value of variable, but if the value exceeds the limit(>=), it will not be increased
	template<typename T, typename L, typename I>
	inline void increase_under_limit(T& var, L max, I inc) {
		// static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
		if(var < max) var += inc;
	}
	template<typename T, typename L>
	inline void increase_under_limit(T& var, L max){
		// static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
		if(var < max) ++var;
	}
	
	//* decrease the value of variable, but if the value is less than the limit(<=), it will not be decreased
	template<typename T, typename L, typename I>
	inline void decrease_above_limit(T& var, L min, I dec) {
		// static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
		if(var > min) var -= dec;
	}
	template<typename T, typename L>
	inline void decrease_above_limit(T& var, L min){
		// static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
		if(var > min) --var;
	}
	
	//* increase the value of variable, and rolling within the range [_MIN, _MAX]
	template<typename T, typename R, typename I>
	inline void increase_rolling(T& var, R min, R max, I inc) {
		// static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
		if(var < max) var += inc;
		else var = min;
	}
	template<typename T, typename R>
	inline void increase_rolling(T& var, R min, R max) {
		// static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
		if(var < max) var++;
		else var = min;
	}
	
	//* decrease the value of variable, and rolling within the range [_MIN, _MAX]
	template<typename T, typename R, typename I>
	inline void decrease_rolling(T& var, R min, R max, I dec) {
		// static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
		if(var > min) var -= dec;
		else var = max;
	}
	template<typename T, typename R>
	inline void decrease_rolling(T& var, R min, R max) {
		// static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
		if(var > min) var--;
		else var = max;
	}
	
	//* increase the value of variable, and prevent overflowing,
	// if it is near to be overflowed, it will not increased any more and return true.
	template<typename T, typename I>
	inline constexpr bool increase_no_overflow(T& var, I inc) {
		// static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
		return ((T)(var + inc) > var) ? (var += inc, false) : (true);
	}
	template<typename T>
	inline constexpr bool increase_no_overflow(T& var) {
		// static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
		return ((T)(var + 1) > var) ? (var++, false) : (true);
	}
	//* decrease the value of variable, and prevent overflowing,
	// if it is near to be overflowed, it will not decreased any more and return true.
	template<typename T, typename I>
	inline constexpr bool decrease_no_overflow(T& var, I dec) {
		// static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
		return ((T)(var - dec) < var) ? (var -= dec, false) : (true);
	}
	template<typename T>
	inline constexpr bool decrease_no_overflow(T& var) {
		// static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
		return ((T)(var - 1) < var) ? (var--, false) : (true);
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
	bool isOverflowed3 = cutil::math::decrease_no_overflow(num, 1); // prevent overflowing, -126 -127 -128 -128 -128 -128, returns true if near to overflow
	bool isOverflowed4 = cutil::math::decrease_no_overflow(num);    // equivelent

*/
	
	
	
	//* Compares two floating-point numbers for equality within a specified epsilon.
	template<typename T> _CUTIL_NODISCARD
	inline constexpr bool fequal(T a, T b, T epsilon = std::numeric_limits<T>::epsilon()) {
		static_assert(std::is_floating_point<T>::value, "T must be a floating point type");
		return (std::abs(a - b) <= epsilon); // overloaded abs() for floating number in <cstdlib>
	}
/*
	bool isEqual4 = cutil::math::fequal(a, b); // (abs(a - b) <= std::numeric_limits<decltype(a)>::epsilon())
	bool isEqual5 = cutil::math::fequal(c, d, 0.0001); // equivelent
*/
	
	
	//* int ret = cutil::pow_int(2, 3); // 2^3 = 8, needs >=C++14
	//  size_t ret = cutil::pow_int<int, size_t>(2, 3); // return as size_t
	template <typename T, typename R = T> _CUTIL_NODISCARD
	inline _CUTIL_CONSTEXPR_CPP14 R pow_int(const T base, const size_t exp) {
		static_assert(std::is_integral<T>::value, "Exponent must be an integer value.");
		static_assert(std::is_integral<R>::value, "Return type must be an integer value.");
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
		R result = base;
		for(size_t i = 1; i < exp; ++i){
			result *= base;
		}
		return result;
	}

	//* int ret = cutil::factorial(3); // 3! = 6
	//  size_t ret = cutil::factorial<int, size_t>(3); // return as size_t
	template <typename T, typename R = T> _CUTIL_NODISCARD
	inline _CUTIL_CONSTEXPR_CPP14 R factorial(const T base) {
		static_assert(std::is_integral<T>::value, "factorial must be an integer value.");
		static_assert(std::is_integral<R>::value, "Return type must be an integer value.");
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
	template <const size_t exp, typename T, typename R = T>
	inline constexpr R pow_int(const T base) {
		static_assert(std::is_integral<T>::value, "Exponent must be an integer value.");
		static_assert(std::is_integral<R>::value, "Return type must be an integer value.");
		if constexpr (exp == 0) {
			return static_cast<R>(1);
		}else if constexpr (exp == 1) {
			return static_cast<R>(base);
		}else{
			return (static_cast<R>(base) * math::pow_int<exp - 1, T, R>(base));
		}
	}
	
	//* int ret = cutil::factorial<3>(); // 3! = 6
	//  size_t ret = cutil::factorial<3, size_t>(); // return as size_t
	template <const size_t base, typename R = size_t>
	inline constexpr R factorial() {
		static_assert(std::is_integral<R>::value, "Return type must be an integer value.");
		if constexpr (base <= 1) {
			return static_cast<R>(1);
		}else if constexpr (base == 2) {
			return static_cast<R>(2);
		}else if constexpr (base == 3) {
			return static_cast<R>(6);
		}else{
			return static_cast<R>(base) * math::factorial<base - 1, R>();
		}
	}
	
#else
	template <const size_t exp, typename T, typename R = T>
	inline constexpr R pow_int(const T base) {
		static_assert(std::is_integral<T>::value, "Exponent must be an integer value.");
		static_assert(std::is_integral<R>::value, "Return type must be an integer value.");
		return math::pow_int(base, exp);
	}
	
	template <const size_t base, typename R = size_t>
	inline constexpr R factorial() {
		static_assert(std::is_integral<R>::value, "Return type must be an integer value.");
		return math::factorial<R>(base);
	}
#endif // C++17
	
	
} // namespace math






//======================= Math Constants =========================

namespace numbers { // not inline
	template <typename T>
	struct Numbers {
		static_assert(std::is_floating_point<T>::value, "T must be a floating-point type");
		static constexpr T e 			= 2.71828182845904523536;	// e
		static constexpr T log2e 		= 1.44269504088896340736;	// log2(e)
		static constexpr T log10e 		= 0.43429448190325182765;	// log10(e)
		static constexpr T ln2 			= 0.69314718055994530942;	// ln(2)
		static constexpr T ln10 		= 2.30258509299404568402;	// ln(10)

		static constexpr T pi 			= 3.14159265358979323846;	// pi
		static constexpr T two_pi 		= 6.28318530717958647692;	// 2*pi
		static constexpr T three_pi 	= 9.42477796076937971538;	// 3*pi
		static constexpr T pi_2 		= 1.57079632679489661923;	// pi/2
		static constexpr T pi_3 		= 1.04719755119659774615;	// pi/3
		static constexpr T pi_4 		= 0.78539816339744830962;	// pi/4
		static constexpr T inv_pi 		= 0.31830988618379067154;	// 1/pi
		static constexpr T inv_sqrt_pi 	= 0.56418958354775628694;	// 1/sqrt(pi)
		static constexpr T two_inv_pi 	= 0.63661977236758134308;	// 2/pi
		static constexpr T two_sqrt_pi 	= 1.12837916709551257390;	// 2/sqrt(pi)

		static constexpr T sqrt2 		= 1.41421356237309504880;	// sqrt(2)
		static constexpr T inv_sqrt2 	= 0.70710678118654752440;	// 1/sqrt(2)
		static constexpr T sqrt3 		= 1.73205080756887729353;	// sqrt(3)
		static constexpr T inv_sqrt3 	= 0.57735026918962576451;	// 1/sqrt(3)

		static constexpr T phi 			= 1.61803398874989484820;	// (1 + sqrt(5)) / 2, golden ratio
		static constexpr T inv_phi 		= 0.61803398874989484820;	// 2 / (1 + sqrt(5)), inversed golden ratio

		static constexpr T egamma 		= 0.57721566490153286060;	// Euler-Mascheroni constant
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





//======================= Memory Operations =========================
inline namespace memory {
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

	//* get pointer (in specific type) which points to the address of specific variable
	template<typename T, typename P = void*> _CUTIL_NODISCARD
	inline constexpr P get_ptr(T& var) { // T must be a left-value reference
		static_assert(std::is_pointer<P>::value, "P must be a pointer type");
		return static_cast<P>(&var);
	}
	
	//* get value from the memory address in the specific type
	template<typename T, typename P> _CUTIL_NODISCARD
	inline constexpr T read_memory(P ptr) {
		static_assert(std::is_pointer<P>::value, "P must be a pointer type");
		return *reinterpret_cast<T*>(ptr);
	}
	
	//* set memory at the specific location in the specific type
	template<typename T, typename P>
	inline void write_memory(P ptr, T val) {
		static_assert(std::is_pointer<P>::value, "P must be a pointer type");
		*reinterpret_cast<T*>(ptr) = val;
	}
	
	// wrapper for C memory functions
	template<typename T> _CUTIL_MAYBE_UNUSED
	inline T* memcpy(T* out, const T* in, size_t size) {
		static_assert(std::is_trivially_copyable<T>::value, "T must be a trivially copyable type");
		return std::memcpy(out, in, size);
	}
	template<typename T> _CUTIL_MAYBE_UNUSED
	inline T* memmove(T* out, const T* in, size_t size) {
		static_assert(std::is_trivially_copyable<T>::value, "T must be a trivially copyable type");
		return std::memmove(out, in, size);
	}
	template<typename T> _CUTIL_MAYBE_UNUSED
	inline T* memset(T& out, int value, size_t size) {
		static_assert(std::is_trivially_copyable<T>::value, "T must be a trivially copyable type");
		return std::memset(&out, value, size);
	}
	template <typename T> _CUTIL_MAYBE_UNUSED
	inline int memcmp(const T* ptr1, const T* ptr2, size_t size) {
		static_assert(std::is_trivially_copyable<T>::value, "T must be a trivially copyable type");
		return std::memcmp(ptr1, ptr2, size);
	}
	
	//* wrapper for C memory functions, but specify amount of elements, not bytes
	template<typename T> _CUTIL_MAYBE_UNUSED
	inline T* memcpy_type(T* out, const T* in, size_t amount = 1) {
		return memory::memcpy(out, in, sizeof(T) * amount);
	}
	template<typename T> _CUTIL_MAYBE_UNUSED
	inline T* memmove_type(T* out, const T* in, size_t amount = 1) {
		return memory::memmove(out, in, sizeof(T) * amount);
	}
	template<typename T> _CUTIL_MAYBE_UNUSED
	inline T* memset_type(T& out, int value, size_t amount = 1) {
		return memory::memset(&out, value, sizeof(T) * amount);
	}
	template<typename T> _CUTIL_MAYBE_UNUSED
	inline int memcmp_type(const T* ptr1, const T* ptr2, size_t amount = 1) {
		return memory::memcmp(ptr1, ptr2, sizeof(T) * amount);
	}
	
	//* delete heap pointer and set it to nullptr
	template<typename T>
	inline void free(T*& ptr) {
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
namespace internal {
	template <bool isDestructorVirtual>
	class EmptyClass {};
	
	template<>
	class EmptyClass<true> {
	public:
		virtual ~EmptyClass() = default;
	};
	
	template<>
	class EmptyClass<false> {
	public:
		~EmptyClass() = default;
	};
} // namespace internal

//* Non Copyable base class
template<bool isDestructorVirtual = false>
class NonCopyable : public internal::EmptyClass<isDestructorVirtual> {
public:
	NonCopyable() = default;
	NonCopyable(const NonCopyable&) = delete;
	NonCopyable& operator=(const NonCopyable&) = delete;
};

//* Non Movable base class
template<bool isDestructorVirtual = false>
class NonMovable : public internal::EmptyClass<isDestructorVirtual> {
public:
	NonMovable() = default;
	NonMovable(NonMovable&&) = delete;
	NonMovable& operator=(NonMovable&&) = delete;
};

//* Non Copyable And Movable base class
template<bool isDestructorVirtual = false>
class NonCopyableAndMovable : public NonCopyable<isDestructorVirtual>, public NonMovable<isDestructorVirtual>
{};
/*
	class nocopy : cutil::NonCopyable<> {
		~nocopy() = default;
	};
	class nocopy2 : cutil::NonCopyable<true> {
		virtual ~nocopy2() = default;
	};

*/



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
