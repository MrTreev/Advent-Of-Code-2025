#include "util.h"
#include <cstddef>
#define write(...) ::std::print(std::cout, __VA_ARGS__)

namespace {
using aoc::check;
using aoc::print;
using aoc::string::is_numeric;
using aoc::string::toint;

class Machine {
    std::vector<char>                m_lights;
    std::vector<std::vector<size_t>> m_wiring;
    std::vector<size_t>              m_joltage;
    static constexpr bool            M_DISPLAY{true};

public:
    Machine(const std::string& line) {
        auto pointer{line.begin()};
        check(*pointer == '[', "first character must be '['");
        std::advance(pointer, 1);
        while (*pointer != ']') {
            m_lights.push_back(*pointer);
            std::advance(pointer, 1);
        }
        check(*pointer == ']', "character at end of first pass must be ']'");
        std::advance(pointer, 1);
        check(*pointer == ' ', "check for space");
        std::advance(pointer, 1);
        while (*pointer != '{') {
            check(*pointer == '(', "check for open-bracket");
            std::advance(pointer, 1);
            m_wiring.emplace_back();
            std::string builder;
            while (*pointer != ')') {
                if (is_numeric(*pointer)) {
                    builder += *pointer;
                } else {
                    check(*pointer == ',', "check for comma");
                    m_wiring.back().push_back(toint<size_t>(builder));
                    builder.clear();
                }
                std::advance(pointer, 1);
            }
            m_wiring.back().push_back(toint<size_t>(builder));
            check(*pointer == ')', "check for close-bracket");
            std::advance(pointer, 1);
            check(*pointer == ' ', "check for space in wiring");
            std::advance(pointer, 1);
        }
        check(*pointer == '{', "check for open-squiggly");
        std::advance(pointer, 1);
        std::string builder;
        while (*pointer != '}') {
            if (is_numeric(*pointer)) {
                builder += *pointer;
            } else {
                check(*pointer == ',', "check for comma");
                m_joltage.push_back(toint<size_t>(builder));
                builder.clear();
            }
            std::advance(pointer, 1);
        }
        m_wiring.back().push_back(toint<size_t>(builder));
        check(*pointer == '}', "check for close-squiggly");
        std::advance(pointer, 2);
        check(pointer == line.end(), "check for end of line");
        if (M_DISPLAY) {
            print("Machine: '{}'", line);
            write("    m_lights: ");
            for (const char light: m_lights) {
                write("{}", light);
            }
            print("\n    m_wiring:");
            for (const auto& wire: m_wiring) {
                write("        (");
                for (const auto num: wire) {
                    write("{:>3}, ", num);
                }
                write(")\n");
            }
            write("    m_joltage: ");
            for (const auto& jolt: m_joltage) {
                write("{}, ", jolt);
            }
            write("\n");
        }
    }
};

std::vector<Machine> parse(const std::vector<std::string>& lines) {
    std::vector<Machine> retval;
    retval.reserve(lines.size());
    for (const std::string& line: lines) {
        retval.emplace_back(line);
    }
    return retval;
}

void run_part1([[maybe_unused]] const std::vector<Machine>& dayvec) {}

void run_part2([[maybe_unused]] const std::vector<Machine>& dayvec) {}

} // namespace

void aoc::run() {
    const std::vector<Machine> dayvec{parse(file::lines(file::day_stream()))};
    run_part1(dayvec);
    run_part2(dayvec);
}
