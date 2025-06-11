/* UTF-8 encoding
* Project URL: https://github.com/BH2WFR/ConsoleUtil
  Author:		BH2WFR
  Updated:		10 JUN 2025
  License:		MIT License
* You can include this header in header files.
* C++14 or later is required.
*/
#ifndef CONSOLEUTIL_CPP_UTIL_H__
#define CONSOLEUTIL_CPP_UTIL_H__
#include <ConsoleUtil/Base.h>

#ifndef CUTIL_CPP14_SUPPORTED
	#error ">= C++14 is required"
#endif

#if defined(__cplusplus)
#include <type_traits>
#include <algorithm>
#include <iterator>
#include <cassert>
#include <cmath>
#include <numeric>
#include <limits>
#include <functional>
#ifdef CUTIL_CPP20_SUPPORTED
	#include <bit>
#endif


_CUTIL_NAMESPACE_BEGIN


//===============  concepts ================
namespace internal {
	template <typename T>
	struct is_uint : std::integral_constant<bool
					, std::is_integral<T>::value
					&& std::is_unsigned<T>::value
					&& !std::is_same<std::remove_cv_t<T>, bool>::value
			> {};
	
	template <typename T>
	struct is_signed_or_float : std::integral_constant<bool
					, (std::is_signed<T>::value && !std::is_same<std::remove_cv_t<T>, bool>::value)
					|| std::is_floating_point<T>::value
			> {};
	
	template <typename From, typename To = From>
	struct is_arithmetic_and_convertible : std::integral_constant<bool
				, std::is_arithmetic<From>::value
				&& std::is_arithmetic<To>::value
				&& std::is_convertible<From, To>::value
				&& !std::is_same<std::remove_cv_t<From>, bool>::value
				&& !std::is_same<std::remove_cv_t<To>, bool>::value
			>{};
	
	template <typename From, typename To = From>
	struct is_integral_and_convertible : std::integral_constant<bool
				, std::is_integral<From>::value
				&& std::is_integral<To>::value
				&& std::is_convertible<From, To>::value
				&& !std::is_same<std::remove_cv_t<From>, bool>::value
				&& !std::is_same<std::remove_cv_t<To>, bool>::value
			>{};
	
	template <typename T>
	struct has_iterators : std::integral_constant<bool
				, std::is_same<decltype(std::declval<T>().begin()), decltype(std::declval<T>().end())>::value
			>{};
	
	template <typename T, typename U>
	struct has_same_size : std::integral_constant<bool, sizeof(T) == sizeof(U)>{};
	
	template <typename Ptr>
	struct remove_const_pointer_to_type {
		using type = typename std::remove_const_t<typename std::remove_pointer_t<Ptr>>;
	};
	
	template <typename P1, typename P2>
	struct is_same_pointer_types : std::integral_constant<bool
								,  std::is_pointer<P1>::value
								&& std::is_pointer<P2>::value
								&& std::is_same<typename cutil::internal::remove_const_pointer_to_type<P1>::type
											  , typename cutil::internal::remove_const_pointer_to_type<P2>::type
									>::value
							>{};
	
	template <typename P1, typename P2>
	struct is_pointer_both_same_attributes : std::integral_constant<bool
										,  std::is_pointer<P1>::value
										&& std::is_pointer<P2>::value
										&& (   std::is_const<typename std::remove_pointer_t<P1>>::value
											== std::is_const<typename std::remove_pointer_t<P2>>::value)
										&& (  std::is_volatile<typename std::remove_pointer_t<P1>>::value
											== std::is_volatile<typename std::remove_pointer_t<P2>>::value)
									>{};
	
	template <typename PBase, typename PDerived>
	struct is_base_of_pointer : std::integral_constant<bool
									,  std::is_pointer<PBase>::value
									&& std::is_pointer<PDerived>::value
									&& std::is_base_of<
											  typename cutil::internal::remove_const_pointer_to_type<PBase>::type
											, typename cutil::internal::remove_const_pointer_to_type<PDerived>::type
										>::value
									>{};
	

	
#ifndef CUTIL_CPP17_SUPPORTED // C++14
	namespace detail {
		// SFINAE辅助模板
		template<bool B, typename T = void>
		using enable_if_t = typename std::enable_if_t<B, T>;

		// 检测函数调用并转换返回类型
		template<typename R, typename F, typename... Args>
		auto is_invocable_r_helper(F&& f, Args&&... args) ->
			decltype(static_cast<R>(std::forward<F>(f)(std::forward<Args>(args)...)), std::true_type{});
		template<typename R, typename F, typename... Args>
		std::false_type is_invocable_r_helper(...);

		// 主实现类
		template<typename R, typename F, typename... Args>
		struct is_invocable_r_impl {
			using type = decltype(is_invocable_r_helper<R>(
				std::declval<F>(), std::declval<Args>()...
			));
		};
	}
	// C++17 std::void_t implementation for C++14
	template <typename...>
	using void_t = void;
	
	// C++17 std:is_invocable implementation for C++14
	template<typename R, typename F, typename... Args>
	struct is_invocable_r : cutil::internal::detail::is_invocable_r_impl<R, F, Args...>::type {};

	template<typename F, typename... Args>
	struct is_invocable : cutil::internal::detail::is_invocable_r_impl<void, F, Args...>::type {};

#else // >= C++17
	template <typename...>
	using void_t = std::void_t<>;
	
	template<typename R, typename F, typename... Args>
	using is_invocable_r = std::is_invocable_r<R, F, Args...>;

	template<typename F, typename... Args>
	using is_invocable = std::is_invocable<F, Args...>;
#endif
} // internal
#define _CUTIL_CONCEPT(_TYPE) 				\
			typename std::enable_if_t<_TYPE, bool> = false
#define _CUTIL_CONCEPT_SAME_REMOVE_CV(T1, T2) 	\
			typename std::enable_if_t<std::is_same<std::remove_cv_t<T1>, std::remove_cv_t<T2>>::value, bool> = true
#define _CUTIL_CONCEPT_UNSIGNED(T) 			\
			typename std::enable_if_t<cutil::internal::is_uint<T>::value, bool> = false
#define _CUTIL_CONCEPT_INTEGRAL(T) 			\
			typename std::enable_if_t<std::is_integral<T>::value && !std::is_same<std::remove_cv_t<T>, bool>::value, bool> = false
#define _CUTIL_CONCEPT_FLOAT(T) 			\
			typename std::enable_if_t<std::is_floating_point<T>::value, bool> = false
#define _CUTIL_CONCEPT_FLOAT_WITHOUT_LONGDOUBLE(T) \
			typename std::enable_if_t<std::is_floating_point<T>::value && !std::is_same<std::remove_cv_t<T>, long double>::value, bool> = false
#define _CUTIL_CONCEPT_SIGNED_OR_FLOAT(T) 	\
			typename std::enable_if_t<cutil::internal::is_signed_or_float<T>::value, bool> = false
#define _CUTIL_CONCEPT_ARITHMETIC(T)		\
			typename std::enable_if_t<std::is_arithmetic<T>::value && !std::is_same<std::remove_cv_t<T>, bool>::value, bool> = false
#define _CUTIL_CONCEPT_ARITHMETIC_CONVERTIBLE(From, To) \
			typename std::enable_if_t<cutil::internal::is_arithmetic_and_convertible<From, To>::value, bool> = true
// #define _CUTIL_CONCEPT_INTEGRAL_CONVERTIBLE(From, To) 	\
// 			typename std::enable_if_t<cutil::internal::is_integral_and_convertible<From, To>::value, bool> = true
#define _CUTIL_CONCEPT_POINTER(T) 			\
			typename std::enable_if_t<std::is_pointer<T>::value, bool> = false
// #define _CUTIL_CONCEPT_IS_SAME(T1, T2) 	\
// 			typename std::enable_if_t<std::is_same<T1, T2>::value, bool> = true
// #define _CUTIL_CONCEPT_IS_DIFFERENT(T1, T2) \
// 			typename std::enable_if_t<!std::is_same<T1, T2>::value, bool> = true
#define _CUTIL_CONCEPT_CONVERTIBLE(From, To) \
			typename std::enable_if_t<std::is_convertible<From, To>::value, bool> = true
#define _CUTIL_CONCEPT_POINTER_DIFFERENT_TYPES(P1, P2) \
			typename std::enable_if_t<!cutil::internal::is_same_pointer_types<P1, P2>::value, bool> = true
#define _CUTIL_CONCEPT_POINTER_SAME_ATTRIBUTES(P1, P2) \
			typename std::enable_if_t<cutil::internal::is_pointer_both_same_attributes<P1, P2>::value, bool> = true
#define _CUTIL_CONCEPT_POINTER_IS_BASE_OF(PBase, PDerived) \
			typename std::enable_if_t<cutil::internal::is_base_of_pointer<PBase, PDerived>::value, bool> = true
#define _CUTIL_CONCEPT_COMPARABLE(T, U, COMP) 	\
			typename = decltype(std::declval<T>() COMP std::declval<U>())

#define _CUTIL_CONCEPT_MEMBER(T, Member) 	\
			typename = decltype(std::declval<T>().Member)
#define _CUTIL_CONCEPT_FUNCTION(T, Func, ...) 	\
			typename = decltype(Func(std::declval<T>(__VA_ARGS__)))
#define _CUTIL_CONCEPT_INVOKABLE(Func, ...) 	\
			typename = decltype(std::declval<Func>()(__VA_ARGS__))
#define _CUTIL_CONCEPT_INVOKABLE_RET(Func, Ret, ...) 	\
			typename = decltype(std::declval<Func>()(__VA_ARGS__) == std::declval<Ret>())
