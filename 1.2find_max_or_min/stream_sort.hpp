#include <hls_stream.h>

/* The main issue was that HLS streams must
 be passed by reference to avoid copying. 
 The fix is simply adding the & in the function declaration.
 The implementation provided will read all values from the
  stream and find the maximum and minimum values. */
void stream_sort(hls::stream<int> &input, int &max, int &min);