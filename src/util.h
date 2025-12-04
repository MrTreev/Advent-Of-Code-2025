#pragma once
#include <algorithm>
#include <cassert>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cxxabi.h>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <ranges>
#include <source_location>
#include <sstream> // IWYU pragma: keep
#include <stdexcept>
#include <string>
#include <string_view>
#include <typeinfo>
#include <vector>

using std::int16_t;
using std::int32_t;
using std::int64_t;
using std::int8_t;

using std::uint16_t;
using std::uint32_t;
using std::uint64_t;
using std::uint8_t;

using std::intmax_t;
using std::intptr_t;
using std::uintmax_t;
using std::uintptr_t;

using std::byte;
using std::nullptr_t;
using std::ptrdiff_t;
using std::size_t;

namespace aoc {
constexpr bool test_mode =
#if defined(NDEBUG)
    false
#else
    true
#endif
    ;

// NOLINTBEGIN(cppcoreguidelines-avoid-non-const-global-variables)
extern size_t part1;
extern size_t part2;
// NOLINTEND(cppcoreguidelines-avoid-non-const-global-variables)

void run();

constexpr void print(const std::string_view str) {
    std::println(std::cout, "{}", str);
}

constexpr void print(std::string_view fst, auto&&... args) {
    print(std::string(std::vformat(fst, std::make_format_args(args...))));
}

constexpr void debug(std::string_view fst, auto&&... args) {
    if constexpr (test_mode) {
        print(fst, std::forward<decltype(args)>(args)...);
    }
}

constexpr bool in(auto item, const std::vector<decltype(item)>& vec) {
    return std::ranges::any_of(vec.begin(), vec.end(), [item](auto cmp) {
        return cmp == item;
    });
}

constexpr void check(bool condition, const std::string& msg) {
    if (!condition) {
        throw std::runtime_error(msg);
    }
}

template<typename T>
constexpr std::string format(const std::vector<T> vec) {
    std::string buf{"{"};
    for (const auto& item: vec) {
        buf += std::format("{},", item);
    }
    buf += "}";
    return buf;
}

constexpr bool vec_same(const std::ranges::range auto&& vec) {
    using T = std::ranges::range_value_t<decltype(vec)>;
    check(vec.size() > 1, "vec_same only takes vectors of length greater than one");
    const T& comp = vec[0];
    for (const T& item: vec) {
        if (item != comp) {
            return false;
        }
    }
    return true;
}

template<typename T>
constexpr auto max_in(const std::vector<T>& vec) {
    using std::views::iota;
    using std::views::zip;
    T      m_d{};
    size_t m_i{0};
    for (const auto&& [idx, item]: zip(iota(0U), vec)) {
        if (item > m_d) {
            m_d = item;
            m_i = idx;
        }
    }
    return std::make_pair(m_i, m_d);
}

namespace file {
std::string           day_file(uint8_t day);
std::filesystem::path day_path(uint8_t day);
std::filesystem::path day_stream(const std::source_location& loc = std::source_location::current());
} // namespace file

namespace string {
constexpr std::string slurp(std::ifstream& instr) {
    std::ostringstream sstr{};
    sstr << instr.rdbuf();
    return sstr.str();
}

constexpr bool is_numeric(char cha) {
    return (cha >= '0' && cha <= '9');
}

constexpr bool is_numeric(const std::string& str) {
    return std::ranges::all_of(str, [](const char cha) {
        return aoc::string::is_numeric(cha);
    });
}

constexpr uint8_t char_to_uint(char cha) {
    return static_cast<uint8_t>(cha) - static_cast<uint8_t>('0');
}

constexpr uint8_t char_to_uint(char cha_1, char cha_2) {
    return (10 * char_to_uint(cha_1)) + char_to_uint(cha_2);
}

template<std::integral T>
constexpr T toint(std::string_view chars) {
    T val = 0;
    for (const char cha: chars) {
        if (aoc::string::is_numeric(cha)) {
            val *= 10;
            val += aoc::string::char_to_uint(cha);
        } else {
            break;
        }
    }
    return val;
}

} // namespace string

namespace math {
constexpr size_t max(size_t aval, size_t bval) {
    return std::max(aval, bval);
}

constexpr size_t min(size_t aval, size_t bval) {
    return std::min(aval, bval);
}

constexpr size_t max(size_t aval, size_t bval, auto&&... args) {
    return max(std::max(aval, bval), std::forward<decltype(args)>(args)...);
}

constexpr size_t min(size_t aval, size_t bval, auto&&... args) {
    return min(std::min(aval, bval), std::forward<decltype(args)>(args)...);
}
} // namespace math

namespace types {
constexpr std::string type_name(auto&& item) {
    char* demangled_name = abi::__cxa_demangle(typeid(item).name(), nullptr, nullptr, nullptr);
    std::string ret_name{demangled_name};
    free(demangled_name); //NOLINT(*-no-malloc,cppcoreguidelines-owning-memory)
    return ret_name;
}
} // namespace types

} // namespace aoc
