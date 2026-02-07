#include "pch.h"
#include "Parser.hpp"

namespace SFS {
	namespace Parser {
		template <CharT T>
		void skipWhiteChars(const std::basic_string<T>& str, size_t& index) {
			while (index < str.size() && (str[index] == ' ' || str[index] == '\t' || str[index] == '\n')) {
				index++;
			}
		}

		template<CharT T>
		bool match(const std::basic_string<T>& str, size_t& index, std::basic_string_view<T> pattern) {
			skipWhiteChars<T>(str, index);
			if (str.substr(index, pattern.size()) == pattern) {
				index += pattern.size();
				return true;
			}
			return false;
		}

		template<CharT T>
		void exceptedString(const std::basic_string<T>& str, size_t& index, std::basic_string_view<T> pattern) {
			if (!match<T>(str, index, pattern)) {
				throw std::runtime_error(std::string("Unexcepted character at: " + std::to_string(index)));
			}
		}

	}
}