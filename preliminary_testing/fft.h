//read "number" audio samples and output processed fourier transform to output
//extra processing: applies Hamming window
void run_fft(float *output);

//initialize fft plans and arrays
void initialize_fft(int size);