#define _CUTIL_CONCEPT_HAS_ITERATOR(T)  	\
			typename std::enable_if_t<cutil::internal::has_iterators<T>::value, bool> = true

#define _CUTIL_CONCEPT_SAME_SIZE(T, U) 		\
			typename std::enable_if_t<cutil::internal::has_same_size<T, U>::value, bool> = true





//=================== Comparison Statements =======================
inline namespace compare {
template<typename T> inline constexpr bool equal_any(T&& compared) noexcept {
	return false; // end of recursion
}
template<typename T> inline constexpr bool equal_all(T&& compared) noexcept {
	return true; // end of recursion
}
template<typename T> inline constexpr bool unequal_any(T&& compared) noexcept {
	return false; // end of recursion
}
template<typename T> inline constexpr bool unequal_all(T&& compared) noexcept {
	return true; // end of recursion
}
template<typename T> inline constexpr bool unequal_mutually(T&& a1) noexcept {
	return true; // end of recursion
}
template<typename T> inline constexpr bool equal_mutually(T&& a1) noexcept {
	return true; // end of recursion
}
template<typename T> inline constexpr bool increasing(T&& a1) noexcept {
	return true; // end of recursion
}
template<typename T> inline constexpr bool increasing_equal(T&& a1) noexcept {
	return true; // end of recursion
}
template<typename T> inline constexpr bool decreasing(T&& a1) noexcept {
	return true; // end of recursion
}
template<typename T> inline constexpr bool decreasing_equal(T&& a1) noexcept {
	return true; // end of recursion
}

//* bool statement: `(compared == arg1 || compared == arg2 || compared == arg3 || ...)`
//  if 1st param `compared` is equal to ANY of the following arguments, return `true`
template<typename T, typename U, typename... E, _CUTIL_CONCEPT_COMPARABLE(T, U, ==)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
inline constexpr bool equal_any(T&& compared, U&& a1, E&&... a) noexcept {
	return (std::forward<T>(compared) == std::forward<U>(a1))
			|| cutil::compare::equal_any(std::forward<T>(compared), std::forward<E>(a)...);
}

//* bool statement: `(compared == arg1 && compared == arg2 && compared == arg3 && ...)`
//  if 1st param `compared` is equal to ALL of the following arguments, return `true`
template<typename T, typename U, typename... E, _CUTIL_CONCEPT_COMPARABLE(T, U, ==)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
inline constexpr bool equal_all(T&& compared, U&& a1, E&&... a) noexcept {
	return ((std::forward<T>(compared) == std::forward<U>(a1))
			&& cutil::compare::equal_all(std::forward<T>(compared), std::forward<E>(a)...));
}

//* bool statement: `(compared != arg1 || compared != arg2 || compared != arg3 || ...)`
//  if 1st param `compared` is NOT equal to ANY of the following arguments, return `true`
template<typename T, typename U, typename... E, _CUTIL_CONCEPT_COMPARABLE(T, U, !=)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
inline constexpr bool unequal_any(T&& compared, U&& a1, E&&... a) noexcept {
	return ((std::forward<T>(compared) != std::forward<U>(a1))
			|| cutil::compare::unequal_any(std::forward<T>(compared), std::forward<E>(a)...));
}

//* bool statement: `(compared != arg1 && compared != arg2 && compared != arg3 && ...)`
//  if 1st param `compared` is NOT equal to ALL of the following arguments, return `true`
template<typename T, typename U, typename... E, _CUTIL_CONCEPT_COMPARABLE(T, U, !=)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
inline constexpr bool unequal_all(T&& compared, U&& a1, E&&... a) noexcept {
	return ((std::forward<T>(compared) != std::forward<U>(a1))
			&& cutil::compare::unequal_all(std::forward<T>(compared), std::forward<E>(a)...));
}

//* check if all of the variables are mutually nonequal, not recommended for large amount of arguments
// if you want to compare more arguments, pls use `std::set` or `std::unordered_set` (hashset)
template<typename T, typename U, typename... E, _CUTIL_CONCEPT_COMPARABLE(T, U, !=)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
inline constexpr bool unequal_mutually(T&& a1, U&& a2, E&&... a) noexcept {
	return (cutil::unequal_all(std::forward<T>(a1), std::forward<U>(a2), std::forward<E>(a)...)
			&& cutil::compare::unequal_mutually(std::forward<T>(a2), std::forward<E>(a)...));
}

//* check if all of the variables are mutually equal `(a1 == a2 && a2 == a3 && ...)`
template<typename T, typename U, typename... E, _CUTIL_CONCEPT_COMPARABLE(T, U, ==)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
inline constexpr bool equal_mutually(T&& a1, U&& a2, E&&... a) noexcept {
	return ((std::forward<T>(a1) == std::forward<U>(a2))
			&& cutil::compare::equal_mutually(std::forward<T>(a2), std::forward<E>(a)...));
}

//* check if all of the variables are mutually increasing, `(a1 < a2 && a2 < a3 && ...)`
template<typename T, typename U, typename... E, _CUTIL_CONCEPT_COMPARABLE(T, U, <)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
inline constexpr bool increasing(T&& a1, U&& a2, E&&... a) noexcept {
	return ((std::forward<T>(a1) < std::forward<U>(a2))
			&& cutil::compare::increasing(std::forward<T>(a2), std::forward<E>(a)...));
}

//* check if all of the variables are mutually increasing or equal, `(a1 <= a2 && a2 <= a3 && ...)`
template<typename T, typename U, typename... E, _CUTIL_CONCEPT_COMPARABLE(T, U, <=)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
inline constexpr bool increasing_equal(T&& a1, U&& a2, E&&... a) noexcept {
	return ((std::forward<T>(a1) <= std::forward<U>(a2))
			&& cutil::compare::increasing_equal(std::forward<T>(a2), std::forward<E>(a)...));
}

//* check if all of the variables are mutually decreasing, `(a1 > a2 && a2 > a3 && ...)`
template<typename T, typename U, typename... E, _CUTIL_CONCEPT_COMPARABLE(T, U, >)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
inline constexpr bool decreasing(T&& a1, U&& a2, E&&... a) noexcept {
	return ((std::forward<T>(a1) > std::forward<U>(a2))
			&& cutil::compare::decreasing(std::forward<T>(a2), std::forward<E>(a)...));
}

//* check if all of the variables are mutually decreasing or equal, `(a1 >= a2 && a2 >= a3 && ...)`
template <typename T, typename U, typename... E, _CUTIL_CONCEPT_COMPARABLE(T, U, >=)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
inline constexpr bool decreasing_equal(T&& a1, U&& a2, E&&... a) noexcept {
	return ((std::forward<T>(a1) >= std::forward<U>(a2))
			&& cutil::compare::decreasing_equal(std::forward<T>(a2), std::forward<E>(a)...));
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
	
	//*--------------------------------------
	bool b1 = cutil::increasing(1, 2, 3, 4, 5); // true
	bool b2 = cutil::increasing(1, 2, 3, 3, 5); // false
	bool b3 = cutil::decreasing(5, 4, 3, 2, 1); // true
	bool b4 = cutil::decreasing(5, 4, 3, 3, 1); // false
	bool b5 = cutil::increasing_equal(1, 2, 3, 3, 5); // true
	bool b6 = cutil::decreasing_equal(5, 4, 3, 3, 1); // true
*/
} // namespace compare

//======================== Repeat And Range Statements =========================
inline namespace range {
//* iterator utils
//* generate code like `container.begin(), container.end()`
#define CUTIL_IT_RANGE(_container) 		(_container).begin(), (_container).end()
//* generate code like `container.rbegin(), container.rend()`
#define CUTIL_CTI_RANGE(_container) 	(_container).cbegin(), (_container).cend()
//* generate code like `container.rbegin(), container.rend()`
#define CUTIL_RIT_RANGE(_container) 	(_container).rbegin(), (_container).rend()
//* generate code like `container.crbegin(), container.crend()`
#define CUTIL_CRIT_RANGE(_container) 	(_container).crbegin(), (_container).crend()
/* Example:
	std::vector<int> vec(10);
	std::iota(CUTIL_IT_RANGE(vec), 0); // fill vec with 0 to 9
*/


//* get if specified value is contained in the container, uses std::find() to compare as .end() iterator
//  unavailable for std::queue, std::priority_queue, std::deque
template<typename T, typename V, _CUTIL_CONCEPT_HAS_ITERATOR(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
inline bool contains(const T& container, const V& value)
{ // value in std::find is const T&, no need to use std::forward<>()
	return (std::find(container.begin(), container.end(), value) != container.end());
}

//* get if specified value by predicate is contained in the container
template<typename T, typename Pred, typename V = typename T::value_type, _CUTIL_CONCEPT_HAS_ITERATOR(T)
	, _CUTIL_CONCEPT_INVOKABLE_RET(Pred, bool, std::declval<V>())> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
inline bool contains_if(const T& container, Pred pred) {
	return (std::find_if(container.begin(), container.end(), pred) != container.end());
}
/*
	std::vector<int> vec = {1, 2, 3, 4, 5};
	if(cutil::contains(vec, 3)){
		// vec contains 3
	}
	if(cutil::contains(std::execution::par_seq, vec, 3)){
		// vec contains 3
	}
	if(cutil::contains_if(vec, [](int i){return i == 3;})){
		// vec contains 3
	}
*/

// C++17 executionPolicy version
template<typename ExecutionPolicy, typename T, typename Pred, typename V = typename T::value_type, _CUTIL_CONCEPT_HAS_ITERATOR(T)
	, _CUTIL_CONCEPT_INVOKABLE_RET(Pred, bool, std::declval<V>())> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
inline bool contains_if(ExecutionPolicy&& policy, const T& container, Pred pred) {
#ifdef CUTIL_CPP17_SUPPORTED
	return (std::find_if(std::forward<ExecutionPolicy>(policy), container.begin(), container.end(), pred) != container.end());
#else
	return cutil::contains_if(container, pred);
#endif
}

template<typename ExecutionPolicy, typename T, typename V, _CUTIL_CONCEPT_HAS_ITERATOR(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
inline bool contains(ExecutionPolicy&& policy, const T& container, const V& value) {
#ifdef CUTIL_CPP17_SUPPORTED
	return (std::find(std::forward<ExecutionPolicy>(policy), container.begin(), container.end(), value) != container.end());
#else
	return cutil::contains(container, value);
#endif
}



//* erase all elements with specific value of `std::vector`/`std::deque`
template<typename T, typename V = typename T::value_type, _CUTIL_CONCEPT_HAS_ITERATOR(T), _CUTIL_CONCEPT_MEMBER(T, shrink_to_fit())> _CUTIL_FUNC_STATIC
inline size_t erase_vector(T& container, const V& value) {
// #ifdef CUTIL_CPP20_SUPPORTED
	// return std::erase(container, value); // compiled with error
// #else
	auto newIt = std::remove(container.begin(), container.end(), value);
	size_t count = std::distance(newIt, container.end());
	container.erase(newIt, container.end()); // iterator will be invalidated
	return count;
// #endif
}

//* erase all elements by predicate of `std::vector`/`std::deque`
template <typename T, typename Pred, typename V = typename T::value_type, _CUTIL_CONCEPT_HAS_ITERATOR(T), _CUTIL_CONCEPT_MEMBER(T, shrink_to_fit())
	, _CUTIL_CONCEPT_INVOKABLE_RET(Pred, bool, std::declval<V>())> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
inline size_t erase_if_vector(T& container, Pred pred) {
// #ifdef CUTIL_CPP20_SUPPORTED
	// return std::erase_if(container, pred); // compiled with error
// #else
	size_t count = 0;
	auto newIt = std::remove_if(container.begin(), container.end(), pred);
	count = std::distance(newIt, container.end());
	container.erase(newIt, container.end());
	return count;
// #endif
}
/*
	std::vector<int> e1 = {1, 2, 2, 4, 2, 5, 4};
	size_t removed = cutil::erase_vector(e1, 2); // 3
	removed = cutil::erase_if_vector(e1, [](int i){return i == 4;}); // 2
	e1.clear();
	removed = cutil::erase_vector(e1, 6); // 0
*/



} // namespace range


//======================= Bit Operations ============================
inline namespace bit { // inline
	//* get bits filtered by mask, `(num & mask)`
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T get_bit_by_mask(T num, T bit_mask) noexcept {
		return (num & bit_mask);
	}
	//* set bits specified by mask, `(num | mask)`
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T set_bit_by_mask(T num, T bit_mask) noexcept {
		return (num | bit_mask);
	}
	//* clear bits specified by mask, `(num & ~mask)`
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T clear_bit_by_mask(T num, T bit_mask) noexcept {
		return (num & (~bit_mask));
	}
	//* flip bits specified by mask, `(num ^ mask)`
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T flip_bit_by_mask(T num, T bit_mask) noexcept {
		return (num ^ bit_mask);
	}
	//* check if bits filtered by mask are zero or not, `(bool)(num & mask)`
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr bool check_bit_by_mask(T num, T bit_mask) noexcept {
		return static_cast<bool>(cutil::bit::get_bit_by_mask(num, bit_mask));
	}
	
	//* get the bit filtered by nth bit, `(num & (1<<bit_idx))`
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T get_bit_by_idx(T num, size_t bit_idx) noexcept {
		return cutil::bit::get_bit_by_mask(num, static_cast<T>(static_cast<T>(1u) << (bit_idx % std::numeric_limits<T>::digits)));
	}
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T get_bit_by_idx(T num, std::initializer_list<size_t> bit_idx) noexcept {
		T mask = static_cast<T>(0);
		for(auto idx : bit_idx) {
			mask |= (static_cast<T>(1u) << (idx % std::numeric_limits<T>::digits));
		}
		return cutil::bit::get_bit_by_mask(num, mask);
	}
	
	//* set the bit specified by nth bit, `(num | (1<<bit_idx))`
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T set_bit_by_idx(T num, size_t bit_idx) noexcept {
		return cutil::bit::set_bit_by_mask(num, static_cast<T>(static_cast<T>(1u) << (bit_idx % std::numeric_limits<T>::digits)));
	}
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T set_bit_by_idx(T num, std::initializer_list<size_t> bit_idx) noexcept {
		T mask = static_cast<T>(0);
		for(auto idx : bit_idx) {
			mask |= (static_cast<T>(1u) << (idx % std::numeric_limits<T>::digits));
		}
		return cutil::bit::set_bit_by_mask(num, mask);
	}
	
	//* clear the bit specified by nth bit, `(num & ~(1<<bit_idx))`
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T clear_bit_by_idx(T num, size_t bit_idx) noexcept {
		return cutil::bit::clear_bit_by_mask(num, static_cast<T>(static_cast<T>(1u) << (bit_idx % std::numeric_limits<T>::digits)));
	}
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T clear_bit_by_idx(T num, std::initializer_list<size_t> bit_idx) noexcept {
		T mask = static_cast<T>(0);
		for(auto idx : bit_idx) {
			mask |= (static_cast<T>(1u) << (idx % std::numeric_limits<T>::digits));
		}
		return cutil::bit::clear_bit_by_mask(num, mask);
	}
	
	//* flip the bit specified by nth bit, `(num ^ (1<<bit_idx))`
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T flip_bit_by_idx(T num, size_t bit_idx) noexcept {
		return cutil::bit::flip_bit_by_mask(num, static_cast<T>(static_cast<T>(1u) << (bit_idx % std::numeric_limits<T>::digits)));
	}
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T flip_bit_by_idx(T num, std::initializer_list<size_t> bit_idx) noexcept {
		T mask = static_cast<T>(0);
		for(auto idx : bit_idx) {
			mask |= (static_cast<T>(1u) << (idx % std::numeric_limits<T>::digits));
		}
		return cutil::bit::flip_bit_by_mask(num, mask);
	}
	
	//* check if the bit filtered by nth bit is zero or not, `(bool)(num & (1<<bit_idx))`
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr bool check_bit_by_idx(T num, size_t bit_idx) noexcept {
		return static_cast<bool>(cutil::bit::get_bit_by_idx(num, bit_idx));
	}
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr bool check_bit_by_idx(T num, std::initializer_list<size_t> bit_idx) noexcept {
		return static_cast<bool>(cutil::bit::get_bit_by_idx(num, bit_idx));
	}
	
	//* rotate bit left by step, `((num << step) | (num >> (N - step)))`
	//  use std::rotl() since C++20
	//  if /O2 is enabled, this will be optimized to a single instruction on x86 and ARM
	//  also, you can use `_rotl()` `_rotl64()` in MSVC
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T rotate_bit_left(T num, int step = 1) noexcept {
	#ifdef CUTIL_CPP20_SUPPORTED
		return std::rotl(num, static_cast<int>(step)); // x86 and ARM have CPU instructions for this
	#else
		constexpr auto digits = std::numeric_limits<T>::digits;
		step = step % digits; // ensure step is within range
		if(step > 0){
			return ((num << step) | (num >> (digits - step)));
		}else if(step < 0){
			return ((num >> -step) | (num << (digits + step))); // rotate left if step is negative
		}
		return num; // step == 0, no rotation needed
	#endif
	}
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T rotl(T num, int step = 1) noexcept {
		return cutil::bit::rotate_bit_left(num, step);
	}
	
	//* rotate bit right by step, `((num >> step) | (num << (N - step)))`
	//  use std::rotr() since C++20
	//  if /O2 is enabled, this will be optimized to a single instruction on x86 and ARM
	//  also, you can use `_rotr()` `_rotr64()` in MSVC
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T rotate_bit_right(T num, int step = 1) noexcept {
	#ifdef CUTIL_CPP20_SUPPORTED
		return std::rotr(num, static_cast<int>(step)); // x86 and ARM have CPU instructions for this
	#else
		constexpr auto digits = std::numeric_limits<T>::digits;
		step = step % digits; // ensure step is within range
		if(step > 0){
			return ((num >> step) | (num << (digits - step)));
		}else if(step < 0){
			return ((num << -step) | (num >> (digits + step))); // rotate right if step is negative
		}
		return num; // step == 0, no rotation needed
	#endif
	}
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T rotr(T num, int step = 1) noexcept {
		return cutil::bit::rotate_bit_right(num, step);
	}
	
	//* insert bit to the left, then shift others to right. `(bit >> 1) | (inserted << (bitSize - 1))`
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T insert_bit_left(T num, bool inserted = true) noexcept {
		return (num >> 1) | (static_cast<T>(inserted) << (std::numeric_limits<T>::digits - 1));
	}
	
	//* insert bit to the right, then shift others to left. `(bit << 1) | inserted`
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T insert_bit_right(T num, bool inserted = true) noexcept {
		return (num << 1) | static_cast<T>(inserted);
	}
	
	//* get lsb (least significant bit, the rightmost bit)
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T get_lsb(T num) noexcept {
		return (num & 1);
	}
	
	//* get msb (most significant bit, the leftmost bit)
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T get_msb(T num) noexcept {
		return (num & (1u << (std::numeric_limits<T>::digits - 1)));
	}
	
	//* has_single_bit, check if the number is power of 2 ({1, 2, 4, 8...})
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr bool has_single_bit(T num) noexcept {
	#ifdef CUTIL_CPP20_SUPPORTED
		return std::has_single_bit(num);
	#else
		return num != 0 && (num & (num - 1)) == 0;
	#endif
	}
	// check if the number is power of 2 ({1, 2, 4, 8...})
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr bool is_power_of_2(T num) noexcept {
		return cutil::bit::has_single_bit(num);
	}
/*
	uint16_t num {0};
	// operate bit by index, starts at 0. use them in a separate line, and returns nothing
	num = cutil::bit::set_bit_by_idx(num, 1);   // equals to {num = num |  (1u << 0));}
	num = cutil::bit::clear_bit_by_idx(num, 2); // equals to {num = num & ~(1u << 2));}
	num = cutil::bit::flip_bit_by_idx(num, 3);  // equals to {num = num ^  (1u << 3));}
	num = cutil::bit::set_bit_by_idx(num, {0, 1, 3});   // initializer_list available
	num = cutil::bit::clear_bit_by_idx(num, {0, 1, 3}); // initializer_list available
	num = cutil::bit::flip_bit_by_idx(num, {0, 1, 3});  // initializer_list available
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
	
	// rotate bits. use them in a separate line, and returns nothing
	uint16_t var {0b0001'0010'0011'0100};
	var = cutil::bit::rotate_bit_left(var, 1);	-> 0b0010'0100'0110'1000
	var = cutil::bit::rotate_bit_right(var, 1);	-> 0b0001'0010'0011'0100
	var = cutil::bit::rotate_bit_left(var, 4);	-> 0b0010'0100'0110'1000
	fmt::println("var={:#016b}", var);
	
	// insert bit.
	uint16_t var2 {0b0001'0010'0011'0100};
	var2 = cutil::bit::insert_bit_left(var2, true);	  -> 0b1000'1001'0001'1010
	var2 = cutil::bit::insert_bit_right(var2, false); -> 0b0001'0010'0011'0100
	
	// get msb and lsb (leftmost and rightmost bit)
	var = cutil::bit::get_msb(0xFFFF); // get msb -> 0x8000
	var = cutil::bit::get_lsb(0xFFFF); // get lsb -> 0x0001
	
	// check if the number is power of 2 ({1, 2, 4, 8...})
	bool out = cutil::bit::has_single_bit(num));
	
*/

	//* get low byte and high byte of a word (16-bit unsigned integer)
	//  regardless of the endianness, the low byte is always the rightmost byte
	_CUTIL_NODISCARD _CUTIL_FUNC_STATIC inline constexpr
	uint8_t get_word_low(uint16_t word) {
		return (uint8_t)(word & 0xFF);
	}
	_CUTIL_NODISCARD _CUTIL_FUNC_STATIC inline constexpr
	uint8_t get_word_high(uint16_t word) {
		return (uint8_t)(word >> 8u);
	}
	_CUTIL_FUNC_STATIC inline
	void set_word_low(uint16_t& word, uint8_t val) {
		word = ((word & 0xFF00) | val);
	}
	_CUTIL_FUNC_STATIC inline
	void set_word_high(uint16_t& word, uint8_t val) {
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
/* instructions:
	float 		pi 		= cutil::numbers::pi_f;
	double 		pi 		= cutil::numbers::pi;
	long double pi_ld 	= cutil::numbers::pi_ld
	
	float 		pi 		= cutil::Numbers<float>::pi;
	double 		pi 		= cutil::Numbers<double>::pi;
	long double pi_ld 	= cutil::Numbers<long double>::pi
*/
template <typename T, _CUTIL_CONCEPT_FLOAT(T)>
struct Numbers {
	// defined as long double type.
	//* mathematical constants
	static constexpr T e 			= static_cast<T>(2.718281828459045235360287471352662498L); //*  e
	static constexpr T log2e 		= static_cast<T>(1.442695040888963407359924681001892137L); //*  log2(e)
	static constexpr T log10e 		= static_cast<T>(0.434294481903251827651128918916605082L); //*  log10(e)
	static constexpr T ln2 			= static_cast<T>(0.693147180559945309417232121458176568L); //*  ln(2)
	static constexpr T ln10 		= static_cast<T>(2.302585092994045684017991454684364208L); //*  ln(10)

	static constexpr T pi 			= static_cast<T>(3.141592653589793238462643383279502884L); //*  pi
	static constexpr T two_pi 		= static_cast<T>(6.283185307179586476925286766559005768L); //*  2 * pi
	static constexpr T three_pi 	= static_cast<T>(9.424777960769379715387930149838508653L); //*  3 * pi
	static constexpr T pi_half 		= static_cast<T>(1.570796326794896619231321691639751442L); //*  pi / 2
	static constexpr T pi_third 	= static_cast<T>(1.047197551196597746154214461093167628L); //*  pi / 3
	static constexpr T pi_quarter 	= static_cast<T>(0.7853981633974483096156608458198757210L);//*  pi / 4
	static constexpr T inv_pi 		= static_cast<T>(0.3183098861837906715377675267450287241L);//*  1 / pi
	static constexpr T inv_sqrt_pi 	= static_cast<T>(0.5641895835477562869480794515607725858L);//*  1 / sqrt(pi)
	static constexpr T two_inv_pi 	= static_cast<T>(0.6366197723675813430755350534900574481L);//*  2 / pi
	static constexpr T two_sqrt_pi 	= static_cast<T>(1.128379167095512573896158903121545172L); //*  2 / sqrt(pi)

	static constexpr T sqrt2 		= static_cast<T>(1.414213562373095048801688724209698079L); //*  sqrt(2)
	static constexpr T inv_sqrt2 	= static_cast<T>(0.7071067811865475244008443621048490393L);//*  1 / sqrt(2)
	static constexpr T sqrt3 		= static_cast<T>(1.732050807568877293527446341505872367L); //*  sqrt(3)
	static constexpr T inv_sqrt3 	= static_cast<T>(0.577350269189625764509148780501957456L); //*  1 / sqrt(3)

	static constexpr T phi 			= static_cast<T>(1.618033988749894848204586834365638118L); //*  (1 + sqrt(5)) / 2, golden ratio
	static constexpr T inv_phi 		= static_cast<T>(0.6180339887498948482045868343656381177L);//*  2 / (1 + sqrt(5)), inverted golden ratio

	static constexpr T egamma 		= static_cast<T>(0.5772156649015328606065120900824024310L);//*  Euler-Mascheroni constant
	
	//* special values of floating point types
	static constexpr T inf 			= std::numeric_limits<T>::infinity();  //* infinity
	static constexpr T neg_inf 		= -std::numeric_limits<T>::infinity(); //* minus infinity
	static constexpr T nan 			= std::numeric_limits<T>::quiet_NaN(); //* NaN (not a number)
	
	//* limits of the type T
	static constexpr T epsilon 		= std::numeric_limits<T>::epsilon(); 	//* machine epsilon, the smallest value that can be added to 1.0 to get a different value
	static constexpr T min 			= std::numeric_limits<T>::min(); 		//* minimum positive value
	static constexpr T max 			= std::numeric_limits<T>::max(); 		//* maximum value
	static constexpr T lowest 		= std::numeric_limits<T>::lowest(); 	//* lowest value, the most negative value
	static constexpr T denorm_min 	= std::numeric_limits<T>::denorm_min(); //* minimum denormalized value, the smallest positive value that can be represented as a denormalized number
	static constexpr T round_error 	= std::numeric_limits<T>::round_error();//* the maximum error due to rounding
};

inline namespace numbers { // inline
	//* alternatives for C++20 std::numbers
	//* double versions
	constexpr double e 				= cutil::Numbers<double>::e;
	constexpr double log2e 			= cutil::Numbers<double>::log2e;
	constexpr double log10e 		= cutil::Numbers<double>::log10e;
	constexpr double ln2 			= cutil::Numbers<double>::ln2;
	constexpr double ln10			= cutil::Numbers<double>::ln10;
		
	constexpr double pi 			= cutil::Numbers<double>::pi;
	constexpr double two_pi 		= cutil::Numbers<double>::two_pi;
	constexpr double three_pi 		= cutil::Numbers<double>::three_pi;
	constexpr double pi_half 		= cutil::Numbers<double>::pi_half;
	constexpr double pi_third 		= cutil::Numbers<double>::pi_third;
	constexpr double pi_quarter 	= cutil::Numbers<double>::pi_quarter;
	constexpr double inv_pi 		= cutil::Numbers<double>::inv_pi;
	constexpr double inv_sqrt_pi 	= cutil::Numbers<double>::inv_sqrt_pi;
	constexpr double two_inv_pi 	= cutil::Numbers<double>::two_inv_pi;
	constexpr double two_sqrt_pi 	= cutil::Numbers<double>::two_sqrt_pi;
	
	constexpr double sqrt2 			= cutil::Numbers<double>::sqrt2;
	constexpr double inv_sqrt2 		= cutil::Numbers<double>::inv_sqrt2;
	constexpr double sqrt3 			= cutil::Numbers<double>::sqrt3;
	constexpr double inv_sqrt3 		= cutil::Numbers<double>::inv_sqrt3;
	
	constexpr double phi 			= cutil::Numbers<double>::phi;
	constexpr double inv_phi 		= cutil::Numbers<double>::inv_phi;
		
	constexpr double egamma 		= cutil::Numbers<double>::egamma;
	
	constexpr double inf 			= cutil::Numbers<double>::inf;
	constexpr double neg_inf 		= cutil::Numbers<double>::neg_inf;
	constexpr double nan 			= cutil::Numbers<double>::nan;
	
	//* float versions
	constexpr float e_f 			= cutil::Numbers<float>::e;
	constexpr float log2e_f 		= cutil::Numbers<float>::log2e;
	constexpr float log10e_f 		= cutil::Numbers<float>::log10e;
	constexpr float ln2_f 			= cutil::Numbers<float>::ln2;
	constexpr float ln10_f 			= cutil::Numbers<float>::ln10;
	
	constexpr float pi_f 			= cutil::Numbers<float>::pi;
	constexpr float two_pi_f 		= cutil::Numbers<float>::two_pi;
	constexpr float three_pi_f 		= cutil::Numbers<float>::three_pi;
	constexpr float pi_half_f 		= cutil::Numbers<float>::pi_half;
	constexpr float pi_third_f 		= cutil::Numbers<float>::pi_third;
	constexpr float pi_quarter_f 	= cutil::Numbers<float>::pi_quarter;
	constexpr float inv_pi_f 		= cutil::Numbers<float>::inv_pi;
	constexpr float inv_sqrt_pi_f 	= cutil::Numbers<float>::inv_sqrt_pi;
	constexpr float two_inv_pi_f 	= cutil::Numbers<float>::two_inv_pi;
	constexpr float two_sqrt_pi_f 	= cutil::Numbers<float>::two_sqrt_pi;
	
	constexpr float sqrt2_f 		= cutil::Numbers<float>::sqrt2;
	constexpr float inv_sqrt2_f 	= cutil::Numbers<float>::inv_sqrt2;
	constexpr float sqrt3_f 		= cutil::Numbers<float>::sqrt3;
	constexpr float inv_sqrt3_f 	= cutil::Numbers<float>::inv_sqrt3;
	
	constexpr float phi_f 			= cutil::Numbers<float>::phi;
	constexpr float inv_phi_f 		= cutil::Numbers<float>::inv_phi;
		
	constexpr float egamma_f 		= cutil::Numbers<float>::egamma;
	
	constexpr float inf_f 			= cutil::Numbers<float>::inf;
	constexpr float neg_inf_f 		= cutil::Numbers<float>::neg_inf;
	constexpr float nan_f 			= cutil::Numbers<float>::nan;
	
	//* long double versions
	constexpr long double e_ld 				= cutil::Numbers<long double>::e;
	constexpr long double log2e_ld 			= cutil::Numbers<long double>::log2e;
	constexpr long double log10e_ld 		= cutil::Numbers<long double>::log10e;
	constexpr long double ln2_ld 			= cutil::Numbers<long double>::ln2;
	constexpr long double ln10_ld 			= cutil::Numbers<long double>::ln10;
	
	constexpr long double pi_ld 			= cutil::Numbers<long double>::pi;
	constexpr long double two_pi_ld 		= cutil::Numbers<long double>::two_pi;
	constexpr long double three_pi_ld 		= cutil::Numbers<long double>::three_pi;
	constexpr long double pi_half_ld 		= cutil::Numbers<long double>::pi_half;
	constexpr long double pi_third_ld 		= cutil::Numbers<long double>::pi_third;
	constexpr long double pi_quarter_ld 	= cutil::Numbers<long double>::pi_quarter;
	constexpr long double inv_pi_ld 		= cutil::Numbers<long double>::inv_pi;
	constexpr long double inv_sqrt_pi_ld 	= cutil::Numbers<long double>::inv_sqrt_pi;
	constexpr long double two_inv_pi_ld 	= cutil::Numbers<long double>::two_inv_pi;
	constexpr long double two_sqrt_pi_ld 	= cutil::Numbers<long double>::two_sqrt_pi;
	
	constexpr long double sqrt2_ld 			= cutil::Numbers<long double>::sqrt2;
	constexpr long double inv_sqrt2_ld 		= cutil::Numbers<long double>::inv_sqrt2;
	constexpr long double sqrt3_ld 			= cutil::Numbers<long double>::sqrt3;
	constexpr long double inv_sqrt3_ld 		= cutil::Numbers<long double>::inv_sqrt3;
	
	constexpr long double phi_ld 			= cutil::Numbers<long double>::phi;
	constexpr long double inv_phi_ld 		= cutil::Numbers<long double>::inv_phi;
	
	constexpr long double egamma_ld 		= cutil::Numbers<long double>::egamma;
	
	constexpr long double inf_ld 			= cutil::Numbers<long double>::inf;
	constexpr long double neg_inf_ld 		= cutil::Numbers<long double>::neg_inf;
	constexpr long double nan_ld 			= cutil::Numbers<long double>::nan;
}




//======================= Numeric and Math Operations =========================
inline namespace math { // inline
	//* limit the numeric variable to the range [_MIN, _MAX], same as `std::clamp(var, min, max)` in C++17
	//  by default, comp == std::less<T>()
	template<typename T> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T clamp(T var, T min, T max) noexcept {
	#ifdef CUTIL_CPP17_SUPPORTED
		return std::clamp(var, min, max);
	#else
		assert((min < max) && "`min` should be less than `max`");
		return std::min(std::max(var, min), max);
	#endif
	}
	template<typename T, typename Comp
		, typename std::enable_if_t<cutil::internal::is_invocable_r<bool, Comp, T, T>::value, bool> = true> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T clamp(T var, T min, T max, Comp comp) noexcept {
	#ifdef CUTIL_CPP17_SUPPORTED
		return std::clamp(var, min, max, comp);
	#else
		assert((comp(min, max)) && "`min` should be less than `max`");
		return std::min(std::max(var, min, comp), max, comp);
	#endif
	}
	
	//* limit the numeric variable to the range [_MIN, _MAX], same as `var = std::clamp(var, min, max)` in C++17
	//  by default, comp == std::less<T>()
	template<typename T, typename R = T, _CUTIL_CONCEPT_CONVERTIBLE(R, T)> _CUTIL_FUNC_STATIC
	inline void limit(T& var, R min, R max) noexcept {
		var = cutil::math::clamp(var, static_cast<T>(min), static_cast<T>(max));
	}
	template<typename T, typename Comp, typename R = T, _CUTIL_CONCEPT_CONVERTIBLE(R, T)
		, typename std::enable_if_t<cutil::internal::is_invocable_r<bool, Comp, T, T>::value, bool> = true> _CUTIL_FUNC_STATIC
	inline void limit(T& var, R min, R max, Comp comp) noexcept {
		var = cutil::math::clamp(var, static_cast<T>(min), static_cast<T>(max), comp);
	}
	
	//* get if a numeric variable is within the interval [_MIN, _MAX]
	template<typename T, typename R = T, _CUTIL_CONCEPT_ARITHMETIC_CONVERTIBLE(R, T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr bool num_in_interval(T var, R min, R max) noexcept {
		assert((min < max) && "`min` should be less than `max`");
		return (var >= min) && (var <= max);
	}
	//* get if a numeric variable is within the interval (_MIN, _MAX)
	template<typename T, typename R = T, _CUTIL_CONCEPT_ARITHMETIC_CONVERTIBLE(R, T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr bool num_in_open_interval(T var, R min, R max) noexcept {
		assert((min < max) && "`min` should be less than `max`");
		return (var > min) && (var < max);
	}
	
#ifdef CUTIL_CPP17_SUPPORTED //* >= C++17
	//* Comparison function to check if a value is within a specified interval
	template <bool LeftClosed, bool RightClosed, typename T, typename R = T
			, _CUTIL_CONCEPT_ARITHMETIC_CONVERTIBLE(R, T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr bool num_in_interval(T var, R min, R max) noexcept {
		assert((min < max) && "`min` should be less than `max`");
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
	d = cutil::math::clamp(d, 20, 30); 	// C++14, equivalent to above
	d = cutil::math::clamp(d, 20, 30, std::less<int>()); // equivalent to above
	cutil::limit(d, 20, 30);			// d: 30, equivalent to `d = cutil::clamp(d, 20, 30);`
	cutil::limit(d, 20, 30, std::less<int>());	// equivalent to above
	fmt::println("{} {} {}", a, b, c); // output: 30 26 20
	

	bool ret = cutil::math::num_in_interval(a, 20, 40);				  // whether a is in [20, 40]
	bool ret = cutil::math::num_in_open_interval(c, 20, 30);		  // whether c is in (20, 30)
	bool ret = cutil::math::num_in_interval<true, true>(a, 20, 40);	  // whether a is in [20, 40], C++17
	bool ret = cutil::math::num_in_interval<true, false>(a, 20, 40);  // whether a is in [20, 40), C++17
	bool ret = cutil::math::num_in_interval<false, false>(a, 20, 40); // whether a is in [20, 40], C++17
*/


	//* increase the value of variable, but if the result exceeds the limit(>=), it will not be increased
	//  if exceeded, returns true.
	template<typename T, typename L = T, _CUTIL_CONCEPT_ARITHMETIC_CONVERTIBLE(L, T)> _CUTIL_FUNC_STATIC
	inline bool increase_under_limit(T& var, L max, int inc = 1) noexcept {
		assert(var <= max);
		if((var + static_cast<T>(inc)) <= static_cast<T>(max)) {
			var += static_cast<T>(inc);
			return false;
		}
		return true;
	}
	// increase the value of variable, but if the result exceeds the limit(>=), it will be clamped to the limit
	// if clamped, returns true.
	template<typename T, typename L = T, _CUTIL_CONCEPT_ARITHMETIC_CONVERTIBLE(L, T)> _CUTIL_FUNC_STATIC
	inline bool increase_under_limit_clamp(T& var, L max, int inc = 1) noexcept {
		if(cutil::math::increase_under_limit(var, max, inc)) {
			var = static_cast<T>(max);
			return true;
		}
		return false;
	}
	
	//* decrease the value of variable, but if the result is less than the limit(<=), it will not be decreased
	//  if exceeded, returns true.
	template<typename T, typename L = T, _CUTIL_CONCEPT_ARITHMETIC_CONVERTIBLE(L, T)> _CUTIL_FUNC_STATIC
	inline bool decrease_above_limit(T& var, L min, int dec = 1) noexcept {
		assert(var >= min);
		if((var - static_cast<T>(dec)) >= static_cast<T>(min)){
			var -= static_cast<T>(dec);
			return false;
		}
		return true;
	}
	// decrease the value of variable, but if the result is less than the limit(<=), it will be clamped to the limit
	// if clamped, returns true.
	template<typename T, typename L = T, _CUTIL_CONCEPT_ARITHMETIC_CONVERTIBLE(L, T)> _CUTIL_FUNC_STATIC
	inline bool decrease_above_limit_clamp(T& var, L min, int dec = 1) noexcept {
		if(cutil::math::decrease_above_limit(var, min, dec)){
			var = static_cast<T>(min);
			return true;
		}
		return false;
	}
	
	//* increase the value of variable, and rolling within the range [_MIN, _MAX]
	//  if rolled, returns true.
	template<typename T, typename R = T, _CUTIL_CONCEPT_ARITHMETIC_CONVERTIBLE(R, T)> _CUTIL_FUNC_STATIC
	inline bool increase_rolling(T& var, R min, R max, int inc = 1) noexcept {
		assert(min < max && cutil::num_in_interval(var, min, max));
		if((var + static_cast<T>(inc)) <= max){
			var += static_cast<T>(inc);
			return false;
		}
		var = static_cast<T>(min);
		return true;
	}
	
	//* decrease the value of variable, and rolling within the range [_MIN, _MAX]
	//  if rolled, returns true.
	template<typename T, typename R = T, _CUTIL_CONCEPT_ARITHMETIC_CONVERTIBLE(R, T)> _CUTIL_FUNC_STATIC
	inline bool decrease_rolling(T& var, R min, R max, int dec = 1) noexcept {
		assert(min < max && cutil::num_in_interval(var, min, max));
		if((var - static_cast<T>(dec)) >= min){
			var -= static_cast<T>(dec);
			return false;
		}
		var = max;
		return true;
	}
	
	//* increase the value of variable, and prevent overflowing,
	// if it is near to be overflowed, it will not increased any more and return true.
	template<typename T, _CUTIL_CONCEPT_ARITHMETIC(T)> _CUTIL_FUNC_STATIC
	inline bool increase_no_overflow(T& var, int inc = 1) noexcept {
		assert(inc > 0);
		return (static_cast<T>(var + inc) > var) ? (var += inc, false) : (true);
	}
	//* decrease the value of variable, and prevent underflowing,
	// if it is near to be underflowed, it will not decreased any more and return true.
	template<typename T, _CUTIL_CONCEPT_ARITHMETIC(T)> _CUTIL_FUNC_STATIC
	inline bool decrease_no_underflow(T& var, int dec = 1) noexcept {
		assert(dec > 0);
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
	bool isOverflowed2 = cutil::math::increase_no_overflow(num);    // equivalent
	num = -125;
	bool isOverflowed3 = cutil::math::decrease_no_underflow(num, 1); // prevent underflowing, -126 -127 -128 -128 -128 -128, returns true if near to overflow
	bool isOverflowed4 = cutil::math::decrease_no_underflow(num);    // equivalent

*/

	//* constexpr abs() of an number, overloaded for unsigned integer types
	template<typename T, _CUTIL_CONCEPT_SIGNED_OR_FLOAT(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T abs(T num) noexcept { // for signed intergers and `float`, `double`, `long double`
	#ifdef CUTIL_CPP20_SUPPORTED
		if (!std::is_constant_evaluated()){
			return std::abs(num); // not constexpr
		}
	#endif // C++20
		return (num < 0) ? -num : num; // in C++14/17/20, std::abs() is not constexpr
	}
	template<typename U, _CUTIL_CONCEPT_UNSIGNED(U)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline U constexpr abs(U num) noexcept { // for `uint8_t`, `uint16_t`, `uint32_t`, `uint64_t`, `size_t`
		return num;
	}
	
	//* constexpr isInf()
	// there are CPU instructions to check for infinity, but they are not portable
	template<typename F, _CUTIL_CONCEPT_FLOAT(F)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr bool isinf(F num) noexcept {
	#ifdef CUTIL_CPP20_SUPPORTED
		if (!std::is_constant_evaluated()){
			return std::isinf(num); // not constexpr
		}
	#endif // C++20
		return (num == std::numeric_limits<F>::infinity() || num == -std::numeric_limits<F>::infinity());
	}
	template<typename I, _CUTIL_CONCEPT_INTEGRAL(I)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr bool isinf(I) noexcept {
		return false;
	}
	
	//* constexpr isNaN()
	// there are CPU instructions to check for NaN, but they are not portable
	template<typename F, _CUTIL_CONCEPT_FLOAT(F)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr bool isnan(F num) noexcept {
	#ifdef CUTIL_CPP20_SUPPORTED
		if (!std::is_constant_evaluated()){
			return std::isnan(num); // not constexpr
		}
	#endif // C++20
		return (num != num); // NaN is not equal to anything, including itself
	}
	template<typename I, _CUTIL_CONCEPT_INTEGRAL(I)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr bool isnan(I num) noexcept {
		return false;
	}
	
	//* get gcd (greatest common divisor)
	template<typename I, _CUTIL_CONCEPT_INTEGRAL(I)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr I gcd(I a, I b) noexcept {
	#ifdef CUTIL_CPP17_SUPPORTED
		return std::gcd(a, b);
	#else
		if(b == 0){
			return cutil::math::abs(a);
		}
		if(a == 0){
			return cutil::math::abs(b);
		}
		return cutil::math::gcd(b, a % b);
	#endif
	}
	
	//* get lcm (least common multiple)
	template<typename I, _CUTIL_CONCEPT_INTEGRAL(I)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr I lcm(I a, I b) noexcept {
	#ifdef CUTIL_CPP17_SUPPORTED
		return std::lcm(a, b);
	#else
		if(a == 0 || b == 0) {
			return 0;
		}
		return cutil::math::abs(a * b / cutil::math::gcd(a, b));
	#endif
	}
	
	//* get midpoint of two integer or floating point numbers
	// if a and b are integers, the result is also truncated to an integer
	// eg. midpoint(6, 9) -> 7.
	template<typename I, _CUTIL_CONCEPT_INTEGRAL(I)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr I midpoint(I a, I b) noexcept {
	#ifdef CUTIL_CPP20_SUPPORTED
		return std::midpoint(a, b);
	#else
		using uint_t = std::make_unsigned_t<I>;
		int k = 1;
		if(a < b) {
			return a + static_cast<I>(static_cast<uint_t>(b - a) / 2);
		}else{
			return b - static_cast<I>(static_cast<uint_t>(a - b) / 2);
		}
	#endif
	}
	template<typename F, _CUTIL_CONCEPT_FLOAT(F)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr F midpoint(F a, F b) noexcept {
	#ifdef CUTIL_CPP20_SUPPORTED
		return std::midpoint(a, b);
	#else
		constexpr auto max = std::numeric_limits<F>::max() / 2;
		constexpr auto min = std::numeric_limits<F>::min() * 2;
		if(cutil::math::isnan(a) || cutil::math::isnan(b)) {
			return std::numeric_limits<F>::quiet_NaN(); // NaN, return NaN
		}else if(cutil::math::abs(a) < max && cutil::math::abs(b) < max) { // normal case
			return ((a + b) / 2);
		}else if(cutil::math::abs(a) < min){ // a < min and b >= max
			return (a + (b / 2));
		}else if(cutil::math::abs(b) < min){ // b < min and a >= max
			return ((a / 2) + b);
		}else{ // a, b >= max
			return ((a / 2) + (b / 2));
		}
	#endif
	}
	//* get midpoint of two pointers
	template<typename T> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T* midpoint(T* a, T* b) noexcept { // for pointers
	#ifdef CUTIL_CPP20_SUPPORTED
		return std::midpoint(a, b);
	#else
		return (a + (b - a) / 2);
	#endif
	}
	

} // namespace math

namespace internal{
	template<typename T>
	struct float_to_int;
	template<>
	struct float_to_int<float> {
		using type = int32_t;
	};
	template<>
	struct float_to_int<double> {
		using type = int64_t;
	};

	template<typename T, _CUTIL_CONCEPT_FLOAT_WITHOUT_LONGDOUBLE(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC _CUTIL_CONSTEXPR_CPP20
	inline bool fequal_ulp_impl(T a, T b, int maxUlpDiff = 4) noexcept {
		using intType_t = typename cutil::internal::float_to_int<std::remove_cv_t<T>>::type;
		if(cutil::math::isnan(a) || cutil::math::isnan(b)) {
			return false; // NaN is not equal to anything, including itself
		}
		if(cutil::math::isinf(a) || cutil::math::isinf(b)) {
			return (a == b); // +inf == +inf, -inf == -inf, but +inf != -inf, inf != non-inf
		}
		const size_t size = sizeof(intType_t);
		intType_t intA;
		intType_t intB;
	#ifdef CUTIL_CPP20_SUPPORTED
		intA = std::bit_cast<intType_t>(a);
		intB = std::bit_cast<intType_t>(b);
	#else // C++14/17, not constexpr
		memcpy(&intA, &a, size);
		memcpy(&intB, &b, size);
		// intA = *reinterpret_cast<volatile intType_t*>(&intA); // UB
		// intB = *reinterpret_cast<volatile intType_t*>(&intB); // UB
	#endif
		if((intA < 0) != (intB < 0)) {
			return (intA == intB); // one is negative, the other is positive
		}
		intType_t diff = cutil::math::abs(intA - intB);
		return (diff <= maxUlpDiff); // check if the difference is within the allowed ULP (Units in the Last Place)
	}
	
	template<typename T, _CUTIL_CONCEPT_FLOAT(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr bool fequal_eps_impl(T a, T b, T epsilon = std::numeric_limits<T>::epsilon()) noexcept {
		if(cutil::math::isnan(a) || cutil::math::isnan(b)) {
			return false; // NaN is not equal to anything, including itself
		}
		if(cutil::math::isinf(a) || cutil::math::isinf(b)) {
			return (a == b); // +inf == +inf, -inf == -inf, but +inf != -inf, inf != non-inf
		}
		return (cutil::math::abs(a - b) <= cutil::math::abs(epsilon)); // overloaded abs() for floating number in <cstdlib>
	}
	
	template<typename T, _CUTIL_CONCEPT_FLOAT(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T lerp_impl(T a, T b, T t) noexcept {
	#ifdef CUTIL_CPP20_SUPPORTED
		return std::lerp((a), (b), t);
	#else
		constexpr T one = static_cast<T>(1);
		constexpr T zero = static_cast<T>(0);
		if(cutil::math::isnan(a) || cutil::math::isnan(b) || cutil::math::isnan(t)) {
			return std::numeric_limits<T>::quiet_NaN(); // NaN, return NaN
		}else if((a <= zero && b >= zero) || (a >= zero && b <= zero)){
			return ((t * b) + ((one - t) * a));
		}else if(t == one){
			return b;
		}
		const T x = (a + (t * (b - a))); // calculate interpolation value
		if((t > one) == (b > a)){
			return std::max(b, x); // if t > 1, return b if x > b, else return x
		}else{
			return std::min(b, x); // if t < 1, return b if x < b, else return x
		}
	#endif
	}
	
	template <typename T, typename R = T, _CUTIL_CONCEPT_ARITHMETIC(T), _CUTIL_CONCEPT_ARITHMETIC(R)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr R pow_impl(const T base, const size_t exp) noexcept { // `base` should != 0
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
		int tmp = cutil::internal::pow_impl(base, exp/2);
		if (exp % 2 == 0){
			return static_cast<R>(tmp * tmp);
		}else{
			return static_cast<R>(base * tmp * tmp);
		}
	}
	
#ifdef CUTIL_CPP17_SUPPORTED
	template <const size_t exp, typename T, typename R = T, _CUTIL_CONCEPT_ARITHMETIC(T), _CUTIL_CONCEPT_ARITHMETIC(R)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr R pow_impl(const T base) noexcept { // `base` should != 0
		if constexpr (exp == 0) {
			return static_cast<R>(1);
		}else if constexpr (exp == 1) {
			return static_cast<R>(base);
		}else if constexpr (exp == 2) {
			return static_cast<R>(base * base);
		}else if constexpr (exp == 3) {
			return static_cast<R>(base * base * base);
		}
		R tmp = cutil::internal::pow_impl<exp / 2, T, R>(base);
		if (exp % 2 == 0){
			return static_cast<R>(tmp * tmp);
		}else{
			return static_cast<R>(base * tmp * tmp);
		}
	}
#endif // C++17

} // namespace internal

inline namespace math { // inline
	//* power function with unsigned integer exponent
	//  int ret = cutil::pow(2, 3); // 2^3 = 8
	//  size_t ret = cutil::pow<int, size_t>(2, 3); // return as size_t
	//  int ret = cutil::pow<3>(2); // 2^3 = 8, >=C++17
	//  from https://stackoverflow.com/questions/1505675/power-of-an-integer-in-c
	//  specially, pow(3, 0) == 1, pow(0, 0) == 1, pow(0, 3) == 0
	template <typename T, typename R = T, _CUTIL_CONCEPT_ARITHMETIC(T), _CUTIL_CONCEPT_ARITHMETIC(R)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr R pow(const T base, const size_t exp) noexcept {
		if(base == static_cast<T>(0)) {
			if(exp > 0){
				return static_cast<R>(0); // 0^exp = 0 for exp > 0
			}else{ // exp == 0, 0^0 is usually defined as 1
				return static_cast<R>(1); // 0^0 is usually defined as 1
			}
		}
		return cutil::internal::pow_impl<T, R>(base, exp); // call the implementation
	}
	
	//* factorial function
	//  int ret = cutil::factorial(3); // 3! = 6
	//  size_t ret = cutil::factorial<int, size_t>(3); // return as size_t
	template <typename T, typename R = T, _CUTIL_CONCEPT_INTEGRAL(T), _CUTIL_CONCEPT_INTEGRAL(R)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr R factorial(const T base) noexcept {
		assert(cutil::math::num_in_interval(base, 0, 40) && "`base` should be in [0, 40]");
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
	//* power function with unsigned integer exponent (C++17)
	//  int ret = cutil::pow<3>(2); // 2^3 = 8, >=C++17
	//  size_t ret = cutil::pow<3, int, size_t>(2); // return as size_t
	//  from https://stackoverflow.com/questions/1505675/power-of-an-integer-in-c
	//  specially, pow<0>(3) == 1, pow<0>(0) == 1, pow<3>(0) == 0
	template <const size_t exp, typename T, typename R = T, _CUTIL_CONCEPT_ARITHMETIC(T), _CUTIL_CONCEPT_ARITHMETIC(R)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr R pow(const T base) noexcept {
		if(base == 0){
			if constexpr (exp > 0) {
				return static_cast<R>(0); // 0^exp = 0 for exp > 0
			}else{ // exp == 0
				return static_cast<R>(1); // 0^0 is usually defined as 1
			}
		}
		return cutil::internal::pow_impl<exp, T, R>(base); // call the implementation
	}
	
	//* factorial function (C++17)
	//  int ret = cutil::factorial<3>(); // 3! = 6
	//  size_t ret = cutil::factorial<3, size_t>(); // return as size_t
	template <const size_t base, typename R = size_t, _CUTIL_CONCEPT_INTEGRAL(R)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr R factorial() noexcept {
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
	
#else // C++14
	template <const size_t exp, typename T, typename R = T> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr R pow(const T base) noexcept {
		return cutil::math::pow(base, exp);
	}
	
	template <const size_t base, typename R = size_t> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr R factorial() noexcept {
		return cutil::math::factorial<R>(base);
	}
#endif // C++17
	
	//* Compares two floating-point numbers for equality within a specified epsilon.
	_CUTIL_NODISCARD _CUTIL_FUNC_STATIC inline constexpr
	bool fequal_eps(float a, float b, float epsilon = std::numeric_limits<float>::epsilon()) noexcept {
		return cutil::internal::fequal_eps_impl(a, b, epsilon);
	}
	_CUTIL_NODISCARD _CUTIL_FUNC_STATIC inline constexpr
	bool fequal_eps(double a, double b, double epsilon = std::numeric_limits<double>::epsilon()) noexcept {
		return cutil::internal::fequal_eps_impl(a, b, epsilon);
	}
	_CUTIL_NODISCARD _CUTIL_FUNC_STATIC inline constexpr
	bool fequal_eps(long double a, long double b, long double epsilon = std::numeric_limits<long double>::epsilon()) noexcept {
		return cutil::internal::fequal_eps_impl(a, b, epsilon);
	}
	//* Compares two floating-point numbers for equality within a specified ULP (Units in the Last Place).
	//  not constexpr in C++14/17, but constexpr in C++20
	_CUTIL_NODISCARD _CUTIL_FUNC_STATIC inline _CUTIL_CONSTEXPR_CPP20
	bool fequal_ulp(float a, float b, int maxUlpDiff = 4) {
		return cutil::internal::fequal_ulp_impl(a, b, maxUlpDiff);
	}
	_CUTIL_NODISCARD _CUTIL_FUNC_STATIC inline _CUTIL_CONSTEXPR_CPP20
	bool fequal_ulp(double a, double b, int maxUlpDiff = 4) {
		return cutil::internal::fequal_ulp_impl(a, b, maxUlpDiff);
	}
/*
	bool isEqual4 = cutil::math::fequal_eps(a, b); // (abs(a - b) <= std::numeric_limits<decltype(a)>::epsilon())
	bool isEqual5 = cutil::math::fequal_eps(c, d, 0.0001); // equivalent
	
	bool isEqual6 = cutil::math::fequal_ulp(a, b); // (abs(a - b) <= 4 ULP)
	bool isEqual7 = cutil::math::fequal_ulp(c, d, 2); // equivalent, 2 ULP
*/

	
	//* linear interpolation, (a + (b - a) * t)
	//  t should be in the range [0, 1]. if t = 0, returns a; if t == 1, returns b.
	//
	//  use std::lerp() since C++20
	_CUTIL_NODISCARD _CUTIL_FUNC_STATIC inline constexpr
	float lerp(float a, float b, float t) noexcept {
		return cutil::internal::lerp_impl(a, b, t);
	}
	_CUTIL_NODISCARD _CUTIL_FUNC_STATIC inline constexpr
	double lerp(double a, double b, double t) noexcept {
		return cutil::internal::lerp_impl(a, b, t);
	}
	_CUTIL_NODISCARD _CUTIL_FUNC_STATIC inline constexpr
	long double lerp(long double a, long double b, long double t) noexcept {
		return cutil::internal::lerp_impl(a, b, t);
	}
	

	//* convert degrees to radians, (degree * M_PI / 180.0)
	// `cutil::fequal_eps(cutil::numbers::pi_3, cutil::math::deg2rad(60.0)) == true`
	template<typename F, _CUTIL_CONCEPT_FLOAT(F)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr F deg2rad(F degree) noexcept {
		// if(cutil::math::isnan(degree) || cutil::math::isinf(degree)) {
		// 	return degree; // NaN or inf, return as is
		// }
		return (degree * cutil::Numbers<F>::pi / static_cast<F>(180.0));
	}
	
	//* convert radians to degrees, (radian * 180.0 / M_PI)
	// `cutil::fequal_eps(60.0, cutil::math::rad2deg(cutil::numbers::pi_3)) == true`
	template<typename F, _CUTIL_CONCEPT_FLOAT(F)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr F rad2deg(F radian) noexcept {
		// if(cutil::math::isnan(radian) || cutil::math::isinf(radian)) {
		// 	return radian; // NaN or inf, return as is
		// }
		return (radian * static_cast<F>(180.0) / cutil::Numbers<F>::pi);
	}
	
	
} // namespace math




//======================= Type Conversions =========================
inline namespace type {
	//* cast bitwise, `(reinterpret_cast<volatile Out*>(&in))`
	// is not constexpr in C++14/17, but constexpr in C++20
	template<typename Out, typename In> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC _CUTIL_CONSTEXPR_CPP20
	inline Out bit_cast(In&& in) noexcept {
		static_assert(sizeof(Out) == sizeof(In), "Out and In must have same size");
	#ifdef CUTIL_CPP20_SUPPORTED
		return std::bit_cast<Out>(in);
	#else
		// return *reinterpret_cast<volatile Out*>(&in); // UB, but works in practice
		Out out;
		memcpy(&out, &in, sizeof(Out)); // copy memory
		return out; // return the casted value
	#endif
	}
	
	//* assign bitwise, `(memcpy(&out, &in, sizeof(T)))`
	template<typename Out, typename In> _CUTIL_FUNC_STATIC
	inline void bitwise_memcpy(Out& out, In&& in) {
		// static_assert(std::is_trivially_copyable_v<Out>, "Out and In must be a trivially copyable type");
		// static_assert(std::is_trivially_copyable_v<std::decay_t<In>>, "In must be a trivially copyable type");
		static_assert(sizeof(Out) == sizeof(In), "Out and In must have same size");
		memcpy(&out, &in, sizeof(Out));
	}
/*
	cutil::bitwise_memcpy(f, i) 				// i -> f, bitwise memcpy
	f = bit_cast<float>(i);   					// equivalent
	f = *reinterpret_cast<volatile float*>(&i); // equivalent
	std::memcpy(&f, &i, sizeof(f)); 			// equivalent
	f = std::bit_cast<float>(i) 				// C++20
*/
	
	
	//* do `dynamic_cast` in DEBUG, assert if failed; do `static_cast` in RELEASE
	//   `PDerived` points to the derived class, `PBase` points to the base class
	//   `PBase` and  `PDerived` should be both pointers point to different types, with same `const` or `volatile` attributes.
	template<typename PDerived, typename PBase
			, _CUTIL_CONCEPT_POINTER_SAME_ATTRIBUTES(PDerived, PBase)
			, _CUTIL_CONCEPT_POINTER_DIFFERENT_TYPES(PDerived, PBase)
			, _CUTIL_CONCEPT_POINTER_IS_BASE_OF(PBase, PDerived)
		> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr PDerived safe_cast(PBase in) {
	#ifdef CUTIL_DEBUG_BUILD
		PDerived out = dynamic_cast<PDerived>(in);
		assert(out != nullptr && "dynamic cast failed");
		return out;
	#else //release
		return static_cast<PDerived>(in);
	#endif
	}
/*
	struct Base { virtual ~A(){} };
	struct A : Base {};
	struct B : Base {};
	
	std::unique_ptr<Base> pa = std::make_unique<A>();
	A* pa1 = cutil::safe_cast<A*>(pa.get()); // do dynamic_cast in debug, assert if failed; do static_cast in release
	const A* pa2 = cutil::safe_cast<const A*>(const_cast<const Base*>(pa.get())); // convert const pointer to const pointer, OK
	// const A* pa3 = cutil::safe_cast<const A*>(pa.get()); // ERROR
	// A* pa4 = cutil::safe_cast<A*>(const_cast<Base*>(pa.get())); // ERROR
*/
	
	
} // namespace type




//======================= Memory Operations =========================
inline namespace memory {
	
	//* get midpoint of two pointers
	template<typename P> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr P* midpoint(P* a, P* b) noexcept {
		return cutil::math::midpoint(a, b);
	}
	
	//* get offset of two pointers in bytes
	template <typename T, typename U> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline ptrdiff_t get_ptr_offset(T* higher, U* lower){
		return reinterpret_cast<uintptr_t>(higher) - reinterpret_cast<uintptr_t>(lower);
	}
	
	// get offset of the struct member to the struct base address
	template <typename U, typename T> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
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
	template<typename T, typename P, _CUTIL_CONCEPT_POINTER(P)> _CUTIL_NODISCARD [[deprecated]] _CUTIL_MAYBE_UNUSED _CUTIL_FUNC_STATIC
	inline T& read_memory(P ptr) {
		return *reinterpret_cast<T*>(ptr); // add volatile might cause error
	}
	
	// (UB) set memory at the specific location in the specific type
	template<typename T, typename P, _CUTIL_CONCEPT_POINTER(P)> [[deprecated]] _CUTIL_MAYBE_UNUSED _CUTIL_FUNC_STATIC
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
	template<typename T> _CUTIL_MAYBE_UNUSED _CUTIL_FUNC_STATIC
	inline T* memcpy_type(T* out, const T* in, size_t amount = 1) {
		return memcpy(out, in, sizeof(T) * amount);
	}
	template<typename T> _CUTIL_MAYBE_UNUSED _CUTIL_FUNC_STATIC
	inline T* memmove_type(T* out, const T* in, size_t amount = 1) {
		return memmove(out, in, sizeof(T) * amount);
	}
	template<typename T> _CUTIL_MAYBE_UNUSED _CUTIL_FUNC_STATIC
	inline T* memset_type(T& out, int value, size_t amount = 1) {
		return memset(&out, value, sizeof(T) * amount);
	}
	template<typename T> _CUTIL_MAYBE_UNUSED _CUTIL_FUNC_STATIC
	inline int memcmp_type(const T* ptr1, const T* ptr2, size_t amount = 1) {
		return memcmp(ptr1, ptr2, sizeof(T) * amount);
	}
	template<typename T> _CUTIL_MAYBE_UNUSED _CUTIL_FUNC_STATIC
	inline T* malloc_type(size_t amount = 1) {
		return static_cast<T*>(std::malloc(sizeof(T) * amount));
	}
	template <typename T> _CUTIL_MAYBE_UNUSED _CUTIL_FUNC_STATIC
	inline T* calloc_type(size_t amount = 1) {
		return static_cast<T*>(std::calloc(amount, sizeof(T)));
	}
	template<typename T> _CUTIL_MAYBE_UNUSED _CUTIL_FUNC_STATIC
	inline T* realloc_type(T* ptr, size_t amount = 1) {
		return static_cast<T*>(std::realloc(ptr, sizeof(T) * amount));
	}
	
	//* delete heap pointer and set it to nullptr
	template<typename T> _CUTIL_FUNC_STATIC
	inline void free_ptr(T*& ptr) {
		if(ptr != nullptr){
			std::free(ptr);
			ptr = nullptr;
		}
	}
	template<typename T> _CUTIL_FUNC_STATIC
	inline void delete_ptr(T*& p) {
		if(p != nullptr){
			delete p;
			p = nullptr;
		}
	}
	template<typename T> _CUTIL_FUNC_STATIC
	inline void delete_array(T*& p) {
		if(p != nullptr){
			delete[] p;
			p = nullptr;
		}
	}

	
} // namespace





//==================== C++ Class Utilities ========================

//* set class constructor/moving/copying to disabled/default
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



//* generate getter and setter
// generate getter and setter with specific type (not recommended, and do not add `const` to the first parameter)
#define CUTIL_GETTER_TYPE(_type, _name, _getter) 	public: _type _getter() {return this->_name;}
#define CUTIL_SETTER_TYPE(_type, _name, _setter) 	public: void _setter(const _type& _val)	{this->_name = _val;}
#define CUTIL_MEMBER_TYPE(_type, _name, ...)		CUTIL_EXPAND(CUTIL_OVERLOAD_IDX(_CUTIL_MEMBER_TYPE_, CUTIL_VA_CNT(__VA_ARGS__))(_type, _name, __VA_ARGS__))
#define _CUTIL_MEMBER_TYPE_2(_type, _name, _getter, _setter)	CUTIL_GETTER_TYPE(_type, _name, _getter) CUTIL_SETTER_TYPE(_type, _name, _setter)
#define _CUTIL_MEMBER_TYPE_1(_type, _name, _func)				_CUTIL_MEMBER_TYPE_2(_type, _name, _func, _func)

// generate getter and setter with type deducing (uses `std::decay_t<decltype(_name)>`)
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
