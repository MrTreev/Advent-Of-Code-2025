#include "util.h"
#include <ranges>
#include <string_view>

namespace {
using aoc::format;
using aoc::debug;
using std::views::iota;
using std::views::zip;
using pairvec = std::vector<std::pair<std::string_view, std::string_view>>;

constexpr auto to_size_t(std::string_view chars) {
    return aoc::string::toint<size_t>(chars);
}

constexpr pairvec parse(const std::string_view dayview) {
    size_t  idx_beg = 0;
    size_t  idx_sep = 0;
    pairvec id_ranges;
    for (const auto [idx, cha]: zip(iota(0U, dayview.length()), dayview)) {
        if ((cha == ',') || (cha == '\n')) {
            id_ranges.emplace_back(
                dayview.substr(idx_beg, idx_sep - idx_beg),
                dayview.substr(idx_sep + 1, idx - idx_sep - 1)
            );
            idx_beg = idx + 1;
        } else if (cha == '-') {
            idx_sep = idx;
        }
    }
    return id_ranges;
}

void check_part1(std::string_view id_view) {
    if ((id_view.length() % 2) == 0) {
        const size_t           split = id_view.length() / 2;
        const std::string_view sub_lo{id_view.substr(0, split)};
        const std::string_view sub_hi{id_view.substr(split)};
        if (sub_lo == sub_hi) {
            aoc::part1 += to_size_t(id_view);
        }
    }
}

void check_part2(std::string_view id_view) {
    if (id_view.length() < 2) {
        return;
    }
    bool invalid = false;
    for (const size_t testno: iota(1U, id_view.length())) {
        if ((id_view.length() % testno) == 0) {
            std::vector<std::string_view> subs;
            for (const size_t idx: iota(0U, id_view.length() / testno)) {
                subs.push_back(id_view.substr(idx * testno, testno));
            }
            if (aoc::vec_same(subs)) {
                invalid = true;
                debug("ID: {}, DIV: {}, {}", id_view, testno, format(subs));
            }
        }
    }
    if (invalid) {
        aoc::part2 += to_size_t(id_view);
        debug("Invalid ID: {}", id_view);
    }
}
} // namespace

void aoc::run() {
    std::ifstream     daystream{file::day_stream()};
    const std::string daystring{string::slurp(daystream)};
    const pairvec     id_ranges{parse(daystring)};
    for (const auto& [id_lo, id_hi]: id_ranges) {
        for (const size_t id_no: iota(to_size_t(id_lo), to_size_t(id_hi) + 1)) {
            const std::string      id_str = std::format("{}", id_no);
            const std::string_view id_view{id_str};
            check_part1(id_view);
            check_part2(id_view);
        }
    }
}

/*
 * 11-22
 * 95-115
 * 998-1012
 * 1188511880-1188511890
 * 222220-222224
 * 1698522-1698528
 * 446443-446449
 * 38593856-38593862
 * 565653-565659
 * 824824821-824824827
 * 2121212118-2121212124
 */
