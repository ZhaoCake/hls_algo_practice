#ifndef FFT_H
#define FFT_H

#include <ap_fixed.h>
#include <complex>
#include <hls_stream.h>

// 定义复数数据类型，使用定点数表示
typedef ap_fixed<16,1> data_t;  // 16位定点数，1位整数部分
typedef std::complex<data_t> complex_t;

// FFT函数声明
void fft_256(hls::stream<complex_t>& input_stream, 
             hls::stream<complex_t>& output_stream);

#endif
