#include "util.h"
#include <algorithm>
#include <ranges>

namespace {
using sizpair = std::pair<size_t, size_t>;
using vecpair = std::vector<sizpair>;

std::pair<vecpair, std::vector<size_t>> parse(std::ifstream daystr) {
    std::string         line;
    vecpair             ranges;
    std::vector<size_t> items;
    while (std::getline(daystr, line)) {
        if (line.empty()) break;
        const auto [beg, end] = aoc::string::split(line, '-');
        ranges.emplace_back(aoc::string::toint<size_t>(beg), aoc::string::toint<size_t>(end));
    }
    while (std::getline(daystr, line)) {
        items.push_back(aoc::string::toint<size_t>(line));
    }
    return {ranges, items};
}

bool check_ranges(size_t item, const vecpair& ranges) {
    //NOLINTNEXTLINE(*-anyofallof)
    for (const auto [beg, end]: ranges) {
        if (beg <= item && item <= end) {
            return true;
        }
    }
    return false;
}

} // namespace

void aoc::run() {
    auto [ranges, items] = parse(std::ifstream(aoc::file::day_stream()));
    for (const size_t item: items) {
        if (check_ranges(item, ranges)) {
            aoc::part1 += 1;
        }
    }
    vecpair cleanranges{};
    quicksort_pairs(ranges);
    for (const auto [r_beg, r_end]: ranges) {
        if (cleanranges.empty()) {
            cleanranges.emplace_back(r_beg, r_end);
        } else {
            size_t& last_end{cleanranges.back().second};
            if (r_beg <= last_end) {
                last_end = std::max(r_end, last_end);
            } else {
                cleanranges.emplace_back(r_beg, r_end);
            }
        }
    }
    for (const auto [r_beg, r_end]: cleanranges) {
        aoc::part2 += r_end - r_beg + 1;
    }
}
