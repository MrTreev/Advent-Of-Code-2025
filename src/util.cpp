#include "util.h"
#include "answers.h"
#include <iostream>
#include <stdexcept>

// NOLINTBEGIN(cppcoreguidelines-avoid-non-const-global-variables)
size_t         aoc::part1{0};
size_t         aoc::part2{0};
static uint8_t g_day{0}; // NOLINT(*-anonymous-namespace)

// NOLINTEND(cppcoreguidelines-avoid-non-const-global-variables)

std::string aoc::file::day_file(uint8_t day) {
    g_day = day;
    const std::string fname{test_mode ? "test" : "day"};
    const std::string filename = std::format("out/test/{}{:02}.txt", fname, day);
    std::println(std::cout, "Advent of Code Day {}, filename: {}", day, filename);
    return filename;
}

std::filesystem::path aoc::file::day_path(uint8_t day) {
    return std::filesystem::relative(day_file(day));
}

std::filesystem::path aoc::file::day_stream(const std::source_location& loc) {
    const std::string fname{loc.file_name()};
    const uint8_t     day =
        string::char_to_uint(fname.at(fname.size() - 6), fname.at(fname.size() - 5));
    return {day_path(day)};
}

namespace {
size_t get_part_1() { // NOLINT(*-cognitive-complexity)
    // NOLINTBEGIN(*-magic-numbers)
    switch (g_day) {
    case 1:  return aoc::test_mode ? day01::test1 : day01::part1;
    case 2:  return aoc::test_mode ? day02::test1 : day02::part1;
    case 3:  return aoc::test_mode ? day03::test1 : day03::part1;
    case 4:  return aoc::test_mode ? day04::test1 : day04::part1;
    case 5:  return aoc::test_mode ? day05::test1 : day05::part1;
    case 6:  return aoc::test_mode ? day06::test1 : day06::part1;
    case 7:  return aoc::test_mode ? day07::test1 : day07::part1;
    case 8:  return aoc::test_mode ? day08::test1 : day08::part1;
    case 9:  return aoc::test_mode ? day09::test1 : day09::part1;
    case 10: return aoc::test_mode ? day10::test1 : day10::part1;
    case 11: return aoc::test_mode ? day11::test1 : day11::part1;
    case 12: return aoc::test_mode ? day12::test1 : day12::part1;
    case 13: return aoc::test_mode ? day13::test1 : day13::part1;
    case 14: return aoc::test_mode ? day14::test1 : day14::part1;
    case 15: return aoc::test_mode ? day15::test1 : day15::part1;
    case 16: return aoc::test_mode ? day16::test1 : day16::part1;
    case 17: return aoc::test_mode ? day17::test1 : day17::part1;
    case 18: return aoc::test_mode ? day18::test1 : day18::part1;
    case 19: return aoc::test_mode ? day19::test1 : day19::part1;
    case 20: return aoc::test_mode ? day20::test1 : day20::part1;
    case 21: return aoc::test_mode ? day21::test1 : day21::part1;
    case 22: return aoc::test_mode ? day22::test1 : day22::part1;
    case 23: return aoc::test_mode ? day23::test1 : day23::part1;
    case 24: return aoc::test_mode ? day24::test1 : day24::part1;
    case 25: return aoc::test_mode ? day25::test1 : day25::part1;
    default: throw std::invalid_argument(std::format("Bad day: {}", g_day));
    }
    // NOLINTEND(*-magic-numbers)
}

size_t get_part_2() { // NOLINT(*-cognitive-complexity)
    // NOLINTBEGIN(*-magic-numbers)
    switch (g_day) {
    case 1:  return aoc::test_mode ? day01::test2 : day01::part2;
    case 2:  return aoc::test_mode ? day02::test2 : day02::part2;
    case 3:  return aoc::test_mode ? day03::test2 : day03::part2;
    case 4:  return aoc::test_mode ? day04::test2 : day04::part2;
    case 5:  return aoc::test_mode ? day05::test2 : day05::part2;
    case 6:  return aoc::test_mode ? day06::test2 : day06::part2;
    case 7:  return aoc::test_mode ? day07::test2 : day07::part2;
    case 8:  return aoc::test_mode ? day08::test2 : day08::part2;
    case 9:  return aoc::test_mode ? day09::test2 : day09::part2;
    case 10: return aoc::test_mode ? day10::test2 : day10::part2;
    case 11: return aoc::test_mode ? day11::test2 : day11::part2;
    case 12: return aoc::test_mode ? day12::test2 : day12::part2;
    case 13: return aoc::test_mode ? day13::test2 : day13::part2;
    case 14: return aoc::test_mode ? day14::test2 : day14::part2;
    case 15: return aoc::test_mode ? day15::test2 : day15::part2;
    case 16: return aoc::test_mode ? day16::test2 : day16::part2;
    case 17: return aoc::test_mode ? day17::test2 : day17::part2;
    case 18: return aoc::test_mode ? day18::test2 : day18::part2;
    case 19: return aoc::test_mode ? day19::test2 : day19::part2;
    case 20: return aoc::test_mode ? day20::test2 : day20::part2;
    case 21: return aoc::test_mode ? day21::test2 : day21::part2;
    case 22: return aoc::test_mode ? day22::test2 : day22::part2;
    case 23: return aoc::test_mode ? day23::test2 : day23::part2;
    case 24: return aoc::test_mode ? day24::test2 : day24::part2;
    case 25: return aoc::test_mode ? day25::test2 : day25::part2;
    default: throw std::invalid_argument(std::format("Bad day: {}", g_day));
    }
    // NOLINTEND(*-magic-numbers)
}

void print_part(uint8_t part, size_t num, size_t expected) {
    if (expected == 0) {
        aoc::print("Part {}: No stored answer, got {}", part, num);
    } else {
        if (num == expected) {
            aoc::print("Part {}: Correct with {}", part, num);
        } else {
            aoc::print("Part {}: Incorrect\ngot      {}\nexpected {}", part, num, expected);
        }
    }
}
} // namespace

int main() {
    aoc::run();
    print_part(1, aoc::part1, get_part_1());
    print_part(2, aoc::part2, get_part_2());
}
