#include "stream_sort.hpp"
#include <linux/limits.h>

void stream_sort(hls::stream<int> input, int &max, int &min) {
#pragma HLS INTERFACE mode=axis port=min
#pragma HLS INTERFACE mode=axis port=max
#pragma HLS INTERFACE mode=axis port=input
    
    
    int max_value = 0;
    int min_value = MAX_INPUT;

    int temp;

    while (!input.empty()) {
        temp = input.read();
        max_value = (temp > max_value) ? temp : max_value;
        min_value = (temp < min_value) ? temp : min_value;
    }
}