#ifndef __FIR_H__
#define __FIR_H__

#include <ap_fixed.h>
#include "hls_stream.h"

// 定义FIR滤波器的阶数
#define N_TAPS 11

// 定义数据类型：16位定点数，8位整数部分
typedef ap_fixed<16,8> data_t;

// FIR滤波器函数声明
void fir_filter(hls::stream<data_t>& in_stream, 
                hls::stream<data_t>& out_stream,
                data_t coefficients[N_TAPS]);

#endif
