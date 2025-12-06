#include "util.h"
#include <algorithm>
#include <ranges>
#include <string_view>

namespace {

#if NDEBUG
#    define write(...)
#    define showvar(...)
#else
#    define write(...)   ::std::print(std::cout, __VA_ARGS__)
#    define showvar(var) aoc::print(#var ": {}", var)
#endif

using aoc::string::char_to_uint;
using std::views::iota;
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
    constexpr size_t N_DIG{12U};
    for (const auto [bank_idx, bank]: zip(iota(0U), banks)) {
        showvar(bank);
        std::vector<size_t> idxs;
        for (const size_t num: iota(0U, N_DIG)) {
            size_t       max_idx{0};
            char         max_dig{'0'};
            const size_t beg_idx{idxs.empty() ? 0 : (idxs.back() + 1)};
            const size_t end_idx{(bank.size() + 1) - (N_DIG - num)};
            write("num({:>2}) ({:>2}-{:>2}), items: ", num, beg_idx, end_idx);
            for (const auto idx: iota(beg_idx, end_idx)) {
                const char dig = bank[idx];
                write("{}", dig);
                if (dig > max_dig) {
                    max_dig = dig;
                    max_idx = idx;
                    write("|");
                }
            }
            idxs.push_back(max_idx);
            write("\n");
        }
        std::string number{};
        for (const size_t idx: idxs) {
            number += bank[idx];
        }
        const auto joltage{aoc::string::toint<size_t>(number)};
        showvar(joltage);
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
