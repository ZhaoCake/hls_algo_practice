#include "adder.hpp"

int main() {
    Q8_8 a, b, sum;

    bool overflow;

     // 测试用例 1: 无溢出
    a = 1.0;  // 1.0 in Q8.8
    b = 2.0;  // 2.0 in Q8.8
    adder(a, b, sum, overflow);
    std::cout << "Sum = " << sum.to_double() << ", Overflow = " << overflow << std::endl;

    // 测试用例 2: 溢出
    a = 127.0;  // 127.0 in Q8.8
    b = 1.0;    // 1.0 in Q8.8
    adder(a, b, sum, overflow);
    std::cout << "Sum = " << sum.to_double() << ", Overflow = " << overflow << std::endl;

    // 测试用例 3: 负数加法
    a = -1.0;  // -1.0 in Q8.8
    b = -2.0;  // -2.0 in Q8.8
    adder(a, b, sum, overflow);
    std::cout << "Sum = " << sum.to_double() << ", Overflow = " << overflow << std::endl;

    return 0;


}