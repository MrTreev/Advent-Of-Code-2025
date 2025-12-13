#include "util.h"
#include <algorithm>
#include <cmath>
#include <ranges>

namespace {
using std::ranges::views::iota;
using std::ranges::views::zip;

using lfloat = long double;

struct Triple {
    //NOLINTBEGIN(*-non-private-member-*)
    long x;
    long y;
    long z;

    //NOLINTEND(*-non-private-member-*)

    bool operator==(const Triple& other) const {
        return (
            (x == other.x) && //
            (y == other.y) && //
            (z == other.z)    //
        );
    }

    [[maybe_unused]] [[nodiscard]]
    std::string str() const {
        return std::format("({:>3},{:>3},{:>3})", x, y, z);
    }
};

std::vector<Triple> parse(const std::vector<std::string>& dayvec) {
    std::vector<Triple> retval;
    retval.reserve(dayvec.size());
    for (const std::string& line: dayvec) {
        const auto [first, tmp]    = aoc::string::split(line, ',');
        const auto [second, third] = aoc::string::split(tmp, ',');
        retval.emplace_back(
            aoc::string::toint<long>(first),
            aoc::string::toint<long>(second),
            aoc::string::toint<long>(third)
        );
    }
    return retval;
}

lfloat sl_distance(const Triple& a, const Triple& b) {
    return std::sqrtl(
        std::powl(a.x - b.x, 2) + //
        std::powl(a.y - b.y, 2) + //
        std::powl(a.z - b.z, 2)   //
    );
}

std::vector<std::pair<lfloat, std::pair<Triple, Triple>>>
make_lens(const std::vector<Triple>& dayvec) {
    std::vector<std::pair<lfloat, std::pair<Triple, Triple>>> lengths;
    for (const Triple& a: dayvec) {
        for (const Triple& b: dayvec) {
            if (&a < &b) continue;
            if (a == b) continue;
            lengths.emplace_back(sl_distance(a, b), std::make_pair(a, b));
        }
    }
    aoc::quicksort_pairs(lengths);
    if constexpr (aoc::test_mode) {
        for (const auto [d, t]: lengths) {}
    }
    return lengths;
}

void run_part1(const std::vector<Triple>& dayvec, const size_t n_cons) {
    const auto                       lengths{make_lens(dayvec)};
    std::vector<std::vector<Triple>> circuits;
    for (const auto [n, len]: zip(iota(0U, n_cons), lengths)) {
        const auto [a, b] = len.second;
        bool changed{false};
        aoc::print("{:15.5f} - {}, {}", len.first, a.str(), b.str());
        for (const auto [circno, circuit]: zip(iota(0U), circuits)) {
            const bool ina = aoc::invec(circuit, a);
            const bool inb = aoc::invec(circuit, b);
            if (ina || inb) {
                if (!ina) {
                    circuit.push_back(a);
                    aoc::print("circuit {}: add a {}", circno, a.str());
                }
                if (!inb) {
                    circuit.push_back(b);
                    aoc::print("circuit {}: add b {}", circno, b.str());
                }
                changed = true;
                break;
            }
        }
        if (!changed) {
            aoc::print("new circuit: add {}, {}", a.str(), b.str());
            circuits.emplace_back();
            circuits.back().push_back(a);
            circuits.back().push_back(b);
        }
    }
    std::vector<size_t> sizes;
    for (const auto& circuit: circuits) {
        aoc::print("circuit: {}", circuit.size());
        sizes.push_back(circuit.size());
    }
    std::ranges::sort(sizes);
    std::ranges::reverse(sizes);
    aoc::part1 = 1;
    aoc::print("idx: siz - part1");
    for (const auto [i, size]: zip(iota(0U, 3U), sizes)) {
        aoc::part1 *= size;
        aoc::print("{:>3}: {:>3} - {:>5}", i, size, aoc::part1);
    }
}

void run_part2(
    [[maybe_unused]] const std::vector<Triple>& dayvec,
    [[maybe_unused]] const size_t               n_cons
) {}
} // namespace

void aoc::run() {
    const std::vector<Triple> dayvec{parse(file::lines(aoc::file::day_stream()))};
    const size_t              n_cons{test_mode ? 10 : 1000};
    run_part1(dayvec, n_cons);
    run_part2(dayvec, n_cons);
}
