#include "fft.h"
#include <math.h>

// 预计算的旋转因子表
static complex_t W[256];

// 初始化旋转因子
void init_twiddle_factors() {
    #pragma HLS ARRAY_PARTITION variable=W cyclic factor=8
    for (int i = 0; i < 256; i++) {
        double angle = -2.0 * M_PI * i / 256.0;
        W[i] = complex_t(cos(angle), sin(angle));
    }
}

// 比特位反转
unsigned char bit_reverse(unsigned char x) {
    x = ((x & 0x55) << 1) | ((x & 0xAA) >> 1);
    x = ((x & 0x33) << 2) | ((x & 0xCC) >> 2);
    return (x << 4) | (x >> 4);
}

void fft_256(hls::stream<complex_t>& input_stream, 
             hls::stream<complex_t>& output_stream) {
    #pragma HLS INTERFACE axis port=input_stream
    #pragma HLS INTERFACE axis port=output_stream
    #pragma HLS INTERFACE s_axilite port=return
    
    // 本地存储
    complex_t data[256];
    #pragma HLS ARRAY_PARTITION variable=data cyclic factor=8
    
    // 初始化旋转因子
    init_twiddle_factors();
    
    // 读取输入数据
    INPUT_READ:
    for (int i = 0; i < 256; i++) {
        #pragma HLS PIPELINE
        data[bit_reverse(i)] = input_stream.read();
    }
    
    // FFT蝶形运算
    STAGE_LOOP:
    for (int stage = 0; stage < 8; stage++) {
        #pragma HLS LOOP_FLATTEN
        int butterfly_size = 1 << stage;
        
        BUTTERFLY_LOOP:
        for (int j = 0; j < 256; j += (butterfly_size * 2)) {
            #pragma HLS PIPELINE
            for (int k = 0; k < butterfly_size; k++) {
                #pragma HLS UNROLL factor=8
                int even_idx = j + k;
                int odd_idx = j + k + butterfly_size;
                int w_idx = k * (256 / (butterfly_size * 2));
                
                complex_t even = data[even_idx];
                complex_t odd = data[odd_idx];
                complex_t twiddle = W[w_idx];
                
                // 蝶形运算
                data[even_idx] = even + twiddle * odd;
                data[odd_idx] = even - twiddle * odd;
            }
        }
    }
    
    // 输出结果
    OUTPUT_WRITE:
    for (int i = 0; i < 256; i++) {
        #pragma HLS PIPELINE
        output_stream.write(data[i]);
    }
}
