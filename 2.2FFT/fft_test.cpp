#include "fft.h"
#include <iostream>
#include <cmath>

int main() {
    hls::stream<complex_t> input_stream;
    hls::stream<complex_t> output_stream;
    
    // 生成测试数据：简单的正弦波
    for (int i = 0; i < 256; i++) {
        double angle = 2.0 * M_PI * i * 4 / 256.0;  // 4Hz信号
        complex_t value(cos(angle), 0);
        input_stream.write(value);
    }
    
    // 运行FFT
    fft_256(input_stream, output_stream);
    
    // 验证结果
    std::cout << "FFT结果：" << std::endl;
    for (int i = 0; i < 256; i++) {
        if (!output_stream.empty()) {
            complex_t value = output_stream.read();
            double real = value.real();
            double imag = value.imag();
            double magnitude = std::sqrt(double(real * real + imag * imag));
            
            // 只打印幅值较大的分量
            if (magnitude > 0.1) {
                std::cout << "频点 " << i << ": 幅值 = " << magnitude << std::endl;
            }
        }
    }
    
    return 0;
}
