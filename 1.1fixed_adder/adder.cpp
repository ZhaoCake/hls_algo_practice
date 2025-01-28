#include "adder.hpp"

// a,b is parameters in; sum and overflow is parameters out.
// the type of it is the read enable and write enable.
void adder(Q8_8 a, Q8_8 b, Q8_8 &sum, bool &overflow) {

// ap_none is used when the data is effective. this ifc don't have hand signal.
#pragma HLS INTERFACE mode=ap_none port=a
#pragma HLS INTERFACE mode=ap_none port=b
// with a valid signal.
#pragma HLS INTERFACE mode=ap_vld port=sum
#pragma HLS INTERFACE mode=ap_vld port=overflow

    // add a and b.
    Q9_8 temp_sum = a + b;

    sum = temp_sum; // can be truncate auto.

    // 检查是否溢出
    if (temp_sum > 127.99609375 || temp_sum < -128.0) {  // Q8.8 的范围是 [-128.0, 127.99609375]
        overflow = true;
    } else {
        overflow = false;
    }
}
