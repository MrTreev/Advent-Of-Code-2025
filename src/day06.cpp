#include "util.h"
#include <utility>

#define write(...) ::std::print(std::cout, __VA_ARGS__)

namespace {
using std::ranges::views::iota;
using std::ranges::views::zip;

void pushnum(
    std::string&                      number,
    size_t&                           counter,
    std::vector<std::vector<size_t>>& items,
    bool                              firstline
) {
    if (!number.empty()) {
        counter += 1;
        if (firstline && items.size() <= counter) {
            items.emplace_back();
        }
        const auto toint = aoc::string::toint<size_t>(number);
        items[counter - 1].push_back(toint);
        number = "";
    }
}

std::vector<std::pair<char, std::vector<size_t>>> parse_1(const std::vector<std::string>& lines) {
    std::vector<std::vector<size_t>> items;
    std::vector<char>                operations;
    bool                             firstline{true};
    for (const std::string& line: lines) {
        size_t      counter{0};
        std::string number;
        if (line.front() == '*' || line.front() == '+') {
            for (const char cha: line) {
                if (cha == '+' || cha == '*') {
                    operations.push_back(cha);
                }
            }
            std::vector<std::pair<char, std::vector<size_t>>> retval;
            for (const auto [opp, nums]: zip(operations, items)) {
                retval.emplace_back(opp, nums);
            }
            return retval;
        }
        for (const char cha: line) {
            if (aoc::string::is_numeric(cha)) {
                number.push_back(cha);
            } else {
                pushnum(number, counter, items, firstline);
            }
        }
        pushnum(number, counter, items, firstline);
        counter   = 0;
        firstline = false;
    }
    std::unreachable();
};

void run_part1(const std::vector<std::string>& lines) {
    const std::vector<std::pair<char, std::vector<size_t>>> items{parse_1(lines)};
    for (const auto& formula: items) {
        const auto& [operation, numbers] = formula;
        size_t op_result{1};
        for (const auto& item: numbers) {
            switch (operation) {
            case '+': op_result += item; break;
            case '*': op_result *= item; break;
            default:  std::unreachable();
            }
        }
        if (operation == '+') op_result -= 1;
        aoc::part1 += op_result;
    }
}

std::vector<std::pair<char, std::vector<size_t>>> parse_2(const std::vector<std::string>& lines) {
    std::vector<std::vector<size_t>> items;
    std::vector<char>                operations;
    std::vector<size_t>              sizes;
    sizes.reserve(lines.size());
    for (const auto& line: lines) {
        sizes.push_back(line.size());
    }
    items.emplace_back();
    const auto [_, vecsize] = aoc::max_in(sizes);
    for (const size_t idx: iota(0U, vecsize)) {
        std::string number;
        uint8_t     setme{0};
        for (const auto [shifter, line]: zip(iota(0U, lines.size()), lines)) {
            if (idx >= line.size()) break;
            if (aoc::string::is_numeric(line[idx])) {
                number += line[idx];
                setme  |= (1U << shifter);
            }
        }
        items.back().push_back(aoc::string::toint<size_t>(number));
        if (setme == 0) {
            items.back().pop_back();
            items.emplace_back();
        }
        number.erase();
    }
    items.pop_back();
    for (const char thing: lines.back()) {
        if (thing == '+' || thing == '*') operations.push_back(thing);
    }
    aoc::check(
        items.size() == operations.size(),
        std::format("items({}), operations({})", items, operations)
    );
    std::vector<std::pair<char, std::vector<size_t>>> retval;
    for (const auto [opp, num]: zip(operations, items)) {
        retval.emplace_back(opp, num);
    }
    return retval;
}

void run_part2(const std::vector<std::string>& lines) {
    const auto parsed = parse_2(lines);
    for (const auto& [operation, numbers]: parsed) {
        size_t op_result{1};
        write("operation({}) {{", operation);
        for (const auto item: numbers) {
            write("{:>5}, ", item);
            switch (operation) {
            case '+': op_result += item; break;
            case '*': op_result *= item; break;
            default:  std::unreachable();
            }
        }
        if (operation == '+') op_result -= 1;
        aoc::part2 += op_result;
        write("}} = {}\n", op_result);
    }
}
} // namespace

void aoc::run() {
    std::ifstream            daystr{aoc::file::day_stream()};
    std::vector<std::string> lines;
    {
        std::string line;
        while (std::getline(daystr, line)) {
            lines.push_back(line + " ");
        }
    }
    run_part1(lines);
    run_part2(lines);
}
