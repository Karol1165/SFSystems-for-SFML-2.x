#pragma once
#ifndef CUSTOMHASH_HPP_
#define CUSTOMHASH_HPP_

#include <variant>
#include <string>
#include <utility>
#include <vector>

namespace std {
    template <>
    struct hash<std::pair<std::string, std::string>> {
        size_t operator()(const std::pair<std::string, std::string>& p) const {
            size_t h1 = hash<std::string>{}(p.first);
            size_t h2 = hash<std::string>{}(p.second);
            return h1 ^ (h2 << 1);
        }
    };

    template <>
    struct hash<std::variant<std::wstring, std::vector<std::wstring>>> {
        size_t operator()(const std::variant<std::wstring, std::vector<std::wstring>>& v) const {
            return std::visit([](const auto& value) -> size_t {
                return hash<decltype(value)>{}(value);
                }, v);
        }
    };
}

#endif