#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fftw3.h>
#include "soundanalyze.h"

FILE *fp; //containing arecord process for sampling data from copy device
fftw_complex *in, *out; //fftw3 arrays: in contains data input to fourier transform, out is the forward fourier transform
fftw_plan p;

#define PI 3.14159


void initialize_fft(int size){
	//initialize arrays
	in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * size);
	out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * size);
	p = fftw_plan_dft_1d(size, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
}

	

void run_fft(float *output, int number){
	int i;
	
	//copy intensity values to complex fftw array and perform hamming windowing
	for (i=0;i<number;i++) {
		float windowVal = 0.54 - (0.46*cos(2*PI*(i/((number - 1)*1.0))));
		//float windowVal = 1;
		in[i][0] = output[i]*windowVal;
		in[i][1] = 0.0;
	}
		
	//Fast Fourier Transform:
	fftw_execute(p);

	//copy results to output array
	//up till number/2 due to nyquist tjafs
	for (i=0;i<number/2;i++){
		output[i] = sqrt(out[i][0]*out[i][0] + out[i][1]*out[i][1]);
	}
	
}
