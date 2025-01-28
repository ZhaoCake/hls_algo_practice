#include "stream_sort.hpp"

int main() {
    hls::stream<int> input_stream;

    // 测试数据
    int data[] = {5, 3, 9, 2, 11, 6, 8};
    int num_elements = sizeof(data) / sizeof(data[0]);

    // 将数据写入流
    for (int i = 0; i < num_elements; i++) {
        input_stream.write(data[i]);
    }

    // 定义变量来存储最大值和最小值
    int max_value = 0;
    int min_value = 0;

    // 调用待测函数
    stream_sort(input_stream, max_value, min_value);

    // 输出结果
    std::cout << "The maximum value is: " << max_value << std::endl;
    std::cout << "The minimum value is: " << min_value << std::endl;

    // 验证结果
    int expected_max_value = 11; // 数据中的最大值
    int expected_min_value = 2;  // 数据中的最小值

    if (max_value == expected_max_value && min_value == expected_min_value) {
        std::cout << "Test passed!" << std::endl;
    } else {
        std::cout << "Test failed! Expected max: " << expected_max_value
                  << ", got: " << max_value
                  << "; Expected min: " << expected_min_value
                  << ", got: " << min_value << std::endl;
    }

    return 0;
}