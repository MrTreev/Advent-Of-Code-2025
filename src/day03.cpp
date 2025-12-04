#include "util.h"
#include <algorithm>
#include <iterator>
#include <ranges>

namespace {
using aoc::string::char_to_uint;
using std::ranges::distance;
using std::ranges::max_element;
using std::views::iota;
using std::views::take;
using std::views::zip;

void run_part1(const std::vector<std::string>& banks) {
    for (const std::string_view bank: banks) {
        char   m_d{'0'};
        size_t m_i{0};
        for (auto [idx, dig]: zip(iota(0U), bank.substr(0, bank.length() - 1))) {
            if (dig > m_d) {
                m_d = dig;
                m_i = idx;
            }
        }
        char n_d{'0'};
        for (const char dig: bank.substr(m_i + 1)) {
            n_d = std::max(dig, n_d);
        }
        const size_t joltage  = char_to_uint(m_d, n_d);
        //aoc::debug("bank: {}, joltage: {}", bank, joltage);
        aoc::part1           += joltage;
    }
}

void run_part2(const std::vector<std::string>& banks) {
    for (const std::string_view bank: banks) {
        std::string number{};
        size_t      new_idx{0};
        aoc::debug("bank: {}", bank);
        aoc::debug("length: {}", bank.length());
        for (const size_t num: iota(0U, 11U)) {
            aoc::debug("new_idx: {}", new_idx);
            aoc::debug("num: {}", num);
            const auto sub_end = ((bank.length() - new_idx) - num);
            aoc::debug("sub_end: {}", sub_end);
            const auto        subst  = bank.substr(new_idx, sub_end);
            const auto* const result = max_element(subst);
            aoc::debug("result: {}", result);
            new_idx  = static_cast<size_t>(distance(bank.begin(), result)) + 1U;
            number  += *result;
            aoc::debug("number: {}", number);
        }
        aoc::debug("");

        const auto joltage{aoc::string::toint<size_t>(number)};
        aoc::print("bank: {}, joltage: {}", bank, joltage);
        aoc::part2 += joltage;
    }
}
} // namespace

void aoc::run() {
    std::ifstream            daystr{aoc::file::day_stream()};
    std::string              line;
    std::vector<std::string> banks;
    while (std::getline(daystr, line)) {
        banks.push_back(line);
    }
    run_part1(banks);
    run_part2(banks);
}
