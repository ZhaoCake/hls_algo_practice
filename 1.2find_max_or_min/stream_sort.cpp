#include "stream_sort.hpp"
#include <limits>

void stream_sort(hls::stream<int> &input, int &max, int &min) {
    max = std::numeric_limits<int>::min();
    min = std::numeric_limits<int>::max();
    
    while (!input.empty()) {
        int val = input.read();
        if (val > max) max = val;
        if (val < min) min = val;
    }
}