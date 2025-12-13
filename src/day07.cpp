#include "util.h"

namespace {
using aoc::check;
using std::ranges::views::iota;

void run_part1(std::vector<std::string> dayvec) {
    for (const size_t lineno: iota(1U, dayvec.size())) {
        for (const size_t idx: iota(0U, dayvec.back().size())) {
            const char lastline = dayvec[lineno - 1][idx];
            if (lastline == '|' || lastline == 'S') {
                const char thisline = dayvec[lineno][idx];
                switch (thisline) {
                case '|': break;
                case '.': dayvec[lineno][idx] = '|'; break;
                case '^':
                    if (dayvec[lineno][idx + 1] == '.') dayvec[lineno][idx + 1] = '|';
                    if (dayvec[lineno][idx - 1] == '.') dayvec[lineno][idx - 1] = '|';
                    aoc::part1 += 1;
                    break;
                default: check(false, std::format("unknown character '{}'", thisline));
                }
            }
        }
    }
}

size_t vecend([[maybe_unused]] const std::vector<std::string>& dayvec) {
    const char* const back = "\033[F";
    std::string       printval{};
    std::string       prefix{back};
    for (const auto& lineval: dayvec) {
        printval += lineval + "\n";
        prefix   += back;
    }
    aoc::print(prefix + printval);
    return 1U;
}

constexpr size_t WIDTH  = 142;
constexpr size_t HEIGHT = 142;

std::array<size_t, WIDTH * HEIGHT> memo{};

//NOLINTNEXTLINE(misc-no-recursionn
size_t run_part2(std::vector<std::string> vec, size_t lno, size_t idx) {
    vec[lno][idx] = '|';
    if (lno + 1 == vec.size()) return vecend(vec);
    size_t& item = memo[(lno * WIDTH) + idx];
    if (item == 0) {
        if (vec[lno + 1][idx] == '.') {
            item = run_part2(vec, lno + 1, idx);
        } else if (vec[lno + 1][idx] == '^') {
            const size_t val1{run_part2(vec, lno + 1, idx - 1)};
            const size_t val2{run_part2(vec, lno + 1, idx + 1)};
            item = val1 + val2;
        } else {
            check(
                false,
                std::format("unknown character at ({},{}): '{}'", lno, idx, vec[lno + 1][idx])
            );
        }
    }
    return item;
}

} // namespace

void aoc::run() {
    const auto dayvec{file::lines(aoc::file::day_stream())};
    run_part1(dayvec);
    part2 = run_part2(dayvec, 1, find_idx(dayvec.front(), 'S'));
}
