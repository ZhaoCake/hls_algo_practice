#include <iostream>
#include "fir.h"

int main() {
    // 创建测试用的输入输出流
    hls::stream<data_t> input_stream;
    hls::stream<data_t> output_stream;
    
    // 定义滤波器系数（示例：低通滤波器）
    data_t coefficients[N_TAPS] = {
        0.1, 0.1, 0.1, 0.1, 0.1,
        0.1, 0.1, 0.1, 0.1, 0.1,
        0.1
    };
    
    // 生成测试数据
    for (int i = 0; i < 20; i++) {
        input_stream.write(data_t(i));
    }
    
    // 运行滤波器
    fir_filter(input_stream, output_stream, coefficients);
    
    // 打印结果
    std::cout << "FIR Filter Output:" << std::endl;
    while (!output_stream.empty()) {
        std::cout << output_stream.read().to_float() << std::endl;
    }
    
    return 0;
}
