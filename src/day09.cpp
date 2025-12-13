#include "util.h"
#include <algorithm>

namespace {
struct coord {
    int64_t x;
    int64_t y;

    [[nodiscard]]
    std::string str() const {
        return std::format("({:>5},{:>5})", x, y);
    }
};

size_t area(const coord& a, const coord& b) {
    const int64_t xdist = std::labs((a.x > b.x) ? (a.x - b.x) : (b.x - a.x)) + 1;
    const int64_t ydist = std::labs((a.y > b.y) ? (a.y - b.y) : (b.y - a.y)) + 1;
    return static_cast<size_t>(xdist * ydist);
}

void area_unit_test() {
    const coord  pos1{.x = 2, .y = 5};
    const coord  pos2{.x = 11, .y = 1};
    const size_t tmp = area(pos1, pos2);
    aoc::check(tmp == 50, "tmp should equal 50");
}

std::vector<coord> parse(const std::vector<std::string>& lines) {
    std::vector<coord> retval;
    for (const std::string& line: lines) {
        const auto [x, y] = aoc::string::split(line, ',');
        retval.emplace_back(aoc::string::toint<int64_t>(x), aoc::string::toint<int64_t>(y));
    }
    return retval;
}

void run_part1(const std::vector<coord>& dayvec) {
    size_t biggest{0};
    for (const auto& pos1: dayvec) {
        for (const auto& pos2: dayvec) {
            biggest = std::max(area(pos1, pos2), biggest);
        }
    }
    aoc::part1 = biggest;
}

void second_unit_test() {
    const coord  pos1{.x = 2, .y = 5};
    const coord  pos2{.x = 11, .y = 1};
    const size_t tmp = area(pos1, pos2);
    aoc::check(tmp == 50, "tmp should equal 50");
}

void run_part2([[maybe_unused]] const std::vector<coord>& dayvec) {}

} // namespace

void aoc::run() {
    const std::vector<coord> dayvec{parse(file::lines(aoc::file::day_stream()))};
    area_unit_test();
    run_part1(dayvec);
    second_unit_test();
    run_part2(dayvec);
}
