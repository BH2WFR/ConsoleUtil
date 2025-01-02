 /**
 ******************************************************************************
 *
 *  @mainpage strutil v1.1.0 - header-only string utility library documentation
 *  @see https://github.com/Shot511/strutil
 *
 *  @copyright  Copyright (C) 2024 Tomasz Galaj
 *  @file       strutil.h
 *  @brief      Library public interface header
 *
 *  @subsection Thank you all for your contributions!!
 *
 ******************************************************************************
 */
#ifndef CONSOLEUTIL_EXTERNAL_STRING_UTIL_H__
#define CONSOLEUTIL_EXTERNAL_STRING_UTIL_H__
#include <ConsoleUtil/Base.h>

#if defined(__cplusplus) && defined(CUTIL_CPP11_SUPPORTED)
#include <cstdint>
#include <algorithm>
#include <cctype>
#include <execution>
#include <map>
#include <regex>
#include <set>
#include <sstream>
#include <string>
#include <vector>


_CUTIL_NAMESPACE_BEGIN
namespace str
{
	namespace internal{
		template<typename T, typename Compare>
		inline void sort(std::vector<T>& vec, Compare comp = std::less<T>()) {
		#ifdef CUTIL_CPP17_SUPPORTED
			std::sort(std::execution::par_unseq, vec.begin(), vec.end(), comp);
		#else
			std::sort(vec.begin(), vec.end(), comp);
		#endif
		}
	}
	
	
	/**
	 * @brief Converts any datatype into std::string.
	 *        Datatype must support << operator.
	 * @tparam T
	 * @param value - will be converted into std::string.
	 * @return Converted value as std::string.
	 */
	template<typename T> _CUTIL_DEPRECATED
	static inline std::string to_string(T value)
	{
		std::stringstream ss;
		ss << value;
		return ss.str();
	}

	/**
	 * @brief Converts std::string into any datatype.
	 *        Datatype must support << operator.
	 * @tparam T
	 * @param str - std::string that will be converted into datatype T.
	 * @return Variable of datatype T.
	 */
	template<typename T> _CUTIL_DEPRECATED
	static inline T parse_string(const std::string & str)
	{
		T result;
		std::istringstream(str) >> result;
		return result;
	}

	/**
	 * @brief Converts std::string to lower case.
	 * @param str - std::string that needs to be converted.
	 * @return Lower case input std::string.
	 */
	static inline _CUTIL_NODISCARD
	std::string to_lower(const std::string & str)
	{
		auto result = str;
		std::transform(result.begin(), result.end(), result.begin(), [](uint8_t c) -> uint8_t
		{
			return static_cast<uint8_t>(std::tolower(c));
		});
		return result;
	}

	/**
	 * @brief Converts std::string to upper case.
	 * @param str - std::string that needs to be converted.
	 * @return Upper case input std::string.
	 */
	static inline _CUTIL_NODISCARD
	std::string to_upper(const std::string & str)
	{
		auto result = str;
		std::transform(result.begin(), result.end(), result.begin(), [](uint8_t c) -> uint8_t
		{
			return static_cast<uint8_t>(std::toupper(c));
		});
		return result;
	}

	/**
	 * @brief Converts the first character of a string to uppercase letter and lowercases all other characters, if any.
	 * @param str - input string to be capitalized.
	 * @return A string with the first letter capitalized and all other characters lowercased. It doesn't modify the input string.
	 */
	static inline _CUTIL_NODISCARD
	std::string capitalize(const std::string & str)
	{
		auto result = str;
		if (!result.empty())
		{
			result.front() = static_cast<char>(std::toupper(result.front()));
		}
		return result;
	}

	/**
	 * @brief Converts only the first character of a string to uppercase letter, all other characters stay unchanged.
	 * @param str - input string to be modified.
	 * @return A string with the first letter capitalized. All other characters stay unchanged. It doesn't modify the input string.
	 */
	static inline _CUTIL_NODISCARD
	std::string capitalize_first_char(const std::string & str)
	{
		auto result = to_lower(str);
		if (!result.empty())
		{
			result.front() = static_cast<char>(std::toupper(result.front()));
		}
		return result;
	}

