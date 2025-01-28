#include <ap_fixed.h>

using Q8_8 = ap_fixed<16, 8>;
using Q9_8 = ap_fixed<17, 9>;

void adder(Q8_8 a, Q8_8 b, Q8_8 &sum, bool &overflow);