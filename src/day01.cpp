#include "util.h"

void aoc::run() {
    std::ifstream daystr{aoc::file::day_stream()};
    int64_t       pointer{50};
    size_t        zeroes{0};

    aoc::print("move: {:5} : {:>2}, {:>2}, {:>2}", "", pointer, 0, 0);

    std::string line;
    while (std::getline(daystr, line)) {
        const auto shift = aoc::string::str_to_long(line.substr(1));
        if (line[0] == 'L') {
            for (int64_t val{(pointer - shift)}; val < 0; val += 100) {
                zeroes++;
            }
            pointer = ((pointer + 1000) - shift) % 100;
        } else {
            for (int64_t val{pointer + shift}; val >= 100; val -= 100) {
                zeroes++;
            }
            pointer = (pointer + shift) % 100;
        }
        aoc::part1 += static_cast<unsigned int>(pointer == 0);
        aoc::print("move: {:5} : {:>2}, {:>2}, {:>2}", line, pointer, aoc::part1, zeroes);
        aoc::part2 += zeroes;
        zeroes      = 0;
    }
}

// too big: 6183
// too low: 6107