	/**
	 * @brief Checks if input std::string str contains specified substring.
	 * @param str - std::string to be checked.
	 * @param substring - searched substring.
	 * @return True if substring was found in str, false otherwise.
	 */
	static inline _CUTIL_NODISCARD
	bool contains(const std::string & str, const std::string & substring)
	{
		return str.find(substring) != std::string::npos;
	}

	/**
	 * @brief Checks if input std::string str contains specified character.
	 * @param str - std::string to be checked.
	 * @param character - searched character.
	 * @return True if character was found in str, false otherwise.
	 */
	static inline _CUTIL_NODISCARD
	bool contains(const std::string & str, const char character)
	{
		return contains(str, std::string(1, character));
	}

	/**
	 * @brief Compares two std::strings ignoring their case (lower/upper).
	 * @param str1 - std::string to compare
	 * @param str2 - std::string to compare
	 * @return True if str1 and str2 are equal, false otherwise.
	 */
	static inline _CUTIL_NODISCARD
	bool compare_ignore_case(const std::string & str1, const std::string & str2)
	{
		return to_lower(str1) == to_lower(str2);
	}

	/**
	 * @brief Trims (in-place) white spaces from the left side of std::string.
	 *        Taken from: http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring.
	 * @param str - input std::string to remove white spaces from.
	 */
	static inline
	void trim_left(std::string & str)
	{
		str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](int ch) { return !std::isspace(ch); }));
	}

	/**
	 * @brief Trims (in-place) white spaces from the right side of std::string.
	 *        Taken from: http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring.
	 * @param str - input std::string to remove white spaces from.
	 */
	static inline
	void trim_right(std::string & str)
	{
		str.erase(std::find_if(str.rbegin(), str.rend(), [](int ch) { return !std::isspace(ch); }).base(), str.end());
	}

	/**
	 * @brief Trims (in-place) white spaces from the both sides of std::string.
	 *        Taken from: http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring.
	 * @param str - input std::string to remove white spaces from.
	 */
	static inline
	void trim(std::string & str)
	{
		trim_left(str);
		trim_right(str);
	}

	 /**
	  * @brief Trims white spaces from the left side of std::string.
	  *        Taken from: http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring.
	  * @param str - input std::string to remove white spaces from.
	  * @return Copy of input str with trimmed white spaces.
	  */
	static inline _CUTIL_NODISCARD
	std::string trim_left_copy(const std::string& str)
	{
		std::string result = str;
		trim_left(result);
		return result;
	}

	/**
	  * @brief Trims white spaces from the right side of std::string.
	  *        Taken from: http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring.
	  * @param str - input std::string to remove white spaces from.
	  * @return Copy of input str with trimmed white spaces.
	  */
	static inline _CUTIL_NODISCARD
	std::string trim_right_copy(const std::string& str)
	{
		std::string result = str;
		trim_right(result);
		return result;
	}

	/**
	  * @brief Trims white spaces from the both sides of std::string.
	  *        Taken from: http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring.
	  * @param str - input std::string to remove white spaces from.
	  * @return Copy of input str with trimmed white spaces.
	  */
	static inline _CUTIL_NODISCARD
	std::string trim_copy(const std::string& str)
	{
		std::string result = str;
		trim(result);
		return result;
	}

	/**
	 * @brief Replaces (in-place) the first occurrence of target with replacement.
	 *        Taken from: http://stackoverflow.com/questions/3418231/c-replace-part-of-a-string-with-another-string.
	 * @param str - input std::string that will be modified.
	 * @param target - substring that will be replaced with replacement.
	 * @param replacement - substring that will replace target.
	 * @return True if replacement was successfull, false otherwise.
	 */
	static inline
	bool replace_first(std::string & str, const std::string & target, const std::string & replacement)
	{
		const size_t start_pos = str.find(target);
		if (start_pos == std::string::npos)
		{
			return false;
		}
		str.replace(start_pos, target.length(), replacement);
		return true;
	}

	/**
	 * @brief Replaces (in-place) last occurrence of target with replacement.
	 *        Taken from: http://stackoverflow.com/questions/3418231/c-replace-part-of-a-string-with-another-string.
	 * @param str - input std::string that will be modified.
	 * @param target - substring that will be replaced with replacement.
	 * @param replacement - substring that will replace target.
	 * @return True if replacement was successfull, false otherwise.
	 */
	static inline
	bool replace_last(std::string & str, const std::string & target, const std::string & replacement)
	{
		size_t start_pos = str.rfind(target);
		if (start_pos == std::string::npos)
		{
			return false;
		}
		str.replace(start_pos, target.length(), replacement);
		return true;
	}

	/**
	 * @brief Replaces (in-place) all occurrences of target with replacement.
	 *        Taken from: http://stackoverflow.com/questions/3418231/c-replace-part-of-a-string-with-another-string.
	 * @param str - input std::string that will be modified.
	 * @param target - substring that will be replaced with replacement.
	 * @param replacement - substring that will replace target.
	 * @return True if replacement was successfull, false otherwise.
	 */
	static inline
	bool replace_all(std::string & str, const std::string & target, const std::string & replacement)
	{
		if (target.empty())
		{
			return false;
		}
		size_t start_pos = 0;
		const bool found_substring = str.find(target, start_pos) != std::string::npos;
		while ((start_pos = str.find(target, start_pos)) != std::string::npos)
		{
			str.replace(start_pos, target.length(), replacement);
			start_pos += replacement.length();
		}
		return found_substring;
	}

	/**
	 * @brief Checks if std::string str ends with specified suffix.
	 * @param str - input std::string that will be checked.
	 * @param suffix - searched suffix in str.
	 * @return True if suffix was found, false otherwise.
	 */
	static inline _CUTIL_NODISCARD
	bool ends_with(const std::string & str, const std::string & suffix)
	{
		const auto suffix_start = str.size() - suffix.size();
		const auto result = str.find(suffix, suffix_start);
		return (result == suffix_start) && (result != std::string::npos);
	}

	/**
	 * @brief Checks if std::string str ends with specified character.
	 * @param str - input std::string that will be checked.
	 * @param suffix - searched character in str.
	 * @return True if ends with character, false otherwise.
	 */
	static inline _CUTIL_NODISCARD
	bool ends_with(const std::string & str, const char suffix)
	{
		return !str.empty() && (str.back() == suffix);
	}

	/**
	 * @brief Checks if std::string str starts with specified prefix.
	 * @param str - input std::string that will be checked.
	 * @param prefix - searched prefix in str.
	 * @return True if prefix was found, false otherwise.
	 */
	static inline _CUTIL_NODISCARD
	bool starts_with(const std::string & str, const std::string & prefix)
	{
		return str.rfind(prefix, 0) == 0;
	}

	/**
	 * @brief Checks if std::string str starts with specified character.
	 * @param str - input std::string that will be checked.
	 * @param prefix - searched character in str.
	 * @return True if starts with character, false otherwise.
	 */
	static inline _CUTIL_NODISCARD
	bool starts_with(const std::string & str, const char prefix)
	{
		return !str.empty() && (str.front() == prefix);
	}

	/**
	 * @brief Splits input std::string str according to input delim.
	 * @param str - std::string that will be splitted.
	 * @param delim - the delimiter.
	 * @return std::vector<std::string> that contains all splitted tokens.
	 */
	static inline _CUTIL_NODISCARD
	std::vector<std::string> split(const std::string & str, const char delim)
	{
		std::vector<std::string> tokens;
		std::stringstream ss(str);
		std::string token;
		while(std::getline(ss, token, delim))
		{
			tokens.push_back(token);
		}
		// Match semantics of split(str,str)
		if (str.empty() || ends_with(str, delim)) {
			tokens.emplace_back();
		}
		return tokens;
	}

	/**
	 * @brief Splits input std::string str according to input std::string delim.
	 *        Taken from: https://stackoverflow.com/a/46931770/1892346.
	 * @param str - std::string that will be split.
	 * @param delim - the delimiter.
	 * @return std::vector<std::string> that contains all splitted tokens.
	 */
	static inline _CUTIL_NODISCARD
	std::vector<std::string> split(const std::string & str, const std::string & delim)
	{
		size_t pos_start = 0, pos_end, delim_len = delim.length();
		std::string token;
		std::vector<std::string> tokens;
		while ((pos_end = str.find(delim, pos_start)) != std::string::npos)
		{
			token = str.substr(pos_start, pos_end - pos_start);
			pos_start = pos_end + delim_len;
			tokens.push_back(token);
		}
		tokens.push_back(str.substr(pos_start));
		return tokens;
	}

	/**
	 * @brief Splits input string using regex as a delimiter.
	 * @param src - std::string that will be split.
	 * @param rgx_str - the set of delimiter characters.
	 * @return vector of resulting tokens.
	 */
	static inline _CUTIL_NODISCARD
	std::vector<std::string> regex_split(const std::string& src, const std::string& rgx_str)
	{
		std::vector<std::string> elems;
		const std::regex rgx(rgx_str);
		std::sregex_token_iterator iter(src.begin(), src.end(), rgx, -1);
		std::sregex_token_iterator end;
		while (iter != end)
		{
			elems.push_back(*iter);
			++iter;
		}
		return elems;
	}

	/**
	 * @brief Splits input string using regex as a delimiter.
	 * @param src - std::string that will be split.
	 * @param dest - map of matched delimiter and those being splitted.
	 * @param rgx_str - the set of delimiter characters.
	 * @return True if the parsing is successfully done.
	 */
	static inline _CUTIL_NODISCARD
	std::map<std::string, std::string> regex_split_map(const std::string& src, const std::string& rgx_str)
	{
		std::map<std::string, std::string> dest;
		std::string tstr = src + " ";
		std::regex rgx(rgx_str);
		std::sregex_token_iterator niter(tstr.begin(), tstr.end(), rgx);
		std::sregex_token_iterator viter(tstr.begin(), tstr.end(), rgx, -1);
		std::sregex_token_iterator end;
		++viter;
		while (niter != end)
		{
			dest[*niter] = *viter;
			++niter;
			++viter;
		}
		return dest;
	}

	/**
	 * @brief Splits input string using any delimiter in the given set.
	 * @param str - std::string that will be split.
	 * @param delims - the set of delimiter characters.
	 * @return vector of resulting tokens.
	 */
	static inline _CUTIL_NODISCARD
	std::vector<std::string> split_any(const std::string & str, const std::string & delims)
	{
		std::string token;
		std::vector<std::string> tokens;
		size_t pos_start = 0;
		for (size_t pos_end = 0; pos_end < str.length(); ++pos_end)
		{
			if (contains(delims, str[pos_end]))
			{
				token = str.substr(pos_start, pos_end - pos_start);
				tokens.push_back(token);
				pos_start = pos_end + 1;
			}
		}
		tokens.push_back(str.substr(pos_start));
		return tokens;
	}

	/**
	 * @brief Joins all elements of a container of arbitrary datatypes
	 *        into one std::string with delimiter delim.
	 * @tparam Container - container type.
	 * @param tokens - container of tokens.
	 * @param delim - the delimiter.
	 * @return std::string with joined elements of container tokens with delimiter delim.
	 */
	template<typename Container> static inline _CUTIL_NODISCARD
	std::string join(const Container & tokens, const std::string & delim)
	{
		std::string result;
		for(auto it = tokens.begin(); it != tokens.end(); ++it)
		{
			if(it != tokens.begin())
			{
				result += delim;
			}
			result += *it;
		}
		return result;
	}

	/**
	 * @brief Inplace removal of all empty strings in a container of strings
	 * @tparam Container - container type.
	 * @param tokens - container of strings.
	 */
	template<template<typename, typename...> typename Container, typename... Args>
	static inline void drop_empty(Container<std::string, Args...> & tokens)
	{
		auto last = std::erase_if(tokens, [](auto& s){ return s.empty(); });
	}

	/**
	 * @brief Inplace removal of all empty strings in a container of strings
	 * @tparam container - container type.
	 * @param tokens - container of strings.
	 * @return container of non-empty tokens.
	 */
	template<template<typename, typename...> typename Container, typename... Args> _CUTIL_NODISCARD
	static inline Container<std::string> drop_empty_copy(const Container<std::string, Args...>& tokens)
	{
		auto result = tokens;
		drop_empty(result);
		return result;
	}

	/**
	 * @brief Inplace removal of all duplicate strings in a vector<string> where order is not to be maintained
	 *        Taken from: C++ Primer V5
	 * @tparam T - arbitrary datatype.
	 * @param tokens - vector of strings.
	 * @return vector of non-duplicate tokens.
	 */
	template<typename T>
	static inline void drop_duplicate(std::vector<T> &tokens)
	{
		internal::sort(tokens);
		// std::sort(std::execution::par_unseq, tokens.begin(), tokens.end());
		auto end_unique = std::unique(tokens.begin(), tokens.end());
		tokens.erase(end_unique, tokens.end());
	}

	/**
	 * @brief Removal of all duplicate strings in a vector<string> where order is not to be maintained
	 *        Taken from: C++ Primer V5
	 * @tparam T - arbitrary datatype.
	 * @param tokens - vector of strings.
	 * @return vector of non-duplicate tokens.
	 */
	template<typename T> _CUTIL_NODISCARD
	static inline std::vector<T> drop_duplicate_copy(const std::vector<T>& tokens)
	{
		std::vector<T> result = tokens;
		internal::sort(result);
		// std::sort(std::execution::par_unseq, tokens.begin(), tokens.end());
		auto end_unique = std::unique(result.begin(), result.end());
		result.erase(end_unique, result.end());
		return result;
	}

	/**
	 * @brief Creates new std::string with repeated n times substring str.
	 * @param str - substring that needs to be repeated.
	 * @param n - number of iterations.
	 * @return std::string with repeated substring str.
	 */
	static inline _CUTIL_NODISCARD
	std::string repeat(const std::string & str, size_t n)
	{
		std::string result;
		result.reserve(str.size() * n);
		for(size_t i = 0; i < n; ++i)
		{
			result += str;
		}
		return result;
	}

	/**
	 * @brief Creates new std::string with repeated n times char c.
	 * @param c - char that needs to be repeated.
	 * @param n - number of iterations.
	 * @return std::string with repeated char c.
	 */
	static inline _CUTIL_NODISCARD
	std::string repeat(char c, size_t n)
	{
		return std::string(n, c);
	}

	/**
	 * @brief Checks if input std::string str matches specified reular expression regex.
	 * @param str - std::string to be checked.
	 * @param regex - the std::regex regular expression.
	 * @return True if regex matches str, false otherwise.
	 */
	static inline _CUTIL_NODISCARD
	bool matches(const std::string & str, const std::regex & regex)
	{
		return std::regex_match(str, regex);
	}

	/**
	 * @brief Sort input std::vector<std::string> strs in ascending order.
	 * @param strs - std::vector<std::string> to be checked.
	 */
	template<typename T>
	static inline void sorting_ascending(std::vector<T> &strs)
	{
		// std::sort(std::execution::par_unseq, strs.begin(), strs.end());
		internal::sort(strs, std::less<T>());
	}

	/**
	 * @brief Sorted input std::vector<std::string> strs in descending order.
	 * @param strs - std::vector<std::string> to be checked.
	 */
	template<typename T>
	static inline void sorting_descending(std::vector<T> &strs)
	{
		// std::sort(std::execution::par_unseq, strs.begin(),strs.end(), std::greater<T>());
		internal::sort(strs, std::greater<T>());
	}

	/**
	 * @brief Reverse input container strs.
	 * @param strs - container to be checked.
	 */
	template<typename Container>
	static inline void reverse_inplace(Container &strs)
	{
		std::reverse(strs.begin(), strs.end());
	}

	/**
	 * @brief Reverse input container strs.
	 * @param strs - container to be checked.
	 */
	template<typename Container> _CUTIL_NODISCARD
	static inline Container reverse_copy(const Container& strs)
	{
		Container result = strs;
		std::reverse(result.begin(), result.end());
		return result;
	}
} // namespace

_CUTIL_NAMESPACE_END
#endif // __cplusplus
#endif /* CONSOLEUTIL_EXTERNAL_STRING_UTIL_H__ */
