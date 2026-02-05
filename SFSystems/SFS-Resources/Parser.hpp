#pragma once  
#ifndef PARSER_HPP_  
#define PARSER_HPP_  

#include <string>  
#include <string_view>  
#include <concepts>

namespace SFS {  
namespace Parser {  

	template<typename T>  
	concept CharT = std::same_as<T, char> ||  
		std::same_as<T, signed char> ||  
		std::same_as<T, unsigned char> ||  
		std::same_as<T, wchar_t> ||  
		std::same_as<T, char8_t> ||  
		std::same_as<T, char16_t> ||  
		std::same_as<T, char32_t>;  

	template<CharT T>  
	inline void skipWhiteChars(const std::basic_string<T>& str, size_t& index);  

	inline void skipWhiteChars(const std::string& str, size_t& index) {
		skipWhiteChars<char>(str, index);
	}

	inline void skipWhiteChars(const std::wstring& str, size_t& index) {
		skipWhiteChars<wchar_t>(str, index);
	}

	template<CharT T>  
	inline bool match(const std::basic_string<T>& str, size_t& index, std::basic_string_view<T> pattern);  

	inline bool match(const std::string& str, size_t& index, std::string_view pattern) {  
		return match<char>(str, index, pattern);  
	}  

	inline bool match(const std::wstring& str, size_t& index, std::wstring_view pattern) {
		return match<wchar_t>(str, index, pattern);
	}

	template<CharT T>  
	inline void exceptedString(const std::basic_string<T>& str, size_t& index, std::basic_string_view<T> pattern);  

	inline void exceptedString(const std::string& str, size_t& index, std::string_view pattern) {
		exceptedString<char>(str, index, pattern);
	}

	inline void exceptedString(const std::wstring& str, size_t& index, std::wstring_view pattern) {
		exceptedString<wchar_t>(str, index, pattern);
	}

	
	inline std::string parseEscapeSequences(const std::string& str) {
		std::string result;
		bool isEscapeSequence = false;
		for (const auto& i : str) {
			if (i == '\\') {
				isEscapeSequence = true;
				continue;
			} else if (isEscapeSequence) {
				switch (i) {
					case 'n': {
						result.push_back('\n');
						break;
					} case 't': {
						result.push_back('\t');
						break;
					} case 'r': {
						result.push_back('\r');
						break;
					} case 'b': {
						result.push_back('\b');
						break;
					} case 'f': {
						result.push_back('\f');
						break;
					} case 'v': {
						result.push_back('\v');
						break;
					} case 'a': {
						result.push_back('\a');
						break;
					} case '0': {
						result.push_back('\0');
						break;
					} case '\\': {
						result.push_back('\\');
						break;
					} case '\'': {
						result.push_back('\'');
						break;
					} case '\"': {
						result.push_back('\"');
						break;
					} default: {
						result.push_back(i);
						break;
					}
				}
			} else
				result.push_back(i);
			isEscapeSequence = false;
		}
		return result;
	}
}
}  
  

#include "Parser.inl"

#endif