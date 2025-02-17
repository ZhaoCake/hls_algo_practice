#include "fir.h"

/**
 * @brief FIR滤波器实现
 * 
 * @param in_stream 输入数据流
 * @param out_stream 输出数据流
 * @param coefficients FIR滤波器系数
 * 
 * 该实现采用了以下优化技术：
 * 1. 数组分区以实现并行访问
 * 2. 流水线优化以提高吞吐量
 */
void fir_filter(hls::stream<data_t>& in_stream, 
                hls::stream<data_t>& out_stream,
                data_t coefficients[N_TAPS]) {
    
    // 移位寄存器用于存储历史输入
    data_t shift_reg[N_TAPS];
    #pragma HLS ARRAY_PARTITION variable=shift_reg complete
    #pragma HLS ARRAY_PARTITION variable=coefficients complete
    
    // 初始化移位寄存器
    init_loop:
    for (int i = 0; i < N_TAPS; i++) {
        #pragma HLS UNROLL
        shift_reg[i] = 0;
    }
    
    // 主处理循环
    main_loop:
    while (!in_stream.empty()) {
        #pragma HLS PIPELINE II=1
        
        // 移位操作
        shift_loop:
        for (int i = N_TAPS-1; i > 0; i--) {
            #pragma HLS UNROLL
            shift_reg[i] = shift_reg[i-1];
        }
        
        // 读取新数据
        shift_reg[0] = in_stream.read();
        
        // 计算FIR输出
        data_t acc = 0;
        mac_loop:
        for (int i = 0; i < N_TAPS; i++) {
            #pragma HLS UNROLL
            acc += shift_reg[i] * coefficients[i];
        }
        
        // 输出结果
        out_stream.write(acc);
    }
}
