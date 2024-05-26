#include <iostream>
#include <functional>

template<typename T, typename U>
auto simple_plus(T lhs, U rhs) -> decltype(lhs + rhs) {
        return lhs + rhs;
}
// g++ hello_again.cpp -o ./helllo.out -std=c++11
auto main() -> int {
    std::cout << std::plus<int>{}(1, 1.23) << "\n";
    std::cout << std::plus<>{}(1, 1.23) << "\n";

}