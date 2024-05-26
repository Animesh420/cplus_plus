#include <iostream>
#include <vector>
#include <algorithm>
#include <format>
#include <cassert>
#include <numeric>
#include <ranges>

template<typename T>
std::ostream& operator << (std::ostream & s, const std::vector<std::vector<T>>& triangle) {
   
   for (const auto& row: triangle) {
    std::ranges::copy(row, std::ostream_iterator<T>(s, " "));
    s << '\n';
   }
   return s;
}

void show_vectors(std::ostream& s, const std::vector<std::vector<int>>& v) {
    size_t final_row_size = v.back().size();
    std::string spaces(final_row_size * 3, ' ');
    for (const auto& row: v) {
        s << spaces;
        if (spaces.size() > 3) {
            spaces.resize(spaces.size()-3);
        }

        for (const auto& data: row) {
            s << std::format("{: ^{}}", data, 6);
        }

        s << "\n";
    }
}

void show_view(std::ostream& s, const std::vector<std::vector<int>>& v) {
    
    std::string spaces(v.back().size(), ' ');
    for (const auto& row: v) {
        s << spaces;
        if (spaces.size()) {
            spaces.resize(spaces.size() - 1);
        }

        auto odds = row | std::views::transform([](int x){ return x % 2 ? '*': ' ';});

        for (const auto& data: odds) {
            s << data << ' ';
        }

        s << "\n";
    }
}

std::vector<int> get_next_row(const std::vector<int> &last_row) {
    std::vector next_row{1};
    if (last_row.empty()) {
        return next_row;
    }
    for (size_t idx = 0; idx + 1 < last_row.size(); ++idx) {
        next_row.emplace_back(last_row[idx] + last_row[idx + 1]);
    }
    next_row.emplace_back(1);
    return next_row;
}

void print_row(std::vector<int> row){
      for (auto number: row) {
            std::cout << number << ' ';
        }
        std::cout << '\n';
}

auto generate_triangle(int rows) {
    std::vector<std::vector<int>> triangle{{1}};

    for (int row =1; row < rows; ++row) {
        triangle.push_back(get_next_row(triangle.back()));
    }

    return triangle;
}

bool is_palindrome(const std::vector<int>& v){
    auto forward = v | std::views::take(v.size() / 2);
    auto backward = v | std::views::reverse | std::views::take(v.size() / 2);
    return std::ranges::equal(forward, backward);
}

void check_properties(const std::vector<std::vector<int>>& triangle) {
   size_t row_number = 1;
   int expected_total = 1;
   for (const auto& row : triangle) {
    assert(row.front() == 1);
    assert(row.back() == 1);
    assert(row.size() == row_number++);

    assert(std::accumulate(row.begin(), row.end(), 0) == expected_total);
    expected_total *= 2;

    assert(std::ranges::all_of(row, [](auto x){ return x >= 0;}));

    assert(is_palindrome(row));
   }

   std::cout << "Test passed successfully " << "\n";
}
int main() {
    // command: g++ -Wall --std=c++20 -o main.out ./vector101.cpp
    auto triangle = generate_triangle(20);
    show_view(std::cout, triangle);

    check_properties(triangle);
}