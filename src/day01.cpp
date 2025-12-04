#include "util.h"
#include <ranges>

namespace {
//NOLINTNEXTLINE(*-non-const-global-variables)
int64_t part1_pointer = 50;
//NOLINTNEXTLINE(*-non-const-global-variables)
int64_t part2_pointer = 50;

void test_part1(int64_t shift, char direction) {
    if (direction == 'L') {
        part1_pointer = ((part1_pointer + 1000) - shift) % 100;
    } else {
        part1_pointer = (part1_pointer + shift) % 100;
    }
    aoc::part1 += static_cast<unsigned int>(part1_pointer == 0);
}

// This is a stupid method, I couldn't be bothered trying to figure out a smart one.
void test_part2(int64_t shift, char direction) {
    const int64_t mod   = (direction == 'L') ? -1 : 1;
    size_t        ticks = 0;
    for ([[maybe_unused]]
         const int64_t tmp: std::views::iota(0, shift)) {
        part2_pointer = (part2_pointer + mod);
        if (part2_pointer == 100 || part2_pointer == -1) {
            if (part2_pointer == 100) {
                part2_pointer = 0;
            } else if (part2_pointer == -1) {
                part2_pointer = 99;
            } else {
                aoc::check(false, "went too fast");
            }
        }
        if (part2_pointer == 0) {
            ticks += 1;
        }
    }
    aoc::part2 += ticks;
    aoc::debug(
        "move: {}{:<5} : {:>2}, {:>2}, ({:>4})",
        direction,
        shift,
        part2_pointer,
        ticks,
        aoc::part2
    );
}
} // namespace

void aoc::run() {
    std::ifstream daystr{aoc::file::day_stream()};
    int64_t       pointer{50};
    aoc::print("move:  {:5} : {:>2}", "", pointer);

    std::string line;
    while (std::getline(daystr, line)) {
        const auto shift = aoc::string::toint<int64_t>(line.substr(1));
        test_part1(shift, line[0]);
        test_part2(shift, line[0]);
    }
}

// too big: 6183
// too low: 6107
