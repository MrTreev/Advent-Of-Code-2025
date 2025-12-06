#include "util.h"
#include <ranges>

namespace {
using std::views::iota;
} // namespace

void aoc::run() {
    std::ifstream                    daystr{aoc::file::day_stream()};
    std::string                      line;
    std::vector<std::vector<size_t>> numbers{};
    std::vector<char>                operations{};
    while (std::getline(daystr, line)) {
        if (aoc::string::is_numeric(line.front())) {
            numbers.emplace_back();
            std::vector<size_t>& newvec = numbers.front();
            std::string          number;
            for (const char cha: line) {
                if (aoc::string::is_numeric(cha)) {
                    number += cha;
                } else if (!number.empty()) {
                    newvec.push_back(aoc::string::toint<size_t>(number));
                    number.clear();
                }
            }
        } else {
            numbers.emplace_back();
            for (const char cha: line) {
                if (cha == '*' || cha == '+') {
                    operations.push_back(cha);
                }
            }
        }
    }
    std::vector<std::vector<size_t>> formulae{};
    formulae.reserve(numbers.front().size());
    //NOLINTNEXTLINE(*-identifier-length)
    for (const auto _: iota(0U, numbers.front().size())) {
        formulae.emplace_back();
        formulae.back().reserve(numbers.size());
    }
}
