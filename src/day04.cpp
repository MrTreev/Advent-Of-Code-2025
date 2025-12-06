#include "util.h"
#define write(...) ::std::print(std::cout, __VA_ARGS__)

namespace aoc {
namespace {
using std::views::iota;

class Matrix {
    std::vector<char> m_buffer;
    size_t            m_ncols{0};
    size_t            m_nrows{0};

public:
    Matrix(std::ifstream& input) {
        std::string line{};
        while (std::getline(input, line)) {
            check((m_ncols == 0) || line.size() == m_ncols, "Bad string length");
            if (m_ncols == 0) {
                check(!line.empty(), "Empty first line");
                debug("line size: {}", line.size());
                m_ncols = line.size();
                m_buffer.append_range(std::views::repeat('.', m_ncols + 3));
            }
            m_buffer.append_range(line);
            m_buffer.push_back('.');
            m_buffer.push_back('.');
            m_nrows += 1;
        }
        m_buffer.append_range(std::views::repeat('.', m_ncols + 3));
    }

    [[nodiscard]]
    size_t index(size_t row, size_t col) const {
        return (row * (m_ncols + 2)) + col;
    }

    [[nodiscard]]
    char getraw(size_t row, size_t col) const {
        return m_buffer[index(row, col)];
    }

    char operator[](size_t row, size_t col) const { return getraw(row + 1, col + 1); }

    void remove(size_t row, size_t col) { m_buffer[index(row + 1, col + 1)] = 'x'; }

    [[nodiscard]]
    const size_t& nrows() const {
        return m_nrows;
    }

    [[nodiscard]]
    const size_t& ncols() const {
        return m_ncols;
    }

    [[nodiscard]]
    std::array<char, 8> around(size_t row, size_t col) const {
        const std::array<char, 8> retval{
            getraw(row + 0, col + 0), //
            getraw(row + 0, col + 1), //
            getraw(row + 0, col + 2), //
            getraw(row + 1, col + 0), //
            getraw(row + 1, col + 2), //
            getraw(row + 2, col + 0), //
            getraw(row + 2, col + 1), //
            getraw(row + 2, col + 2)  //
        };
        return retval;
    }
};

[[maybe_unused]]
void show_field(const Matrix& floor) {
    std::print(std::cout, "|   ");
    const size_t columns = floor.ncols();
    const size_t rows    = floor.nrows();
    for (const size_t col: iota(0U, columns)) {
        std::print(std::cout, "|{:>3}", col);
    }
    std::print(std::cout, "|\n");
    for (const size_t row: iota(0U, rows)) {
        std::print(std::cout, "|{:>3}", row);
        for (const size_t col: iota(0U, columns)) {
            std::print(std::cout, "| {} ", floor[row, col]);
        }
        std::print(std::cout, "|\n");
    }
    std::print(std::cout, "\n");
}

size_t run_part1(const Matrix& floor) {
    size_t able{0};
    for (const size_t row: iota(0U, floor.nrows())) {
        for (const size_t col: iota(0U, floor.ncols())) {
            if (floor[row, col] != '.') {
                const auto arr{floor.around(row, col)};
                const long count{std::ranges::count(arr, '@')};
                if (count < 4) able += 1;
            }
        }
    }
    return able;
}

size_t run_part2(Matrix floor) {
    size_t changes{0};
    //NOLINTNEXTLINE(*-do-while)
    do {
        changes = 0;
        for (const size_t row: iota(0U, floor.nrows())) {
            for (const size_t col: iota(0U, floor.ncols())) {
                if (floor[row, col] == '@') {
                    const auto arr{floor.around(row, col)};
                    const long count{std::ranges::count(arr, '@')};
                    if (count < 4) {
                        floor.remove(row, col);
                        changes += 1;
                        print("changed: ({},{})", row, col);
                    }
                }
            }
        }
        print("changes: {}", changes);
    } while (changes != 0);
    return run_part1(floor);
}

} // namespace
} // namespace aoc

void aoc::run() {
    std::ifstream daystr{aoc::file::day_stream()};
    const Matrix  floor{daystr};
    show_field(floor);
    aoc::part1 = run_part1(floor);
    aoc::part2 = run_part2(floor);
}
