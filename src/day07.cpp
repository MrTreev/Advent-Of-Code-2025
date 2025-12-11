#include "util.h"

namespace {
using std::ranges::views::iota;
} // namespace

void aoc::run() {
    const auto dayvec{file::lines(aoc::file::day_stream())};
    for (const size_t lineno: iota(1U, dayvec.size())) {
        for (const size_t idx: iota(0U, dayvec.back().size())) {
        }
    }
}
